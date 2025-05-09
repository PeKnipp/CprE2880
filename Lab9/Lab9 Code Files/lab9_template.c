/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping_template.h"

// Uncomment or add any include directives that are needed

//#warning "Possible unimplemented functions"
//#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	char data[100];
//	unsigned long * timeptr;
	//timeptr = &time_diff;

	// YOUR CODE HERE

	while(1)
	{


      // YOUR CODE HERE
	    ping_trigger();

	    sprintf(data, "%lu|%f|%hu", time_diff, ping_getDistance(), overflow);
	    lcd_clear();
        lcd_puts(data);
	    timer_waitMillis(500);
	}

}
