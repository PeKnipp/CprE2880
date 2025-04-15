///**
// * lab6_template.c
// *
// * Template file for CprE 288 Lab 6
// *
// * @author Diane Rover, 2/15/2020
// *
// */
//
////#include "Timer.h"
////#include "lcd.h"
//#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
//#include <stdbool.h>
//#include "driverlib/interrupt.h"
//
//// Uncomment or add any include directives that are needed
//// #include "open_interface.h"
//// #include "movement.h"
//// #include "button.h"
//
//
//
////#warning "Possible unimplemented functions"
////#define REPLACEME 0
//
//
//int main(void) {
////	timer_init(); // Must be called before lcd_init(), which uses timer functions
////	lcd_init();
//	uart_init();
//
//	 cyBOT_Scan_t scanner_data;
//	 cyBOT_init_Scan(0b0011);
//	// YOUR CODE HERE
//
//	char checkChar = 0;
//	int i;
//	char info[100];
//	int angleInc = 2;
//    float distanceAtAngle[180/angleInc+1];
//
//
//	while(1)
//	{
//	    //Part 1
//	    checkChar = uart_receive_nonblocking();
//	    if (checkChar == 'g'){
//            for (i=0; i<=180; i+=angleInc){
//                checkChar = uart_receive_nonblocking();
//                if (checkChar == 's'){
//                    sprintf(info, "Scan cancelled");
//                    uart_sendStr(info);
//                    break;
//                }
//                cyBOT_Scan(i, &scanner_data);
//                distanceAtAngle[i/angleInc] = scanner_data.sound_dist;
//                sprintf(info, "Angle: %i\nDistance: %f\n\n", i, scanner_data.sound_dist);
//                uart_sendStr(info);
//
//            }
//	    }
//
//
//	}
//
//}
