/*
 * adc.c
 *
 *  Created on: Mar 25, 2025
 *      Author: pknipper
 */


#include "adc.h"

void adc_init(){
    //Start Port B
    SYSCTL_RCGCGPIO_R |= 0x02;

    //Start ADC0
    SYSCTL_RCGCADC_R |= 0x01;

    //Check active
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
    while ((SYSCTL_PRADC_R & 0x01) == 0) {};

    GPIO_PORTB_DIR_R &= 0xEF;
    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_DEN_R &= 0xEF;
    GPIO_PORTB_AMSEL_R |= 0x10;

    ADC0_ACTSS_R &= 0xFFF7;
    ADC0_EMUX_R &= 0x0FFF;
    ADC0_SSMUX3_R &= 0xFFF0;
    ADC0_SSMUX3_R += 10;
    ADC0_SSCTL3_R |= 0x0006;
    ADC0_IM_R &= 0xFFF7;
    ADC0_ACTSS_R |= 0x0008;
    ADC0_SAC_R |= 0x04;
}

uint16_t adc_read(){
    uint16_t result;
    ADC0_PSSI_R = 0x0008; // 1) initiate SS3
    while((ADC0_RIS_R&0x08)==0){}; // 2) wait for conversion done
    result = ADC0_SSFIFO3_R & 0xFFF; // 3) read result
    ADC0_ISC_R = 0x0008; // 4) acknowledge completion
    return result;
}
