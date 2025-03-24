#include <pthread.h>

typedef struct {
    unsigned char usartData;
    int port_fd;
    pthread_mutex_t readMtx;
} Reader;

#define initPCReader(port) \ 
    {0, port, PTHREAD_MUTEX_INITIALIZER}


unsigned char getUSARTData(Reader *self);
void readerMainLoop(Reader *self);