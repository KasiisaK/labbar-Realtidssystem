/*
 * lab5.c
 *
 * Created: 08/03/2025 18:14:19
 * Author : AskFr
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "gui.h"
#include "joystickHandler.h"


void sysInit(){
	// Clock Prescaler Register "maximum speed"
	CLKPR = 0b10000000; // Clock prescaler Change Enable
	CLKPR = 0b00000000; // Set 0 for sys clock
}

int main(void)
{

}

