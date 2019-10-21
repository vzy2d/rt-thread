#include "platform.h"

static volatile uint8_t *uart = (void *)UART0_CTRL_ADDR;

#define UARTLITE_MMIO 0x40600000

#define UARTLITE_RX_FIFO  0x0
#define UARTLITE_TX_FIFO  0x4
#define UARTLITE_STAT_REG 0x8
#define UARTLITE_CTRL_REG 0xc

#define UARTLITE_RST_FIFO 0x03
#define UARTLITE_TX_FULL  0x08
#define UARTLITE_RX_VALID 0x01

// #define REG_QUEUE     0
// #define REG_LINESTAT  5
// #define REG_STATUS_RX 0x01
// #define REG_STATUS_TX 0x20

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline uint64_t ind(uintptr_t addr) { return *(volatile uint64_t *)addr; }

static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }
static inline void outw(uintptr_t addr, uint16_t data) { *(volatile uint16_t *)addr = data; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }
static inline void outd(uintptr_t addr, uint64_t data) { *(volatile uint64_t *)addr = data; }

void uart_init(void) {
  outb(UARTLITE_MMIO + UARTLITE_CTRL_REG, UARTLITE_RST_FIFO);
}

void uart_putc(uint8_t ch) {
  if (ch == '\n') uart_putc('\r');

  while (inb(UARTLITE_MMIO + UARTLITE_STAT_REG) & UARTLITE_TX_FULL);
  outb(UARTLITE_MMIO + UARTLITE_TX_FIFO, ch);
}

int uart_getc(void) {
  if (inb(UARTLITE_MMIO + UARTLITE_STAT_REG) & UARTLITE_RX_VALID)
    return inb(UARTLITE_MMIO + UARTLITE_RX_FIFO);
  return -1;
}


// void uart_putc(uint8_t ch) {
//   while ((uart[REG_LINESTAT] & REG_STATUS_TX) == 0);
//   uart[REG_QUEUE] = ch;
//   if (ch == '\n') uart_putc('\r');
// }

// int uart_getc(void) {
//   if (uart[REG_LINESTAT] & REG_STATUS_RX) {
//     return uart[REG_QUEUE];
//   }
//   return -1;
// }
