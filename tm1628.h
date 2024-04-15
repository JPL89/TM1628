// @File        TM1628.H	 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		14/04/24
//
//
// Copyright (C) 2024  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef TM1628_H_
#define TM1628_H_

#include <xc.h>

#define TM1628_CLK PORTAbits.RA0
#define TM1628_DIO PORTAbits.RA1
#define TM1628_STB PORTAbits.RA2

#define TM1628_CLK_TRIS TRISAbits.RA0
#define TM1628_DIO_TRIS TRISAbits.RA1
#define TM1628_STB_TRIS TRISAbits.RA2

// COMMANDS
#define TM1628_COMMAND1 0x00
#define TM1628_COMMAND2 0x40
#define TM1628_COMMAND3 0xC0
#define TM1628_COMMAND4 0x80

// COMMAND1 BYTE
#define TM1628_COMMAND2_DISPLAY_MODE_6GRIDS_12SEGMENTS 0x02
#define TM1628_COMMAND2_DISPLAY_MODE_7GRIDS_11SEGMENTS 0x03

// COMMAND2 BYTE
#define TM1628_COMMAND2_WRITE_DATA 0x00
#define TM1628_COMMAND2_READ_KEY 0x02
#define TM1628_COMMAND2_FIXED_ADDRESS 0x04
#define TM1628_COMMAND2_MODE_NORMAL 0x00
#define TM1628_COMMAND2_MODE_TEST 0x01

// COMMAND3 BYTE
#define TM1628_COMMAND3_ADDRESS0 0x00
#define TM1628_COMMAND3_ADDRESS1 0x01
#define TM1628_COMMAND3_ADDRESS2 0x02
#define TM1628_COMMAND3_ADDRESS3 0x03
#define TM1628_COMMAND3_ADDRESS4 0x04
#define TM1628_COMMAND3_ADDRESS5 0x05
#define TM1628_COMMAND3_ADDRESS6 0x06
#define TM1628_COMMAND3_ADDRESS7 0x07
#define TM1628_COMMAND3_ADDRESS8 0x08
#define TM1628_COMMAND3_ADDRESS9 0x09
#define TM1628_COMMAND3_ADDRESS10 0x10
#define TM1628_COMMAND3_ADDRESS11 0x11
#define TM1628_COMMAND3_ADDRESS12 0x12
#define TM1628_COMMAND3_ADDRESS13 0x13


// COMMAND4 BYTE
#define TM1628_COMMAND4_PULSE_1_16 0x00
#define TM1628_COMMAND4_PULSE_2_16 0x01
#define TM1628_COMMAND4_PULSE_4_16 0x02
#define TM1628_COMMAND4_PULSE_10_16 0x03
#define TM1628_COMMAND4_PULSE_11_16 0x04
#define TM1628_COMMAND4_PULSE_12_16 0x05
#define TM1628_COMMAND4_PULSE_13_16 0x06
#define TM1628_COMMAND4_PULSE_14_16 0x07
#define TM1628_COMMAND4_DISPLAY_ON 0x08

void TM1628_Write(unsigned char data);
void TM1628_Command(unsigned char data);
void TM1628_Data(unsigned char address, unsigned char data);
void TM1628_Clear(void);
void TM1628_Init(void);

unsigned char TM1628_GetKey(void);
unsigned char TM1628_Read(void);

#endif /*  */
