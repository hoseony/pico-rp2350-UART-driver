#include <stdio.h>
#include <stdint.h>
#include "uart.h"

void UART_write_byte(UART_t *port, uint8_t byte) {
    if( !(port->UART_FR & ((uint32_t)1 << 5)) ) {
        port->UART_DR = byte;
    }
}

void UART_write_bytes(UART_t *port, uint8_t *byte, uint8_t length) {
    if (byte == NULL) {
        return;
    }

    while( !(port->UART_FR & ((uint32_t)1 << 5)) ) {
        port->UART_DR = *byte;
        byte++;
    };
}

