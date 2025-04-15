/*
 * cyBot_sendString.c
 *
 *  Created on: Feb 11, 2025
 *      Author: pknipper
 */

#include "cyBot_sendString.h"

void cyBot_sendString(char message[]){

    int i;
    for (i = 0; i < strlen(message); i++){
        cyBot_sendByte(message[i]);
    }
}
