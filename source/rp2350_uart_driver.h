#ifndef RP2350_UART_DRIVER_H
#define RP2350_UART_DRIVER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

// ------------------ MASKS ---------------------
#define UART_FR_TXFF_MASK (0x00000001u << 5)
#define UART_FR_RXFE_MASK (0x00000001u << 4)
#define UART_LCR_H_FEN_MASK (0x00000001u << 4)

#define UART_CR_RXE_MASK (0x00000001u << 9) // receive bit (1 to receive)
#define UART_CR_TXE_MASK (0x00000001u << 8) // transmit bit (1 to transmit)
#define UART_CR_EN_MASK (0x00000001u << 0) // enable UART (1 to enable)

// ------------------ List of Registers (UART) ---------------------
typedef struct {
    volatile uint32_t UART_DR;          // 0x000 Data Register
    volatile uint32_t UART_SR;          // 0x004 Recieve Status Register (error message)
    volatile uint32_t RESERVED0[4];     // occupy 16 bytes
    volatile uint32_t UART_FR;          // 0x018 flag register
    volatile uint32_t RESERVED1;        // occupy byte
    volatile uint32_t UART_ILPR;        // 0x020 low-power counter register
    volatile uint32_t UART_IBRD;        // 0x024 integer baud rate
    volatile uint32_t UART_FBRD;        // 0x028 fractional baud rate
    volatile uint32_t UART_LCR_H;       // 0x02c line control register
    volatile uint32_t UART_CR;          // 0x030 Control Register
    volatile uint32_t UART_IFLS;        // 0x034 interrupt FIFO
    volatile uint32_t UART_IMSC;        // 0x038 interrupt mask set
    volatile uint32_t UART_RIS;         // 0x03c Raw interrupt status register
    volatile uint32_t UART_MIS;         // 0x040 Masked Interrupt status register
    volatile uint32_t UART_ICR;         // 0x044 Interrupt clear register
    volatile uint32_t UART_DMACR;       // 0x048 DMA control Register
/*  I am not using these part for now
    volatile uint32_t UART_PERIPHID0;   // peripherals
    volatile uint32_t UART_PERIPHID1;
    volatile uint32_t UART_PERIPHID2;
    volatile uint32_t UART_PERIPHID3;
    volatile uint32_t UART_PCELLID0;    // PCELL?
    volatile uint32_t UART_PCELLID1;
    volatile uint32_t UART_PCELLID2;
    volatile uint32_t UART_PCELLID3;*/
} UART_t;

#define UART0_BASE 0x40070000u
#define UART1_BASE 0x40078000u

#define UART0 ((UART_t *)UART0_BASE)
#define UART1 ((UART_t *)UART1_BASE)

// ------------------RESET ---------------------
#define RESET_UART0_MASK (0x00000001u << 26)
#define RESET_UART1_MASK (0x00000001u << 27)
#define RESET_BASE 0x40020000u
#define RESETS ((RESETS_t *)RESET_BASE)

typedef struct {
    volatile uint32_t RESET; // 0x40020000
    volatile uint32_t WDSEL;
    volatile uint32_t RESET_DONE;
} RESETS_t;

// ------------------GPIO ---------------------
#define GPIO_UART_FUNCT 2 
#define BANK_IO_BASE 0x40028000u

typedef struct {
    volatile uint32_t STATUS; //0x40028000
    volatile uint32_t CTRL;
} GPIO_CTRL_PAIR_t;

#define GPIO0 ((GPIO_CTRL_PAIR_t *)(BANK_IO_BASE))
#define GPIO1 ((GPIO_CTRL_PAIR_t *)(BANK_IO_BASE + 0x008))


// --------------- function prototypes -----------------------
void UART_transmitByte(UART_t *port, uint8_t byte);
void UART_init(UART_t *port, RESETS_t *resets, uint32_t baudRate);
void UART_setBaudRate(UART_t *port, uint32_t baudRate);
void UART_transmitBytes(UART_t *port, uint8_t *byte, size_t length);
int UART_receiveByte(UART_t *port, uint8_t *receiveBuffer, uint32_t *receiveBufferIndex, uint32_t receiveBufferSize);
int UART_receiveBytes(UART_t *port, uint8_t *receiveBuffer, uint32_t *receiveBufferIndex, uint32_t receiveBufferSize);
void UART_writeBitFIFO(UART_t *port, bool enable);
void UART_writeBitCR(UART_t *port, bool enable);

#endif
