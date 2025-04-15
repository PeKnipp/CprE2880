/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	// Print "Hello, world" on the LCD
	char message[] = ":)";
	char display[21] = "                    ";
	char temp[21] = "";
	uint32_t delay = 300;
	uint32_t counter = 0;

	lcd_puts(display);
	while (1) {

	    for (counter = 0; counter < strlen(message); counter++){
	        strncpy(temp, display + 1, 19);
	        strncat(temp, message + counter, 1);
	        strcpy(display, temp);
	        memset(temp, '\0', sizeof(temp));
	        lcd_clear();
	        lcd_puts(display);
	        timer_waitMillis(delay);
	    }

	    for (counter = 0; counter<20; counter++){
	        strncpy(temp, display + 1, 19);
            strcat(temp, " ");
            strcpy(display, temp);
            memset(temp, '\0', sizeof(temp));
            lcd_clear();
            lcd_puts(display);
            timer_waitMillis(delay);
	    }

	}


	// lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
