/**
 * scan.c: Functions for moving the sensor towards a specified angle and taking a reading from one of the sensors
 *
 *  @author Christopher Ledo
 *  @date 4/18/2025
 */

#include <servo.h>
#include <ping.h>
#include <adc.h>
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "Timer.h"

/**
 * A replacement for the cyBOT_Scan function from previous labs
 */
double getScanAt(int angle, char scanType){
    double distance;
    servo_move(angle); //moves the sensor to take a reading at the given angle value
    if(scanType == SONAR){ //takes a reading using the ping sensor
        distance = ping_getDistance(); //getDistance does all calculations internally to find the distance to object
    }
    else if (scanType == IR){ //takes a reading using the IR sensor
        distance = pow((14493.0/adc_read()), 1.321); //calculations to use the ADC voltage to estimate distance
        //TODO: formula needs to be calibrated within adc.c
        //TODO: needs to be calculated within adc.c
    }
    return distance; //returns distance estimation from the scan
}
