/*
 * calibration.c
 *
 *  Created on: Mar 12, 2025
 *      Author: pknipper
 */
#include "calibration.h"
void ServoCalibration(){
    lcd_init();
    timer_init();

    right_calibration_value = 283000;
    left_calibration_value = 1183000;

    cyBOT_init_Scan(0b0001);
    cyBOT_SERVO_cal();

}
