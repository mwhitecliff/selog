/*
 *    2024 by mwhitecliff
 *    Zephyr Workshop Noser
 */

#include <zephyr/kernel.h>

int main (void)
{
    printk("Hello world from %s\n", CONFIG_BOARD);
    return 0;
}