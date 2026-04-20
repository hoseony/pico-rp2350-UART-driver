#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>

#define UART_FR_TXFF_MASK (0x00000001u << 5)
#define UART_FR_RXFE_MASK (0x00000001u << 4)
#define UART_LCR_H_FEN_MASK (0x00000001u << 4)

#define UART0_BASE 0x40070000u
#define UART1_BASE 0x40078000u

#define UART0 ((UART_t *)UART0_BASE)
#define UART1 ((UART_t *)UART1_BASE)

#define UART_CR_RXE_MASK (0x00000001u << 9) // receive bit (1 to receive)
#define UART_CR_TXE_MASK (0x00000001u << 8) // transmit bit (1 to transmit)
#define UART_CR_EN_MASK (0x00000001u << 0) // enable UART (1 to enable)

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
/*    volatile uint32_t UART_PERIPHID0;   // peripherals
    volatile uint32_t UART_PERIPHID1;
    volatile uint32_t UART_PERIPHID2;
    volatile uint32_t UART_PERIPHID3;
    volatile uint32_t UART_PCELLID0;    // PCELL?
    volatile uint32_t UART_PCELLID1;
    volatile uint32_t UART_PCELLID2;
    volatile uint32_t UART_PCELLID3;*/
} UART_t;


#define RESET_UART0_MASK (0x00000001u << 26)
#define RESET_UART1_MASK (0x00000001u << 27)
#define RESET_BASE 0x40020000u
#define RESETS ((RESETS_t *)RESET_BASE)

typedef struct {
    volatile uint32_t RESET; // 0x40020000
    volatile uint32_t WDSEL;
    volatile uint32_t RESET_DONE;
} RESETS_t;

// ------------------------------

#define GPIO_UART_FUNCT 2 
#define BANK_IO_BASE 0x40028000u

typedef struct {
    volatile uint32_t GPIO0_STATUS; //0x40028000
    volatile uint32_t GPIO0_CTRL;
    volatile uint32_t GPIO1_STATUS;
    volatile uint32_t GPIO1_CTRL;
} GPIO_t;

#endif
