/*
 *  1-WireCRC.h
 *
 *  Author: Kestutis Bivainis
 *
 *  Original source code from
 *  http://kazus.ru/forums/showthread.php?t=100566
 */

#ifndef _1_WIRE_H
#define _1_WIRE_H

#include <stdint.h>
#include <lpc_types.h>

#define ONE_WIRE_PIN  3
#define ONE_WIRE_PORT 0

// in microseconds
#define Time_Pulse_Delay_Low  10
#define Time_Pulse_Delay_High 60
#define Time_Reset_Low        480
#define Time_After_Reset      350
#define Time_Hold_Down        2

#define One_Wire_Read_ROM    0x33
#define One_Wire_Skip_ROM    0xCC
#define One_Wire_Search_ROM  0xF0
#define One_Wire_Match_ROM   0x55

#define One_Wire_Success       0x00
#define One_Wire_Error_No_Echo 0x01
#define One_Wire_Bus_Low_Error 0x02
#define One_Wire_Device_Busy   0x03
#define One_Wire_CRC_Error     0x04

bool One_Wire_Pin_Read(void);
void One_Wire_Pin_Low(void);
void One_Wire_Pin_High(void);

uint8_t One_Wire_Reset(void);

void One_Wire_Write_Bit(uint8_t Bit);
void One_Wire_Write_Byte(uint8_t Byte);
uint8_t One_Wire_Read_Bit(void);
uint8_t One_Wire_Read_Byte(void);

#endif
