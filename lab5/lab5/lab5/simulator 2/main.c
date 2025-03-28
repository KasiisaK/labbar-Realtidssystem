#include <pthread.h>
#include <termios.h>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> // open (file manipulation)
#include <unistd.h> // read/wite

//TODO: macro kanske måste vara: unsigned int southA = 0b0100; för write
//TODO: ändra /dev/terS0 så blir rätt med "mode"

/*
Bit 0: Northbound car arrival sensor activated
Bit 1: Northbound bridge entry sensor activated
Bit 2: Southbound car arrival sensor activated
Bit 3: Southbound bridge entry sensor activated
*/
#define NORTH_ARVL		0b0001
#define NORTH_BR_ARVL	0b0010
#define SOUTH_ARVL		0b0100
#define SOUTH_BR_ARVL	0b1000

/*
Bit 0: Northbound green light status
Bit 1: Northbound red light status
Bit 2: Southbound green light status
Bit 3: Southbound red light status
*/
#define NORTH_GREEN 0b0001
#define NORTH_RED	0b0010
#define SOUTH_GREEN 0b0100
#define SOUTH_RED   0b1000

// Mutex
pthread_mutex_t carBridgeMtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t southCarMtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t northCarMtx = PTHREAD_MUTEX_INITIALIZER;


// Global variables
int serialPort;

int northCarQue;
int northBrigCar;
int southCarQue;
int southBrigCar;


int northLightGreen;
int northLightRed;
int southLightGreen;
int southLightRed;

// Struct for thread argument in removeCar
typedef struct {
    char direction;
} ThreadArg;

// Functions
void terminosInit();
void printState();
void* getUserInput(void* arg);
void* removeCarAfterFiveSec(void* arg);
void simulation();
void* mainProgramLoop(void* arg);

void terminosInit() {
    serialPort = open("/dev/terS2", O_RDWR);
    struct termios ter;

    if (tcgetattr(serialPort, &ter) != 0) {
        printf("Error: Could not open port.\n");
    } 

    // Set 9600N81
    cfsetispeed(&ter, B9600);
    cfsetospeed(&ter, B9600);
    ter.c_cflag &= ~PARENB;
    ter.c_cflag &= ~CSTOPB;
    ter.c_cflag &= ~CSIZE;
    ter.c_cflag |= CS8;

    // Disable flow control
    ter.c_cflag &= ~CRTSCTS;

    // Non-canonical mode
    ter.c_lflag &= ~ICANON;
    ter.c_lflag &= ~ECHO;
    ter.c_lflag &= ~ECHOE;
    ter.c_lflag &= ~ECHONL;
    ter.c_lflag &= ~ISIG;

    // Input modes
    ter.c_iflag &= ~(IXON | IXOFF | IXANY);
    ter.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

    // Output modes
    ter.c_oflag &= ~OPOST;
    ter.c_oflag &= ~ONLCR;

    if (tcsetattr(serialPort, TCSANOW, &ter) != 0) {
		printf("Error: Could not apply settings\n");
	}
}

void printState() {
	pthread_mutex_lock(&carBridgeMtx);
	pthread_mutex_lock(&southCarMtx);
	pthread_mutex_lock(&northCarMtx);
	printf("North cars que: %d, North cars bridge %d.\n", northCarQue, northBrigCar);
	printf("South cars que: %d, South cars bridge %d.\n", southCarQue, southBrigCar);
	printf("North light green: %d, South light green: %d\n", northLightGreen, southLightGreen);
    printf("North light red: %d, South light red: %d\n", northLightRed, southLightRed);
	pthread_mutex_unlock(&northCarMtx);
	pthread_mutex_unlock(&southCarMtx);
	pthread_mutex_unlock(&carBridgeMtx);
}

