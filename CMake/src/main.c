#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

int main(int argc, char const *argv[])
{
    char * usr_c = malloc(sizeof(char));
    msg_intro();
    msg_command_options();
    usr_command(usr_c);
    printf("HERE%c\n", *usr_c);
    return 0;
}
