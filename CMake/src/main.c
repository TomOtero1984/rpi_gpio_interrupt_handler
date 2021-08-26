//  Program for setting GPIO on RPI
//
//  Author: Tom Otero
//  Email:  tomotero1984@gmail.com
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"


void loop() {
    msg_command_options();
    // Init user command char pointer
    char * usr_c = malloc(sizeof(char));
    while(1) {
        usr_command(usr_c);
        switch (*usr_c) {
        case '1': {
            printf("usr_c = %c\n", *usr_c);
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
