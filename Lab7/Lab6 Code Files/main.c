/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart-interrupt.h"
#include "open_interface.h"
#include "movement.h"
#include "calibration.h"

#include <math.h>
#include <stdio.h>
#include <stdint.h>

struct fieldObject{
    char firstEdge;
    char secondEdge;
    float distance;
    float angle;
    char radialWidth;
    float linearWidth;
};

// Uncomment or add any include directives that you want to use
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

// Your code can use the global variables defined in uart-interrupt.c
// They are declared with the extern qualifier in uart-interrupt.h, which makes the variables visible to this file.

//#warning "Possible unimplemented functions"
//#define REPLACEME 0


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	uart_interrupt_init();
	cyBOT_init_Scan(0b0111);
    cyBOT_Scan_t scanner_data;
    cyBOT_Scan(0, &scanner_data);
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    char i;
    char j = 0;  //number of legit objects starts at zero
    char manual = 0;
    char wheels_on = 0;
    char info[100];
    char angleInc = 2;
//    const int scanArraySizes = 91; //180/angleInc + 1;
    float PINGdata[91]; //initialize arrays to only have as many entrys as scans
    short IRdata[91];
    struct fieldObject objects[6] = {0};

    right_calibration_value = 238000;
    left_calibration_value = 1188250;

