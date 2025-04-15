/*
 * main.c
 *
 *  Created on: Feb 7, 2025
 *      Author: pknipper
 */
#include "open_interface.h"
#include "movement.h"

int main(void){
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    lcd_init();

    //Checkpoint 1
//    move_forward(sensor_data, 1000);

//    //Checkpoint 2
    move_forward(sensor_data, 500);
    turn_right(sensor_data, 90);
    move_forward(sensor_data, 500);
    turn_right(sensor_data, 90);
    move_forward(sensor_data, 500);
    turn_right(sensor_data, 90);
    move_forward(sensor_data, 500);

    //Checkpoint 3
//    move_forward(sensor_data, 2000);

    oi_free(sensor_data);
    return 0;
}
