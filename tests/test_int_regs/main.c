#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
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

void setup_io() {
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        printf("can't open /dev/mem \n");
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
        printf("mmap error %d\n", (int)int_map);
        exit(-1);
    }

    int_m = (volatile unsigned *)int_map;

}


int main() {
    setup_io();
    printf("ref_int_m: %d\n", int_m);
    printf("INT_PENDING: %d\n", INT_PENDING);
    printf("INT_ENABLE: %d\n", INT_ENABLE);
    int regs[4] = {16,17,18,19};
    for(int i=0; i<4; i++) {
        INT_ENABLE = 1 << regs[i];
        printf("INT_ENABLE%d: %d\n", regs[i], INT_ENABLE);
    }

    printf("INT_DISABLE: %d\n", INT_DISABLE);
    for(int i=0; i<4; i++) {
        INT_DISABLE = 1 << regs[i];
        printf("INT_DISABLE%d: %d\n", regs[i], INT_DISABLE);
    }
}
