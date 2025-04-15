/*
 * main.c
 *
 *  Created on: Feb 11, 2025
 *      Author: pknipper
 */


#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_sendString.h"
#include "cyBot_Scan.h"
#include "timer.h"
//#include <math.h>


void main(){
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    cyBOT_Scan_t scanner_data;
    cyBOT_init_Scan(0b0011);

    cyBot_uart_init();
    lcd_init();
    timer_init();

    right_calibration_value = 283000;
    left_calibration_value = 1183000;

    //Part 1
//    char ASCII = cyBot_getByte();
//    char message[11];
//
//    lcd_putc(ASCII);
//    sprintf(message, "Got an %c\n\r", ASCII);
//
//
//    cyBot_sendString(message);

    //Part 2 Calibration
    cyBOT_init_Scan(0b0001);
    cyBOT_SERVO_cal();


    //Part 2
//    int i;
//    int angleInc = 2;
//    char pressedKey = 'p';
//    char info[100];
//    float distanceAtAngle[180/angleInc+1];
//
//    while (pressedKey != 'm'){
//        pressedKey = cyBot_getByte();
//    }
//
//    for (i=0; i<=180; i+=angleInc){
//
//        cyBOT_Scan(i, &scanner_data);
//        distanceAtAngle[i/angleInc] = scanner_data.sound_dist;
//        sprintf(info, "Angle: %i\nDistance: %f\n\n", i, scanner_data.sound_dist);
//        cyBot_sendString(info);
//    }
//
//    cyBOT_init_Scan(0b0001);
//
//
//    //Part 3
//    int objNum = 1;
//
//    int firstIndex, secondIndex, angle , radialWidth;
//    float distance;
//
//    int swAngle = 0;
//    int sw = 1000;
//    float swDist = 0;
//
//
//    for (i=0; i<180/angleInc; i++){
//
//        if (distanceAtAngle[i] < 100){
//
//            firstIndex = i;
//
//            while (distanceAtAngle[i] < 100 && i<180/angleInc){
//
//                secondIndex=i;
//                i++;
//
//            }
//
//            angle = ((firstIndex*angleInc) + (secondIndex*angleInc)) / 2;
//            distance = distanceAtAngle[(firstIndex +secondIndex)/2];
//            radialWidth = (secondIndex*angleInc) - (firstIndex*angleInc);
//
//            if (radialWidth >= 5){
//
//                sprintf(info, "Object_Number: %i\nObject_Angle: %i\nObject_Distance: %f\nObject_Width: %i\n\n", objNum, angle, distance, radialWidth);
//                 cyBot_sendString(info);
//                 objNum++;
//
//                 if (radialWidth < sw){
//                     sw = radialWidth;
//                     swAngle = angle;
//                     swDist = distance;
//                 }
//
//            }
//
//        }
//    }
//
//    if(swAngle > 90){
//        cyBot_sendString("Turning Left\n\r");
//        cyBOT_Scan(90, &scanner_data);
//        turn_left(sensor_data, swAngle - 90 - 5);
//    }
//    else if(swAngle < 90){
//        cyBot_sendString("Turning Right\n\r");
//        cyBOT_Scan(90, &scanner_data);
//        turn_right(sensor_data, 90 - swAngle - 5);
//    }
//    else {cyBot_sendString("Not Turning\n\r");}
//
//    cyBot_sendString("Moving!\n\r");
//    move_forward(sensor_data, swDist * 10 - 100);
//
//    //manual movement
////    while (pressedKey != 'q'){
////            pressedKey = cyBot_getByte();
////            if (pressedKey == ' '){
////                oi_setWheels(0,0);
////            }
////            if (pressedKey == 'w'){
////                oi_setWheels(100,100);
//////                move_forward(sensor_data, 75);
////            }
////            if (pressedKey == 's'){
////                oi_setWheels(-100,-100);
//////                move_backward(sensor_data, 75);
////            }
////            if (pressedKey == 'a'){
////                turn_left(sensor_data, 5);
////            }
////            if (pressedKey == 'd'){
////                turn_right(sensor_data, 5);
////            }
////        }
//
//    cyBot_sendString("END\n\r");
    oi_free(sensor_data);
}
