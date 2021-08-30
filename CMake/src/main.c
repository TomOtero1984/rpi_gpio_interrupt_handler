//  Program for setting GPIO on RPI
//
//  Author: Tom Otero
//  Email:  tomotero1984@gmail.com
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/gpio.h"


void loop() {
    int pin = 18;
    msg_command_options();
    // Init user command char pointer
    char * usr_c = malloc(sizeof(char));
    while(1) {
        usr_command(usr_c);
        switch (*usr_c) {
        case '1': {
            GPIO_FALLING_EDGE_DETECT_ENABLE = 1 << pin;
            break;
        }
        case '2': {
            for(int i = 0; i < 10; i++)
            {
                printf("GPIO_PIN_EVENT_STATUS: %d",GPIO_PIN_EVENT_STATUS);
                sleep(1);
            }
            break;
        }
        case 'q': {
            return;
        }
        default:{
            printf("Invalid Command\n");
            break;
        }
        }
    }
    free(usr_c);
}

int main(int argc, char const *argv[])
{

    // Intro message
    msg_intro();
    // main loop
    loop();
    return 0;
}
