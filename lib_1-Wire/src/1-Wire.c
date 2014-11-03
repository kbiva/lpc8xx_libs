/*
 *  1-Wire.c
 *
 *  Author: Kestutis Bivainis
 *
 *  Original source code from
 *  http://kazus.ru/forums/showthread.php?t=100566
 */

#include "chip.h"
#include "1-Wire.h"

// microseconds delay on MRT channel 1 for 12Mhz clock
#define DWT_Delay(us) (Chip_MRT_SetInterval(LPC_MRT_CH1,(us*12-3)))

bool One_Wire_Pin_Read(void) {

  Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT,ONE_WIRE_PORT,ONE_WIRE_PIN);
  return Chip_GPIO_GetPinState(LPC_GPIO_PORT,ONE_WIRE_PORT,ONE_WIRE_PIN);
}

void One_Wire_Pin_Low(void) {

  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,ONE_WIRE_PORT,ONE_WIRE_PIN);
  Chip_GPIO_SetPinState(LPC_GPIO_PORT,ONE_WIRE_PORT,ONE_WIRE_PIN,0);
}

void One_Wire_Pin_High(void) {

  Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT,ONE_WIRE_PORT,ONE_WIRE_PIN);
}

uint8_t One_Wire_Reset(void) {

  uint8_t tmp;
  if((One_Wire_Pin_Read())==0)
    return One_Wire_Bus_Low_Error;
  One_Wire_Pin_Low();
  DWT_Delay(Time_Reset_Low);
  One_Wire_Pin_High();
  DWT_Delay(Time_Pulse_Delay_High);
  if (One_Wire_Pin_Read())
    tmp=One_Wire_Error_No_Echo;
  else
    tmp=One_Wire_Success;
  One_Wire_Pin_High();
  DWT_Delay(Time_After_Reset);
  return tmp;
}

void One_Wire_Write_Byte(uint8_t Byte) {

  uint8_t cnt;
  for(cnt=0;cnt!=8;cnt++)
    One_Wire_Write_Bit(Byte&(1<<cnt));
}

void One_Wire_Write_Bit(uint8_t Bit) {

  One_Wire_Pin_Low();
  if(Bit) {
    DWT_Delay(Time_Pulse_Delay_Low);
    One_Wire_Pin_High();
    DWT_Delay(Time_Pulse_Delay_High);
  }
  else {
    DWT_Delay(Time_Pulse_Delay_High);
    One_Wire_Pin_High();
    DWT_Delay(Time_Pulse_Delay_Low);
  }
}

uint8_t One_Wire_Read_Byte(void) {

  uint8_t tmp=0;
  uint8_t cnt;
  for(cnt=0;cnt!=8;cnt++)
    if(One_Wire_Read_Bit())
      tmp|=(1<<cnt);
  DWT_Delay(Time_Pulse_Delay_High);
  return tmp;
}

uint8_t One_Wire_Read_Bit(void) {

  uint8_t tmp;
  One_Wire_Pin_Low();
  DWT_Delay(Time_Hold_Down);
  One_Wire_Pin_High();
  DWT_Delay(Time_Pulse_Delay_Low);
  if(One_Wire_Pin_Read())
    tmp = 1;
  else
    tmp = 0;
  DWT_Delay(Time_Pulse_Delay_High);
  return tmp;
}
