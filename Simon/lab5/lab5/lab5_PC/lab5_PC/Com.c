/*
 * Com.c
 *
 * Created: 2022-03-11 14:07:10
 *  Author: simeng-0
 */ 

#include "Com.h"


//fileP = fopen("/dev/ttyS0", "rb+"); // reading and writing in binary mode

serial = open("")

int* initCom(Com *self) {
	int port = open("/dev/ttyS0", O_RDWR);
	struct termios settings;
	
	if(tcgetattr(port, &settings) != 0) {
		printf("1Error %i from tcgetattr: %s\n", errno, strerror(errno));
		return 1;
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
	self->port = &port;
	return &port;
}


void cycle(Com *self){	//working name
	int sent = 0;
	int changed = 0;
	
	
	//tries to continue sending cars in the same direction
	if(self->direction == 's' && self->southBound > 0){
		self->carsLeftUntilChange--;
		//make thread let south car pass
		sent = 1;
		}else if(self->direction == 'n' && self->northBound > 0){
		self->carsLeftUntilChange--;
		//make thread let north car pass
		sent = 1;
	}
	
	//if no car has been sent (current traffic direction is empty), it'll change direction and send send a car from there
	if(sent == 0){
		if (self->northBound > self->southBound){
			self->direction = 'n';
			//make thread let north car pass
			}else{
			self->direction = 's';
			//make thread let south car pass
		}
		self->carsLeftUntilChange = 15;
	}
	
	//changes direction if too many cars from one direction has passed
	if(self->carsLeftUntilChange == 0){
		if(self->direction == 'n' && self->southBound > 0){
			self->direction = 's';
			changed = 1;
			}else if(self->direction == 's' && self->northBound > 0){
			self->direction = 'n';
			changed = 1;
		}
		self->carsLeftUntilChange = 15;
	}
	
	//it'll call itself again as long as there are cars left. If the direction was changed it'll wait five seconds, otherwise one.
	if(self->northBound > 0 || self->southBound > 0){
		if(changed == 1){
			AFTER(SEC(5), self, cycle, 0);
			}else{
			AFTER(SEC(1), self, cycle, 0);
		}
		}else{
		self->carsLeftUntilChange = 15;
	}
}


void listen() {
	
}


void readWrite() {
	
	

	//unsigned char msg[] = { 's', 'n', 'n', 'l', 'o', '\n' };
	//write(port, msg, sizeof(msg));
	
	//unsigned int south = 0b0100;
	//unsigned int north = 0b0001;
	//unsigned char ch;
	//scanf("%c", &ch);
	
	/*
	if(ch == 's') {
		write(port, &south, 2);
	}else if(ch == 'n') {
		write(port, &north, 2);
	}
	*/
	
	//write(port, &test, 2);
	

	int i = 5;
	while(i) {
		char buffer[100];
		ssize_t length = read(port, &buffer, sizeof(buffer));
		if (buffer[0] != 0){
			buffer[length] = '\0';
			printf("%s\n", buffer);
			i--;
			//break;
		}
	}
	
	/*
	int northG = 0;
	int northR = 1;
	int southG = 0;
	int southR = 1;
	
	while(1){
		char buffer[100];
		ssize_t length = read(port, &buffer, sizeof(buffer));
		if (buffer[0] != 0){
			if (buffer == 0b0001){
				//north light is green
				northG = 1;
			}else if (buffer == 0b0010){
				//north light is red
				northR = 1;
			}else if (buffer == 0b0100){
				//south light is green
				southG = 1;
			}else if (buffer == 0b1000){
				//south light is red
				southR = 1;
			}
			
			buffer[length] = '\0';
			printf("%s\n", buffer);
			//break;
		}
	}*/
	
	//char buffer[100];
	//ssize_t length = read(port, &buffer, sizeof(buffer));
	//buffer[length] = '\0';
	//printf("%s", buffer);
	
	close(port);
	return 0;
}