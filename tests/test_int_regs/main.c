#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>


#define INT_BASE 0x3F00B000
#define PAGE_SIZE (4 * 1024)
#define BLOCK_SIZE (4 * 1024)

int mem_fd;
void *int_map;
volatile unsigned *int_m;

#define INT_PENDING *(int_m + 0x208/4)
#define INT_ENABLE *(int_m + 0x214/4)
#define INT_DISABLE *(int_m + 0x220/4)

#define GPIO_INT0 16
#define GPIO_INT1 17
#define GPIO_INT2 18
#define GPIO_INT3 19


void setup_io() {
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        printf("[ERROR] can't open /dev/mem \n");
        exit(-1);
    }

    int_map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        INT_BASE
    );

    close(mem_fd);

    if (int_map == MAP_FAILED) {
        printf("[ERROR] mmap error %d\n", (int)int_map);
        exit(-1);
    }

    int_m = (volatile unsigned *)int_map;

}


void int_enable(int regs_size, int* regs) {
    printf("[DEBUG] INT_ENABLE: %d\n", INT_ENABLE);
    for(int i=0; i<regs_size; i++) {
        INT_ENABLE = 1 << regs[i];
        printf("[DEBUG] INT_ENABLE%d: %d\n", regs[i], INT_ENABLE);
    }
}

void int_disable(int regs_size, int* regs) {
    printf("[DEBUG] INT_DISABLE: %d\n", INT_DISABLE);
    for(int i=0; i<regs_size; i++) {
        INT_DISABLE = 1 << regs[i];
        printf("[DEBUG] INT_DISABLE%d: %d\n", regs[i], INT_DISABLE);
    }
}


int main(int argc, char const *argv[]) {
    // Setup mmap
    setup_io();

//    printf("[DEBUG] ref_int_m: %d\n", int_m);
//    printf("[DEBUG] INT_PENDING: %d\n", INT_PENDING);
//    printf("[DEBUG] INT_ENABLE: %d\n", INT_ENABLE);

    // Define gpio_int array
    int gpio_int_regs[] = {
            GPIO_INT0,
            GPIO_INT1,
            GPIO_INT2,
            GPIO_INT3
        };
    int gpio_int_regs_size = (int)(sizeof(gpio_int_regs) /
                                   sizeof(gpio_int_regs[0]));
    // Set Mode
    char mode[12] = "both";
    if(argc > 1) {
        strcpy(mode,argv[1]);
    }

    printf("[DEBUG] mode: %s\n", mode);

    // Handle Mode
    if(strcmp(mode, "both")==0) {
        int_enable(
            gpio_int_regs_size,
            gpio_int_regs
        );

        sleep(1)

        int_disable(
            gpio_int_regs_size,
            gpio_int_regs
        );
    }
    else if(strcmp(mode, "--enable")==0 || strcmp(mode, "-e")==0) {
        int_enable(
            gpio_int_regs_size,
            gpio_int_regs
        );
    }
    else if(strcmp(mode, "--disable")==0 || strcmp(mode, "-d")==0) {
        int_disable(
            gpio_int_regs_size,
            gpio_int_regs
        );
    }
    else {
        printf("[ERROR] Invalid mode!");
    }
    return 0;
}
