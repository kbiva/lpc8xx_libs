/*
 *  2_5_digits_indicator.h
 *
 *  Author: Kestutis Bivainis
 */

#ifndef _2_5_DIGITS_INDICATOR_H
#define _2_5_DIGITS_INDICATOR_H

#include <stdint.h>

void Init_2_5_Digits_Indicator(uint8_t SCLK_Pin,uint8_t MOSI_Pin);

void Indicator_Clear(void);
void Indicator_Display_Dec(uint8_t val);
void Indicator_Display_Dec_LZ(uint8_t val);// with leading zero
void Indicator_Display_Hex(uint16_t val);
void Indicator_Display_Hex_LZ(uint16_t val);// with leading zero
void Indicator_Display_Minus(void);

#endif
