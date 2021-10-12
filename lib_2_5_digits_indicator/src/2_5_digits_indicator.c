/*
 *  2_5_digits_indicator.c
 *
 *  Author: Kestutis Bivainis
 */

#include "chip.h"
#include "2_5_digits_indicator.h"

//                           0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F
static uint8_t digits[] = {0x88,0xDB,0xA2,0x92,0xD1,0x94,0x84,0xDA,0x80,0x90,0xC0,0x85,0xAC,0x83,0xA4,0xE4,
//                          10   11   12   13   14   15   16   17   18   19   1A   1b   1C   1d   1E   1F
                           0x08,0x5B,0x22,0x12,0x51,0x14,0x04,0x5A,0x00,0x10,0x40,0x05,0x2C,0x03,0x24,0x64};

static void GPIO_Configuration(uint8_t SCLK_Pin,uint8_t MOSI_Pin) {

  // init SWM
  Chip_SWM_Init();
  Chip_SWM_MovablePinAssign(SWM_SPI0_SCK_IO, SCLK_Pin);
  Chip_SWM_MovablePinAssign(SWM_SPI0_MOSI_IO, MOSI_Pin);
  Chip_SWM_Deinit();

  // init SPI0
  Chip_SPI_Init(LPC_SPI0);
  Chip_SPI_ConfigureSPI(LPC_SPI0,SPI_MODE_MASTER|
                                 SPI_CLOCK_CPHA0_CPOL0|
                                 SPI_DATA_MSB_FIRST|
                                 SPI_SSEL_ACTIVE_LO);
  LPC_SPI0->DIV = 4;
  Chip_SPI_Enable(LPC_SPI0);
}

static void sendToIndicator(uint16_t word) {

  while ((LPC_SPI0->STAT & SPI_STAT_TXRDY) == 0);

  // 16bits,end of transfer,transmit slave select,receive ignore
  LPC_SPI0->TXDATCTL = SPI_TXCTL_FLEN(16) |
                       SPI_TXDATCTL_EOT |
                       //SPI_TXCTL_DEASSERT_SSEL |
                       SPI_TXDATCTL_ASSERT_SSEL |
                       SPI_TXDATCTL_RXIGNORE |
                       word;
}

void Init_2_5_Digits_Indicator(uint8_t SCLK_Pin,uint8_t MOSI_Pin) {

  GPIO_Configuration(SCLK_Pin,MOSI_Pin);
  Indicator_Clear();
}

void Indicator_Display_Dec(uint8_t val) {

  uint16_t b;
  uint8_t d12;

  b = digits[val % 10];
  b <<= 8;
  d12 = val / 10;
  if (d12 > 9) {
    b |= digits[d12 + 6];
  }
  else if (d12) {
    b |= digits[d12];
  }
  else {
    b |= 0xFF;
  }
  sendToIndicator(b);
}

void Indicator_Display_Dec_LZ(uint8_t val) {

  uint16_t b;
  uint8_t d12;

  b = digits[val % 10];
  b <<= 8;
  d12 = val / 10;
  if (d12 > 9) {
    b |= digits[d12 + 6];
  }
  else {
    b |= digits[d12];
  }
  sendToIndicator(b);
}

void Indicator_Display_Hex(uint16_t val) {

  uint16_t b;

  b = digits[val % 16];
  b <<= 8;

  if (val / 16) {
    b |= digits[val / 16];
  }
  else {
    b |= 0xFF;
  }
  sendToIndicator(b);
}

void Indicator_Display_Hex_LZ(uint16_t val) {

  uint16_t b;

  b = digits[val % 16];
  b <<= 8;
  b |= digits[val / 16];
  sendToIndicator(b);
}

void Indicator_Display_Minus(void) {

  sendToIndicator(0x77F7);
}

void Indicator_Clear(void) {

  sendToIndicator(0xFFFF);
}
