#include <stdio.h>
#include <string.h>
#include "../include/utils.h"


void msg_intro() {
    printf("### RPi GPIO TOOL ####\n");
}

void msg_command_options() {
    printf("1. GPIO Mode\n");
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
