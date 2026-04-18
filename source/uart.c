#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "uart.h"

int main() {
    int bufSize = 100;
    uint8_t receiveBuffer[bufSize];
    uint32_t receiveBufferIndex = 0;
}

// write byte to Data Register
void UART_transmitByte(UART_t *port, uint8_t byte) {
    while (1) {
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

int UART_receiveByte(UART_t *port, uint8_t *receiveBuffer, uint32_t *receiveBufferIndex, uint32_t receiveBufferSize) {
    if (port == NULL || receiveBuffer == NULL || receiveBufferIndex == NULL) {
        // input argument no good;
        return 1;
    }

    while (port->UART_FR & RXFE_MASK) {
        ; // wait until DR is not empty
    }

    uint8_t data = (uint8_t)(port->UART_DR & 0xFF);

    if (*receiveBufferIndex < receiveBufferSize) { // buffer good 
        receiveBuffer[*receiveBufferIndex] = data;
        (*receiveBufferIndex)++;
    } else { // buffer overflow
        (*receiveBufferIndex) = 0;
        return 1;
    }

    return 0;
}

int UART_receiveBytes(UART_t *port, uint8_t *receiveBuffer, uint32_t *receiveBufferIndex, uint32_t receiveBufferSize) {
    if (port == NULL || receiveBuffer == NULL || receiveBufferIndex == NULL) {
        // input argument no good;
        return 1;
    }

    while ( !(port->UART_FR & RXFE_MASK) ) { // if DR is not empty
        // you read byte at a time, but UART_DR is 32bit, so you mask the first 8 bits
        uint8_t data = (uint8_t)(port->UART_DR & 0xFF);

        if (*receiveBufferIndex < receiveBufferSize) { // buffer good 
            receiveBuffer[*receiveBufferIndex] = data;
            (*receiveBufferIndex)++;
        } else { // buffer overflow
            (*receiveBufferIndex) = 0;
            return 1;
        }
    }

    return 0;
}
