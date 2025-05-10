/*
 * lab5_PC.c
 *
 * Created: 2022-03-10 16:34:24
 * Author : simeng-0
 */ 


#include <stdio.h>
#include <string.h>

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <pthread.h>


int port;
int northG = 0;
int northR = 1;
int southG = 0;
int southR = 1;


unsigned int southA = 0b0100;
unsigned int northA = 0b0001;
unsigned int southE = 0b1000;
unsigned int northE = 0b0010;

int running = 1;

int northBoundCars = 0;
int southBoundCars = 0;
int carsOnBridge = 0;
pthread_mutex_t carsOnBridge_m = PTHREAD_MUTEX_INITIALIZER;

void initCom();
void* listen(void *id);
void printer();
void* writePort(void *id);
void simulator();
void* leavingBridge(void* id);
void* enterBridgeNorth(void* id);
void* enterBridgeSouth(void* id);


void initCom() {
	port = open("/dev/ttyS0", O_RDWR);
	struct termios settings;
	
	if(tcgetattr(port, &settings) != 0) {
		printf("1Error %i from tcgetattr: %s\n", errno, strerror(errno));
		//return 1;
	}

	settings.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	settings.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	settings.c_cflag &= ~CSIZE; // Clear all bits that set the data size
	settings.c_cflag |= CS8; // 8 bits per byte (most common)
	settings.c_cflag |= CREAD | CLOCAL;
	
	
	settings.c_lflag &= ~ICANON;
	settings.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	settings.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	settings.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	settings.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed


	// Set in/out baud rate to be 9600
	cfsetispeed(&settings, B9600);
	cfsetospeed(&settings, B9600);
	
	settings.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	settings.c_cc[VMIN] = 0;
	
	if (tcsetattr(port, TCSANOW, &settings) != 0) {
		printf("2Error %i from tcsetattr: %s\n", errno, strerror(errno));
		//return 1;
	}
}


void *listen(void *id) {
	while(running){
		printf("\e[1;1H\e[2J");
		char given;
		int length = read(port, &given, sizeof(given));
		printf("Received: %x\r\n", given);
		
		
		if (given & 0b0001){
			//north light is green
			northG = 1;
		}else{
			northG = 0;
		}
		if (given & 0b0010){
			//north light is red
			northR = 1;
		}else{
			northR = 0;
		}
		if (given & 0b0100){
			//south light is green
			southG = 1;
		}else{
			southG = 0;
		}
		if (given & 0b1000){
			//south light is red
			southR = 1;
		}else{
			southR = 0;
		}
		
		simulator();
		usleep(6000);
		printer();
		
	}
}

void printer(){
	pthread_mutex_lock(&carsOnBridge_m);
	printf("northG: %d, northR: %d\r\n", northG, northR);
	printf("southG: %d, southR: %d\r\n", southG, southR);
	printf("-------------------------------\r\n");
	printf("North light: %c%c\r\n", northG ? 'G' : ' ', northR ? 'R' : ' ');
	printf("South light: %c%c\r\n", southG ? 'G' : ' ', southR ? 'R' : ' ');
	printf("Cars northbound: %d\r\n", northBoundCars);
	printf("Cars southbound: %d\r\n", southBoundCars);
	printf("Cars on bridge: %d\r\n", carsOnBridge);
	printf("-------------------------------\r\n\n");
	pthread_mutex_unlock(&carsOnBridge_m);
}

void* writePort(void *id) {
	char ch;
	while(running) {
		scanf("%c", &ch );
		if(ch == 's') {
			write(port, &southA, sizeof(southA));
			southBoundCars++;
		}else if(ch == 'n') {
			write(port, &northA, sizeof(northA));
			northBoundCars++;
		}else if(ch == 'e') {
			running = 0;
		}
	}
}

void simulator(){
	pthread_t exitingcar;
	if(northG == 1 && northBoundCars > 0){
		northBoundCars--;
		pthread_mutex_lock(&carsOnBridge_m);
		carsOnBridge++;
		pthread_mutex_unlock(&carsOnBridge_m);
		pthread_create(&exitingcar, NULL, leavingBridge, NULL);	
		write(port, &northE, sizeof(northE));
	}else
	if(southG == 1 && southBoundCars > 0){
		southBoundCars--;
		pthread_mutex_lock(&carsOnBridge_m);
		carsOnBridge++;
		pthread_mutex_unlock(&carsOnBridge_m);
		pthread_create(&exitingcar, NULL, leavingBridge, NULL);
		write(port, &southE, sizeof(southE));
	}
}

void* leavingBridge(void* id){
	usleep(5000000);
	pthread_mutex_lock(&carsOnBridge_m);
	carsOnBridge--;
	pthread_mutex_unlock(&carsOnBridge_m);
}

int main(void){
	initCom();
	
	printer();
	
	pthread_t listener;
	pthread_t writer;
	
	pthread_create(&listener, NULL, listen, NULL);
	pthread_create(&writer, NULL, writePort, NULL);
	
	pthread_join(listener, NULL);
	pthread_join(writer, NULL);

}

