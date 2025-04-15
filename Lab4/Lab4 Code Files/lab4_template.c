/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
#include "cyBot_sendString.h"                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	cyBot_uart_init();
	            // Don't forget to initialize the cyBot UART before trying to use it

	// YOUR CODE HERE

	lcd_clear();
	lcd_puts("Running...");

      // YOUR CODE HERE

	//Part 1
//	lcd_printf("%d", button_getButton());

	//Part 3
	int pressedButton = 5;
	while(pressedButton){
	    pressedButton = button_getButton();

        if (pressedButton == 4){
            cyBot_sendString("Ultra Cool!\n\r");
        }
        else if (pressedButton == 3){
            cyBot_sendString("Super Cool!\n\r");
        }
        else if (pressedButton == 2){
            cyBot_sendString("Very Cool!\n\r");
        }
        else if (pressedButton == 1){
            cyBot_sendString("Cool!\n\r");
        }
        else { cyBot_sendString("Lame.\n\r");}
	}

	cyBot_sendString("END\n\r");
}
