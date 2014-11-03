/*
 *  usart.c
 *
 *  Author: Kestutis Bivainis
 *
 */

#include "chip.h"
#include "usart.h"
#include <stdio.h>

struct __FILE {int handle;};
FILE __stdout;
FILE __stdin;

void USART0_Init(uint32_t baud) {

  Chip_SWM_Init();
  Chip_SWM_MovablePinAssign(SWM_U0_TXD_O,4);
  Chip_SWM_MovablePinAssign(SWM_U0_RXD_I,0);
  Chip_SWM_Deinit();

  Chip_UART_Init(LPC_USART0);
  Chip_Clock_SetUARTClockDiv(1);
  Chip_UART_SetBaud(LPC_USART0,baud);
  Chip_UART_ConfigData(LPC_USART0,UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1);
  Chip_UART_Enable(LPC_USART0);
}

int fputc(int ch, FILE *f) {

  while (!(Chip_UART_GetStatus(LPC_USART0) & UART_STAT_TXRDY));
  Chip_UART_SendByte(LPC_USART0,ch);
  return ch;
}

int fgetc(FILE *f) {

  while (!(Chip_UART_GetStatus(LPC_USART0) & UART_STAT_RXRDY));
  return ((int)(Chip_UART_ReadByte(LPC_USART0)));
}
