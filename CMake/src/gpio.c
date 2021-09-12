#include "../include/gpio.h"


void printButton(int g)
{
    if (GET_GPIO(g)) // !=0 <-> bit is 1 <- port is HIGH=3.3V
        printf("Button pressed!\n");
    else // port is LOW=0V
        printf("Button released!\n");
}


void setup_io() {
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    /* mmap GPIO */
    gpio_map = mmap(
        NULL,                   //Any adddress in our space will do
        BLOCK_SIZE,             //Map length
        PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
        MAP_SHARED,             //Shared with other processes
        mem_fd,                 //File to map
        GPIO_BASE               //Offset to GPIO peripheral
    );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED) {
        printf("mmap error %d\n", (int)gpio_map); //errno also set!
        exit(-1);
    }

    printf("gpio_map: %d\n", (int)gpio_map);

    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;

} // setup_io
