#include <stdio.h>
#include "..\include\utils.h"


void msg_intro() {
    printf("### RPi GPIO TOOL ####\n");
}

void msg_command_options() {
    printf("1. GPIO Mode\n");
}

void usr_command(char * usr_c) {
    printf("> ");
    *usr_c = (char)getchar();
    printf("%c", *usr_c);
    printf("\n");
}