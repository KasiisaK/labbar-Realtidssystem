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

// System clock frequency (8 MHz)
#define F_CPU 8000000UL

// Desired interrupt period (50 ms)
#define INTERRUPT_PERIOD_MS 50

// Prescaler value (1024)
#define PRESCALER 1024

// Calculate the value for OCR1A
#define OCR1A_VALUE (((INTERRUPT_PERIOD_MS / 1000.0) * F_CPU) / PRESCALER - 1)

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
int isPressed = 0;

static void initialize(void) {
	int i;
	for (i = 0; i < NTHREADS - 1; i++)
	threads[i].next = &threads[i + 1];
	threads[NTHREADS - 1].next = NULL;
	
	// Enable pull-up resistor on PORTB pin 7 (joystick downward)
	DDRB &= ~(1 << DDB7);  // Set PORTB pin 7 as input
	PORTB |= (1 << PB7); // Enable pull-up resistor
	
	// Enable pin change interrupt for PCINT15 (PORTB pin 7)
	PCMSK1 |= (1 << PCINT15); // Enable PCINT15 in Pin Change Mask Register 1
	EIMSK |= (1 << PCIE1); // Enable PCI1 in External Interrupt Mask Register
	
	// Configure OCR1A (Output Compare Register A) for 50 ms interrupts
	TCCR1B |= (1 << WGM12);  // Set CTC mode (Clear Timer on Compare)
	OCR1A = OCR1A_VALUE; // Set compare value for 50 ms (8 MHz / 1024 prescaler)
	TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
	TIMSK1 |= (1 << OCIE1A); // Enable Timer/Counter1 Compare Match A interrupt
	
	// Enable global interrupts
	sei();
	initialized = 1;
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
    }
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

    enqueue(newp, &readyQ);
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
		enqueue(current, &(m->waitQ)); // Add current thread to the mutex wait queue
		dispatch(dequeue(&readyQ));    // Dispatch the next thread
		} else {
		m->locked = 1; // Lock the mutex
	}
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
	if (m->waitQ) {
		enqueue(dequeue(&(m->waitQ)), &readyQ); // Move a thread from the wait queue to the ready queue
		} else {
		m->locked = 0; // Unlock the mutex
	}
	ENABLE();
}

// ISR(PCINT1_vect) {
// 	if (!(PINB & (1 << PINB7))) { // Check if PORTB pin 7 is low (joystick pressed)
// 		if (!isPressed) { // Only yield if the joystick was not already pressed
// 			isPressed = 1; // Set the flag to indicate the joystick is pressed
// 			yield(); // Call yield() to switch threads
// 		}
// 		} else {
// 		isPressed = 0; // Reset the flag when the joystick is released
// 	}
// }

// Timer interupt
ISR(TIMER1_COMPA_vect) {
	yield(); // Call yield() to switch threads
}