void* getUserInput(void* arg) {
    char input;
    while (1) {
        scanf("%c", &input);
        switch (input)
        {
        case 'n':
            // Write to the AVR
            write(serialPort, NORTH_ARVL, sizeof(NORTH_ARVL));
            pthread_mutex_lock(&northCarMtx);
            northCarQue++;
            pthread_mutex_unlock(&northCarMtx);
            break;
        case 's':
            // Write to the AVR
            write(serialPort, SOUTH_ARVL, sizeof(SOUTH_ARVL));
            pthread_mutex_lock(&southCarMtx);
            southCarQue++;
            pthread_mutex_unlock(&southCarMtx);
            break;
        case 'e':
            exit(0);
            break;
        
        default:
            //printf("Input was not n, s or e.\n");
            break;
        }
    }
    return NULL;
}

void* mainProgramLoop(void* arg) {
    while (1) {
        // Clear screen
        printf("\e[1;1H\e[2J");
        unsigned char buf;
        int n = read(serialPort, &buf, sizeof(buf));
        printf("USART: %x\n", buf);

        if (NORTH_GREEN & buf) northLightGreen = 1;
        if (NORTH_RED & buf) northLightRed = 1;
        if (SOUTH_GREEN & buf) southLightGreen = 1;
        if (SOUTH_RED & buf) southLightRed = 1;

        simulation();
        printState();
        usleep(1000000); // Reapet every sec
    }
    return NULL;
}

void* removeCarAfterFiveSec(void* arg) {
    // Get direction arg from struct
    ThreadArg* targ = (ThreadArg*)arg;
    char direction = targ->direction;
    free(arg);

    usleep(5000000); // 5 sec delay
    switch (direction)
    {
    case 'n':
        pthread_mutex_lock(&carBridgeMtx);
        northBrigCar--;
        pthread_mutex_unlock(&carBridgeMtx);
        break;
    case 's':
        pthread_mutex_lock(&carBridgeMtx);
        southBrigCar--;
        pthread_mutex_unlock(&carBridgeMtx);
        break;    
    default:
        break;
    }
    return NULL;
}

void simulation() {
    pthread_t carLeavingThread; // Leave after 5 sec
    ThreadArg* arg;

    // Handle north logic
    if (northLightGreen && northCarQue > 0) {
        pthread_mutex_lock(&carBridgeMtx);
        pthread_mutex_lock(&northCarMtx);
        // Set argument
        arg = malloc(sizeof(ThreadArg));
        arg->direction = 'n';
        // Remove que add to bridge
        northCarQue--;
        northBrigCar++;
        pthread_create(&carLeavingThread, NULL, removeCarAfterFiveSec, arg);
        pthread_detach(carLeavingThread);

        pthread_mutex_unlock(&northCarMtx);
        pthread_mutex_unlock(&carBridgeMtx);
        // Send info to AVR
        write(serialPort, NORTH_BR_ARVL, sizeof(NORTH_BR_ARVL));
    }
    // South logic
    if (southLightGreen && southCarQue > 0) {
        pthread_mutex_lock(&carBridgeMtx);
        pthread_mutex_lock(&southCarMtx);
        // Set arguent
        arg = malloc(sizeof(ThreadArg));
        arg->direction = 's';
        // Remove que add to bridge
        southCarQue--;
        southBrigCar++;
        pthread_create(&carLeavingThread, NULL, removeCarAfterFiveSec, arg);
        pthread_detach(carLeavingThread);
        
        pthread_mutex_unlock(&southCarMtx);
        pthread_mutex_unlock(&carBridgeMtx);
        // Send info to AVR
        write(serialPort, SOUTH_BR_ARVL, sizeof(SOUTH_BR_ARVL));
    }
}

int main() {
    terminosInit();

    pthread_t mainLoop;
    pthread_t userInputLoop;

    pthread_create(&mainLoop, NULL, mainProgramLoop, NULL);
    pthread_create(&userInputLoop, NULL, getUserInput, NULL);

    pthread_join(mainLoop, NULL);
    pthread_join(userInputLoop, NULL);

    return 0;
}