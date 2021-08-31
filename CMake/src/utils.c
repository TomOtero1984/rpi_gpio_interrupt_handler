#include <stdio.h>
#include <string.h>
#include "../include/utils.h"


void msg_intro() {
    printf("### RPi GPIO TOOL ####\n");
}

void msg_command_options() {
    printf("1. Set GPIO Pin\n");
    printf("2. Read Pin Status\n");
    printf("-----------------\n");
    printf("Q. Quit\n");
}

void usr_command(char * usr_c) {
    printf("> ");
    *usr_c = (char)getchar();
    flush();
}

void flush() {
    /*Flush stdin*/
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

void write_gpio_status(int pin, int status) {
    printf("Status of pin %d: %d", pin, status);
}
