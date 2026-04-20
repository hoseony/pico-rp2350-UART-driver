#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "uart.h"
// #include "hardware/clocks.h"

// --------------- function prototypes -----------------------
void UART_transmitByte(UART_t *port, uint8_t byte);
void UART_init(UART_t *port, RESETS_t *resets, uint32_t baudRate);
void UART_setBaudRate(UART_t *port, uint32_t UART_clk_hz, uint32_t baudRate);
void UART_transmitBytes(UART_t *port, uint8_t *byte, size_t length);
int UART_receiveByte(UART_t *port, uint8_t *receiveBuffer, uint32_t *receiveBufferIndex, uint32_t receiveBufferSize);
int UART_receiveBytes(UART_t *port, uint8_t *receiveBuffer, uint32_t *receiveBufferIndex, uint32_t receiveBufferSize);
void UART_writeBitFIFO(UART_t *port, bool enable);
void UART_writeBitCR(UART_t *port, bool enable);
// -----------------------------------------------------------

int main() {
    int bufSize = 100;
    uint8_t receiveBuffer[bufSize];
    uint32_t receiveBufferIndex = 0;

    UART_init(UART0, RESETS, 115200);
    
    for (volatile int i = 0; i < 100000; i++);  // small delay
   
    uint8_t string[] = "hello aidan";
    while(1) {
        UART_transmitBytes(UART0, string, sizeof(string) - 1);
    }
}

// write byte to Data Register
void UART_transmitByte(UART_t *port, uint8_t byte) {
    while (1) {
        if ( !(port->UART_FR & UART_FR_TXFF_MASK) ) {
            port->UART_DR = byte;
            break;
        }
    }
}

// basically made simpler version of uart_init from pg.972 on rp2350 documentation
void UART_init(UART_t *port, RESETS_t *resets, uint32_t baudRate) {
    // initialize the memory address
    GPIO_t *gpio = (GPIO_t *)BANK_IO_BASE;
 
    if (port == NULL || resets == NULL) {
        return;
    }

    // disable bits
    UART_writeBitCR(port, 0);

    // make UART0 to 0, (using UART)
    resets->RESET &= ~(RESET_UART0_MASK); // make UART0 to 0

    while( !(resets->RESET_DONE & RESET_UART0_MASK)) {
        ; // I am waiting for it to be reset
    }
   
    gpio->GPIO0_CTRL = GPIO_UART_FUNCT;
    gpio->GPIO1_CTRL = GPIO_UART_FUNCT;

    UART_setBaudRate(port, 48000000u, baudRate);
    UART_writeBitFIFO(port, 1);

    port->UART_LCR_H &= ~(0x3u << 5); // clear stuff
    port->UART_LCR_H |= (0x3u << 5); // setting the word length to be 8 ('b11 = 0x3u)

    UART_writeBitCR(port, 1);
}

void UART_setBaudRate(UART_t *port, uint32_t UART_clk_hz, uint32_t baudRate) {
    uint32_t baud_rate_div = (8 * UART_clk_hz / baudRate) + 1;
    uint32_t baud_ibrd = baud_rate_div >> 7;
    uint32_t baud_fbrd;

    if (baud_ibrd == 0) {
        baud_ibrd = 1;
        baud_fbrd = 0;
    } else if (baud_ibrd >= 65535) {
        baud_ibrd = 65535;
        baud_fbrd = 0;
    } else {
        baud_fbrd = (baud_rate_div & 0x7f) >> 1;
    }

    port->UART_IBRD = baud_ibrd;
    port->UART_FBRD = baud_fbrd; 

    port->UART_IBRD = 26;
    port->UART_FBRD = 3;
}

// write bytes to Data Register
void UART_transmitBytes(UART_t *port, uint8_t *byte, size_t length) {
    if (byte == NULL) return;

    while(length != 0) {
        if ( !(port->UART_FR & UART_FR_TXFF_MASK) ) {
            port->UART_DR = *byte;
            byte++;
            length--;
        }
    }
}

// write FIFO bit on LCR_H register (to enable / disbale FIFO)
void UART_writeBitFIFO(UART_t *port, bool enable) {
    if (enable) {
        port->UART_LCR_H |= (UART_LCR_H_FEN_MASK);
    } else {
        port->UART_LCR_H &= ~(UART_LCR_H_FEN_MASK);
    }
}

// enable RXE, TXE, EN for CR (you need to do this for initialize)
void UART_writeBitCR(UART_t *port, bool enable) {
    if (enable) {
        port->UART_CR |= (UART_CR_RXE_MASK | UART_CR_TXE_MASK | UART_CR_EN_MASK);
    } else {
        port->UART_CR &= ~(UART_CR_RXE_MASK | UART_CR_TXE_MASK | UART_CR_EN_MASK);
    }
}


int UART_receiveByte(UART_t *port, uint8_t *receiveBuffer, uint32_t *receiveBufferIndex, uint32_t receiveBufferSize) {
    if (port == NULL || receiveBuffer == NULL || receiveBufferIndex == NULL) {
        // input argument no good;
        return 1;
    }

    while (port->UART_FR & UART_FR_RXFE_MASK) {
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

    while ( !(port->UART_FR & UART_FR_RXFE_MASK) ) { // if DR is not empty
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
