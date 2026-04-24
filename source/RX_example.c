#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "rp2350_uart_driver.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

int main(void) {
    // I needed this to actually be able to see the output through USB serial
    stdio_init_all();     

    // initialize UART
    UART_init(UART0, RESETS, 115200);

    // initialize buffer to receive bytes
    uint8_t rxBuf[128];
    uint32_t rxIdx = 0;

    // receive bytes
    while (1) {
        UART_receiveBytes(UART0, rxBuf, &rxIdx, sizeof(rxBuf));
        if (rxIdx > 0) { // when it actually received something
            printf("%.*s", rxIdx, rxBuf);
            UART_transmitBytes(UART0, rxBuf, rxIdx);
            rxIdx = 0;
        }
    }
}
