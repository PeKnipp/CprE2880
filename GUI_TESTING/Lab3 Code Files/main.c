///////////////////////////////////////////////////////////////////////
// Name: Simple-CyBot-echo.c                                         //
// Author: Phillip Jones (phjones@iastate.edu)                       //
// Date: 09/26/2023                                                  //
// Description: Simple Cybot program that is an Echo'ish program for //
//              communicating with the Starter Client Socket code.   //
///////////////////////////////////////////////////////////////////////

#include "cyBot_uart.h"
#include "lcd.h"
#include "Timer.h"
#include "movement.h"
#include "cyBot_Scan.h"
#include "cybot_sendString.h"

void main () {
  oi_t *sensor_data = oi_alloc();
  oi_init(sensor_data);

  cyBOT_Scan_t scanner_data;
  cyBOT_init_Scan(0b0011);

  timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called 
	              // and enables time functions (e.g. timer_waitMillis)
  lcd_init();   // Initialize the the LCD screen.  This also clears the screen. 
  cyBot_uart_init();  // Initialize UART

  char my_data;       // Variable to get bytes from Client
  char command[100];  // Buffer to store command from Client
  int index = 0;      // Index position within the command buffer
  int connected = 1;
  int wheels_on = 0;

  // Write to LCD so that we know the program is running
  lcd_printf("Running");

  while(connected)
  {

    index = 0;  // Set index to the beginning of the command buffer
    my_data = cyBot_getByte(); // Get first byte of the command from the Client

    // Get the rest of the command until a newline byte (i.e., '\n') received
    while(my_data != '\n' )
    {
      command[index] = my_data;  // Place byte into the command buffer
      index++;
      my_data = cyBot_getByte(); // Get the next byte of the command
    }

    command[index] = '\n';  // place newline into command in case one wants to echo the full command back to the Client
    command[index+1] = 0;   // End command C-string with a NULL byte so that functions like printf know when to stop printing

    lcd_printf("Got: %s", command);  // Print received command to the LCD screen

    // Send a response to the Client (Starter Client expects the response to end with \n)
    // In this case I am just sending back the first byte of the command received and a '\n'
    cyBot_sendByte(command[0]);

    // Only send a '\n' if the first byte of the command is not a '\n',
    // to avoid sending back-to-back '\n' to the client
    if(command[0] != '\n')
    {
      cyBot_sendByte('\n');
    }

    if (command[0] == 'M'){
        oi_setWheels(0, 0);
        int i;
        int angleInc = 2;
        char info[100];

        for (i=0; i<=180; i+=angleInc){
                cyBOT_Scan(i, &scanner_data);
                sprintf(info, "Angle: %i\nDistance: %f\n\n", i, scanner_data.sound_dist);
                cyBot_sendString(info);
            }
        cyBot_sendString("END\n");
    }

    if(command[0] == ' '){
        if (wheels_on){
            oi_setWheels(0, 0);
            wheels_on = 0;
        }

    }

    if(command[0] == 'w'){
        if (!wheels_on){
            oi_setWheels(200, 200);
            wheels_on = 1;
        }
    }

    if(command[0] == 's'){
        if (!wheels_on){
            oi_setWheels(-200, -200);
            wheels_on = 1;
        }
}

    if(command[0] == 'a'){
        if (!wheels_on){
            oi_setWheels(150, -150);
            wheels_on = 1;
        }
    }

    if(command[0] == 'd'){
        if (!wheels_on){
            oi_setWheels(-150, 150);
            wheels_on = 1;
        }

    }

    if(command[0] == 'q'){
        connected = 0;
    }

  }
 
  oi_free(sensor_data);
}
