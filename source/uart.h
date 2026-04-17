#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>

#define TXFF_MASK (0x00000001 << 5)
#define FEN_MASK (0x00000001 << 4)

typedef struct{
    volatile uint32_t UART_DR;          // 0x000 Data Register
    volatile uint32_t UART_SR;          // 0x004 Recieve Status Register (error message)
    volatile uint32_t RESERVED0[4];     // occupy 16 bytes
    volatile uint32_t UART_FR;          // 0x018 flag register
    volatile uint32_t RESERVED1;        // occupy byte
    volatile uint32_t UART_ILPR;        // 0x020 low-power counter register
    volatile uint32_t UART_IBRD;        // 0x024 integer baud rate
    volatile uint32_t UARTFBRD;         // 0x028 fractional baud rate
    volatile uint32_t UART_LCR_H;       // 0x02c line control register
    volatile uint32_t UART_CR;          // 0x030 Control Register
    volatile uint32_t UART_IFLS;        // 0x034 interrupt FIFO
    volatile uint32_t UART_IMSC;        // 0x038 interrupt mask set
    volatile uint32_t UART_RIS;         // 0x03c Raw interrupt status register
    volatile uint32_t UART_MIS;         // 0x040 Masked Interrupt status register
    volatile uint32_t UART_ICR;         // 0x044 Interrupt clear register
    volatile uint32_t UART_DMACR;       // 0x048 DMA control Register
    volatile uint32_t UART_PERIPHID0;   // peripherals
    volatile uint32_t UART_PERIPHID1;
    volatile uint32_t UART_PERIPHID2;
    volatile uint32_t UART_PERIPHID3;
    volatile uint32_t UART_PCELLID0;    // PCELL?
    volatile uint32_t UART_PCELLID1;
    volatile uint32_t UART_PCELLID2;
    volatile uint32_t UART_PCELLID3;
} UART_t;

#endif
