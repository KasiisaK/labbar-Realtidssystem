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

bool joystick_pressed = 0;


static void initialize(void) {
	int i;
	for (i = 0; i < NTHREADS - 1; i++)
	threads[i].next = &threads[i + 1];
	threads[NTHREADS - 1].next = NULL;
	initialized = 1;
}

static void enqueue(thread p, thread *queue) {
	// Insert at index 0
	p->next = *queue;
	*queue = p;
}

static thread dequeue(thread *queue) {
	thread p = *queue;
	if (*queue) {
		*queue = (*queue)->next;
		} else {
		while (1); // Kernel panic
	}
	return p;
}

static void dispatch(thread next) {
	if (setjmp(current->context) == 0) {
		current = next;
		longjmp(next->context, 1);
	}
}

void spawn(void (*function)(int), int arg) {
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

	// Start the new thr
	enqueue(newp, &readyQ);
	dispatch(newp); // Key change for Part 2

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
	if (m->locked) {
		enqueue(current, &(m->waitQ));
		dispatch(dequeue(&readyQ));
		} else {
		m->locked = 1;
	}
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
	if (m->waitQ) {
		enqueue(dequeue(&(m->waitQ)), &readyQ);
		} else {
		m->locked = 0;
	}
	ENABLE();
}
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
    // If already unlocked
	if (m->waitQ) {
		enqueue(dequeue(&(m->waitQ)), &readyQ); // Move a thread from the wait queue to the ready queue
		} else {
		m->locked = 0; // Unlock the mutex
	}
	ENABLE();
}

// Timer Interupt
ISR(TIMER1_COMPA_vect) {
	unlock(&blink_mutex);
}

// Joystick Interupt
ISR(PCINT1_vect) {
	bool oldValue = joystick_pressed;

	// Check if joystick is pressed (active low, bit 7 of PINB == 0)
	if (!(PINB & (1 << PB7))) {
		if (!joystick_pressed) {
			joystick_pressed = 1;
			// Checks toggle
			if (oldValue == 0 && joystick_pressed == 1) unlock(&button_mutex);
		}
		} else {
		joystick_pressed = 0;
	}
}



