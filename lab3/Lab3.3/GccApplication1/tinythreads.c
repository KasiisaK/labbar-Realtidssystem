#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;
    
    initialized = 1;
}

static void enqueue(thread p, thread *queue) {
    p->next = *queue;
    *queue = p;
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    //add and run the thread
    enqueue(current, &readyQ);
    enqueue(newp, &readyQ);
    dispatch(dequeue(&readyQ));
    ENABLE();
}

void yield(void) {
    DISABLE();
    enqueue(current, &readyQ);
    dispatch(dequeue(&readyQ));
    ENABLE();
}

void lock(mutex *m) {
    DISABLE();
    // If already locked
    if(m->locked){
        enqueue(current, &(m->waitQ));
        dispatch(dequeue(&readyQ));
    } else {
        m->locked = 1;
    }
    ENABLE();
}

void unlock(mutex *m) {
    DISABLE();
    //if not waiting
    if((m->waitQ) == NULL){
        m->locked = 0;
    // If already unlocked
    } else {
        enqueue(current, &readyQ);
        dispatch(dequeue(&(m->waitQ)));
    }
    ENABLE();
}
