/*
 *  2_5_digits_indicator.h
 *
 *  Author: Kestutis Bivainis
 */

#ifndef _2_5_DIGITS_INDICATOR_H
#define _2_5_DIGITS_INDICATOR_H

#include <stdint.h>

// SPI0
#define INDICATOR_SCLK_Pin 15
#define INDICATOR_MOSI_Pin 16

void Init_2_5_Digits_Indicator(void);

void IndicatorClear(void);
void IndicatorDisplayDec(uint8_t val);
void IndicatorDisplayDecLZ(uint8_t val);// with leading zero
void IndicatorDisplayHex(uint16_t val);
void IndicatorDisplayHexLZ(uint16_t val);// with leading zero
void IndicatorDisplayMinus(void);

#endif
