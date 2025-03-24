#include "PCReader.h"
#include <pthread.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h> // usleep()

unsigned char getUSARTData(Reader *self) {
    pthread_mutex_lock(&self->readMtx);
    unsigned char data = self->usartData;
    pthread_mutex_unlock(&self->readMtx);
    return data;
}


void readerMainLoop(Reader *self) {
    // Continusly get data from USART and store in usartData
    while(1) { 
        unsigned char buf;
        int n = read(self->port_fd, &buf, 1);
        if(n < 0) printf("Read error");
        if(n > 0) {
            pthread_mutex_lock(&self->readMtx);
            self->usartData = buf;
            pthread_mutex_unlock(&self->readMtx);
            printf("Received: 0x%02X\n", buf); // Better debug format
        }
        usleep(1000); // Non-blocking poll
    }
} 