//    ServoCalibration();

	while(command_flag != 3) //'q' character quits the program when not scanning
	{

      // YOUR CODE HERE
			//first, try leaving this loop empty and see what happens
			//then add code for your application
			// OPTIONAL
			//test and reset command_flag if your ISR is updating it
			//for example, if the flag is 1, do something, like send a message to PuTTY or LCD, or stop a sensor scan, etc.
			//be sure to reset command_flag so you don't keep responding to an old flag

	    if (command_flag == 1){ //'g' starts the scan
	        for (i = 0; i < 91; i++){
	            PINGdata[i] = 0;
	            IRdata[i] = 0;
	        }

	        sprintf(info, "\n\rANGLE:       PING:       IR:     \n\r");
	        uart_sendStr(info);

	        for (i=0; i<=180/angleInc; i++){

                if (command_flag == 2){ //'s' prematurely ends the scan
                    sprintf(info, "Scan cancelled\n\r");
                    uart_sendStr(info);
                    break;
                }

                if (command_flag == 5){ //'m' switches mode
                    command_flag = 0;
                    if (!manual){
                        sprintf(info, "Switching to manual scan\n\r");
                        uart_sendStr(info);
                    }
                    else{
                        sprintf(info, "Switching to auto scan\n\r");
                        uart_sendStr(info);
                    }
                    manual = !manual;

                }

                timer_waitMillis(20); //wait for servo
	            cyBOT_Scan(i * angleInc, &scanner_data); //scan
	            PINGdata[i] = scanner_data.sound_dist;
	            IRdata[i] = scanner_data.IR_raw_val;
	            sprintf(info, "%d       %f      %d      \n\r", i * angleInc, PINGdata[i], IRdata[i]);
	            uart_sendStr(info);

	        }

//	        if (j > 0){
//                int k;
//                for (k = 0; k < j; k++){
//                    objects[k].firstEdge = 0;
//                    objects[k].secondEdge = 0;
//                    objects[k].distance = 0;
//                    objects[k].angle = 0;
//                    objects[k].radialWidth = 0;
//                    objects[k].linearWidth = 0;
//                }
//	        }

	        j = 0;
	        for (i = 0; i < 91; i+=angleInc){   //sizeof(IRdata) = 180/angleInc + 1
	            command_flag = 0;
	            if (command_flag == 5){ //'m' switches mode
                    if (!manual){
                        sprintf(info, "Switching to manual scan\n\r");
                        uart_sendStr(info);
                    }
                    else{
                        sprintf(info, "Switching to auto scan\n\r");
                        uart_sendStr(info);
                    }
                    manual = !manual;

                }


	            if (IRdata[i] >= 750){ //if IR reports a number greater than 1000, probably an object

	                objects[j].firstEdge = i * angleInc;    //set the first edge of the object at the inital instance

	                do{

	                    objects[j].secondEdge = i * angleInc;   //while still reporting >1000 values incrementally set the second edge of the object
	                    i++;

	                }while (i < 91 && IRdata[i] >= 750);

	                objects[j].radialWidth = objects[j].secondEdge - objects[j].firstEdge;  //set the width

	                if (objects[j].radialWidth > angleInc){ //only count instances that have a radial width larger than the increment
	                    j++;
	                }

	            }
	        }

	        int smallestObject = 0;
	        for (i = 0; i<j; i++){
	            command_flag = 0;
	            if (command_flag == 5){ //'m' switches mode
                    if (!manual){
                        sprintf(info, "Switching to manual scan\n\r");
                        uart_sendStr(info);
                    }
                    else{
                        sprintf(info, "Switching to auto scan\n\r");
                        uart_sendStr(info);
                    }
                    manual = !manual;

                }

                objects[i].angle = (objects[i].firstEdge + objects[i].secondEdge)/2.0;
                objects[i].distance = PINGdata[(int)(objects[i].angle / angleInc)];
                objects[i].linearWidth = 2.0*objects[i].distance*tan((objects[i].radialWidth*(M_PI/180))/2.0);
                if (objects[i].linearWidth < objects[smallestObject].linearWidth){
                    smallestObject = i;
                }
	            sprintf(info, "\n\rObject_Number: %i\n\r", i+1);
                uart_sendStr(info);
                sprintf(info, "Object_Angle: %f\n\r", objects[i].angle);
                uart_sendStr(info);
                sprintf(info, "Object_Distance: %f\n\r", objects[i].distance);
                uart_sendStr(info);
                sprintf(info, "Object_Width: %f\n\r", objects[i].linearWidth);
                uart_sendStr(info);
                sprintf(info, "RW: %i\n\r", objects[i].radialWidth);
                uart_sendStr(info);
            }

	        sprintf(info,"Smallest object: %d", smallestObject + 1);
	        uart_sendStr(info);

	        if(!manual){
                if(objects[smallestObject].angle > 90){
                    sprintf(info,"\n\rTurning Left\n\r");
                    uart_sendStr(info);
                    cyBOT_Scan(0, &scanner_data);
                    turn_left(sensor_data, (objects[smallestObject].angle - 90.0 - 5.0));   //enters inf loop at open_interface.c -> char oi_uartReceive(void) -> while ((UART4_FR_R & UART_FR_RXFE))
                }
                else if(objects[smallestObject].angle < 90){
                    sprintf(info,"\n\rTurning Right\n\r");
                    uart_sendStr(info);
                    cyBOT_Scan(0, &scanner_data);
                    turn_right(sensor_data, (90.0 - objects[smallestObject].angle - 5.0));  //enters inf loop at open_interface.c -> char oi_uartReceive(void) -> while ((UART4_FR_R & UART_FR_RXFE))
                }
                else {
                    sprintf(info,"\n\rNot Turning!\n\r");
                    uart_sendStr(info);
                    cyBOT_Scan(0, &scanner_data);
                }

                sprintf(info,"Moving!\n\r");
                uart_sendStr(info);
                move_forward(sensor_data, objects[smallestObject].distance * 10 - 100);
	        }

            if (command_flag == 4 && !manual){
                command_flag = 1;
                sprintf(info, "RESCANNING\n\r");
                uart_sendStr(info);
            }
            else if(manual){
                wheels_on = 0;
                while (command_flag != 1){
                    if (command_flag == 6){
                        if (!wheels_on){
                            oi_setWheels(200, 200);
                            wheels_on = !wheels_on;

                        }
                    }
                    if (command_flag == 7){
                        if (!wheels_on){
                            oi_setWheels(-200, -200);
                            wheels_on = !wheels_on;

                        }
                    }
                    if (command_flag == 8){
                        if (!wheels_on){
                                oi_setWheels(150, -150);
                                wheels_on = !wheels_on;

                            }
                    }
                    if (command_flag == 9){
                        if (!wheels_on){
                            oi_setWheels(-150, 150);
                            wheels_on = !wheels_on;

                        }
                    }
                    if (command_flag == 10){
                        if (wheels_on){
                            oi_setWheels(0, 0);
                            wheels_on = !wheels_on;
                        }
                    }
                }
            }
            else command_flag = 0;
	    }
	}
    oi_free(sensor_data);
    return 0;
}
