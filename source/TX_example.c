#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "rp2350_uart_driver.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"


// example transmission
int main() {
    // initialize UART
    UART_init(UART0, RESETS, 115200);
   
    // setting up bytes to send
    uint8_t string[] = "hello aidan\n";

    // sending those bytes
    while (1) {
        // -1 to exclude null terminator ('\0')
        UART_transmitBytes(UART0, string, sizeof(string) - 1);
    }

    return 0;
}
