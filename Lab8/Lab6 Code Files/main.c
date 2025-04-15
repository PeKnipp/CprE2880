/**
 * lab8 - main.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "adc.h"
#include <stdio.h>
#include <math.h>



int main(void) {
    timer_init();
    lcd_init();
    adc_init();

    char data[100];
    while(1){
        lcd_clear();
        float distance = pow((14493.0/adc_read()), 1.321);
        sprintf(data, "%f", distance);
        lcd_puts(data);
        timer_waitMillis(2000);
    }


}
