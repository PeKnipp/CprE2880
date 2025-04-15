/*
 * movement.c
 *
 *  Created on: Feb 7, 2025
 *      Author: pknipper
 */
#include "movement.h"

double move_forward(oi_t *sensor_data, double distance_mm){

    double sum = 0;

    oi_setWheels(200,200);
    while (sum < distance_mm){

        lcd_clear();
        oi_update(sensor_data);

        if (sensor_data->bumpLeft){

            sum += bump_left(sensor_data);
            oi_setWheels(200,200);
        }

        if (sensor_data->bumpRight){

            sum += bump_right(sensor_data);
            oi_setWheels(200,200);
        }

        sum += sensor_data -> distance;
        lcd_printf("%f", sum);
    }
    oi_setWheels(0,0);

    return sum;
}

double move_backward(oi_t *sensor_data, double distance_mm){

    double sum = 0;

        oi_setWheels(-150,-150);
        while (sum > (distance_mm * -1)){

            lcd_clear();
            oi_update(sensor_data);

//            if (sensor_data->bumpLeft){
//                bump_left(sensor_data);
//                oi_setWheels(-150,-150);
//            }
//
//            if (sensor_data->bumpRight){
//                bump_right(sensor_data);
//                oi_setWheels(-150,-150);
//            }

            sum += sensor_data -> distance;
            lcd_printf("%f", sum);
        }
        oi_setWheels(0,0);

        return sum;
    }


double turn_right(oi_t *sensor, double degrees){
    double currentAngle = 0;

    oi_setWheels(-100, 100);
    while ((currentAngle -5) > (degrees * -1) ){

        lcd_clear();
        oi_update(sensor);


        currentAngle += sensor -> angle;
        lcd_printf("%f", currentAngle);
    }
    oi_setWheels(0,0);

    return currentAngle;
}

double turn_left(oi_t *sensor, double degrees){
    double currentAngle = 0;

        oi_setWheels(100, -100);
        while ((currentAngle +5) < degrees ){
            oi_update(sensor);
            currentAngle += sensor -> angle;
            lcd_printf("%f", currentAngle);
        }
        oi_setWheels(0,0);

        return currentAngle;
}

double bump_right(oi_t *sensor){
    double amountBack = move_backward(sensor, 150);
    turn_left(sensor, 90);
    move_forward(sensor, 200);
    turn_right(sensor, 90);

    return amountBack;
}

double bump_left(oi_t *sensor){
    double amountBack = move_backward(sensor, 150);
    turn_right(sensor, 90);
    move_forward(sensor, 200);
    turn_left(sensor, 90);

    return amountBack;
}
