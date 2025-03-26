#include <pthread.h>

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>   // For perror
#include <stdlib.h>  // For exit

#include "bridge.h"
#include "PCReader.h"
#include "userInput.h"
#include "simulation.h"



int serialPort;

void terminosInit(int *port) {
    // Open port
    *port = open("/dev/ttyS0", O_RDWR);
    if (*port < 0) {
        perror("Error opening serial port");
        exit(1);
    }
    
    // Configure termios settings
    struct termios tty;
    if(tcgetattr(*port, &tty) != 0) {
        perror("Error getting termios settings");
        exit(1);
    }

    // Set baud rate (9600 baud)
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // N81 configuration
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    // Disable flow control
    tty.c_cflag &= ~CRTSCTS;
    
    // Non-canonical mode
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    
    // Input modes
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    
    // Output modes
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    
    // Apply settings
    if (tcsetattr(*port, TCSANOW, &tty) != 0) {
        perror("Error applying termios settings");
        exit(1);
    }
}


void main() {
    terminosInit(&serialPort);
    // Objects
    Bridge bridge = initBridge(); // North/south trafic lights
    Reader read = initPCReader(serialPort); // Reads data from AVR
    Simulation simulation = initSimulation(&bridge, &read, serialPort); // Main simulation
    Input inputHandler = initInput_handler(&simulation); // Takes input from user (n, s, e)

    // Threads
    pthread_t inputThread;
    pthread_t simulationThread;
    pthread_t readThread;

    pthread_create(&inputThread, NULL, (void*)getUserInput, &inputHandler);
    pthread_create(&simulationThread, NULL, (void*)mainSimulationLoop, &simulation);
    pthread_create(&readThread, NULL, (void*)readerMainLoop, &read);

    pthread_join(inputThread, NULL);
    pthread_join(simulationThread, NULL);
    pthread_join(readThread, NULL);

    return 0;
}