//lab1-part1

#include <avr/io.h>
#include <stdbool.h>

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

//pos: 0-5 position of the char, ch: char to display
void writeChar(char ch, int pos)
{
	//check outside range of display
	if(pos<0 || pos>5)
	{
		return;
	}
	
	//replace if not 0-9
	if (ch < '0' || ch > '9')
	{
		ch = ' ';
	}
}



