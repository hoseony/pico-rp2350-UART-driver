#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "uart.h"

// write byte to Data Register
void UART_transmitByte(UART_t *port, uint8_t byte) {
    while(1) {
        if ( !(port->UART_FR & TXFF_MASK) ) {
            port->UART_DR = byte;
            break;
        }
    }
}

// write bytes to Data Register
void UART_transmitBytes(UART_t *port, uint8_t *byte, size_t length) {
    if (byte == NULL) return;

    while(length != 0) {
        if ( !(port->UART_FR & TXFF_MASK) ) {
            port->UART_DR = *byte;
            byte++;
            length--;
        }
    }
}

// write FIFO bit on LCR_H register (to enable / disbale FIFO)
void UART_writeBitFIFO(UART_t *port, bool enable) {
    if (enable) {
        port->UART_LCR_H |= (FEN_MASK);
    } else {
        port->UART_LCR_H &= ~(FEN_MASK);
    }
}

void UART_receive_byte(UART_t *port) {

}
