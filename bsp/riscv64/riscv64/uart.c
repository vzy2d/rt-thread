#include "platform.h"

static volatile uint8_t *uart = (void *)UART0_CTRL_ADDR;

#ifndef __NOOP__

#define REG_QUEUE     0
#define REG_LINESTAT  5
#define REG_STATUS_RX 0x01
#define REG_STATUS_TX 0x20

void uart_putc(uint8_t ch) {
  while ((uart[REG_LINESTAT] & REG_STATUS_TX) == 0);
  uart[REG_QUEUE] = ch;
  if (ch == '\n') uart_putc('\r');
}

int uart_getc(void) {
  if (uart[REG_LINESTAT] & REG_STATUS_RX) {
    return uart[REG_QUEUE];
  }
  return -1;
}

#else

#define UARTLITE_RX_FIFO  0x0
#define UARTLITE_TX_FIFO  0x4
#define UARTLITE_STAT_REG 0x8
#define UARTLITE_CTRL_REG 0xc

#define UARTLITE_RST_FIFO 0x03
#define UARTLITE_TX_FULL  0x08
#define UARTLITE_RX_VALID 0x01

void uart_putc(uint8_t ch) {
  while (uart[UARTLITE_STAT_REG] & UARTLITE_TX_FULL);
  uart[UARTLITE_TX_FIFO] = ch;

  if (ch == '\n') uart_putc('\r');

}

int uart_getc(void) {
  if (uart[UARTLITE_STAT_REG] & UARTLITE_RX_VALID)
    return uart[UARTLITE_RX_FIFO];
  return -1;
}

#endif
