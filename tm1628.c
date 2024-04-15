// @File        TM1628.C	 		
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

#include "tm1628.h"

void TM1628_Command(unsigned char data)
{
	TM1628_STB = 0;
	TM1628_Write(data);	
	TM1628_STB = 1;
}

//  TM1628 DATA TRANSMISSION
//  STB____                                         ____
//         |_______________________________________|
//       
//
//  DIN ---B0--B1--B2--B3--B4--B5--B6--B7----------------
//
//  CLK___    __   __   __   __   __   __   _____________                     
//        |  |  | |  | |  | |  | |  | |  | |
//         ---  ---  ---  ---  ---  ---  ---
void TM1628_Write(unsigned char data)
{
    for(unsigned char mask = 0x01; mask; mask <<= 1)
    {                        
        if (data & mask) 
            TM1628_DIO = 1; 
        else 
            TM1628_DIO = 0;
		
        TM1628_CLK = 1;
         __asm__ __volatile__("nop");
        TM1628_CLK = 0;
        __asm__ __volatile__("nop");
    }
}

void TM1628_Data(unsigned char address, unsigned char data)
{        
    TM1628_Command(TM1628_COMMAND2|TM1628_COMMAND2_FIXED_ADDRESS);
    
	TM1628_STB = 0;
	TM1628_Write(TM1628_COMMAND3 | address);
	TM1628_Write(data);	
	TM1628_STB = 1;
}

unsigned char TM1628_Read(void)
{
	unsigned char data = 0;
          
    TM1628_DIO_TRIS = 1;
        
    TM1628_DIO = 1;
    
    for (unsigned char mask = 0x01; mask; mask <<= 1) 
    {
        data >>= 1;
        if (TM1628_DIO) data |= 0x80;
			
		TM1628_CLK = 1;
         __asm__ __volatile__("nop");
        TM1628_CLK = 0;
        __asm__ __volatile__("nop");
	}
    
    TM1628_DIO_TRIS = 0;    
    
	return (data);
}

unsigned char TM1628_GetKey(void)
{
    unsigned char key = 0;
               
	TM1628_STB = 0;	
    TM1628_Write(TM1628_COMMAND2|TM1628_COMMAND2_READ_KEY);    
    key |= TM1628_Read() << 0; 
    key |= TM1628_Read() << 1;
    key |= TM1628_Read() << 2;
    key |= TM1628_Read() << 3;
    key |= TM1628_Read() << 4;
    TM1628_STB = 1;             
    
	return key;
}

void TM1628_Clear(void)
{
    for(unsigned char i=0; i<14; i++) TM1628_Data(i, 0x00);
}

void TM1628_Init(void)
{
    TM1628_CLK_TRIS = 0;
    TM1628_DIO_TRIS = 0;
    TM1628_STB_TRIS = 0;
	
    TM1628_CLK = 0;
    TM1628_STB = 1;
    
    TM1628_Command( TM1628_COMMAND1|TM1628_COMMAND2_DISPLAY_MODE_6GRIDS_12SEGMENTS);
    TM1628_Command( TM1628_COMMAND2|TM1628_COMMAND2_FIXED_ADDRESS);
    TM1628_Command( TM1628_COMMAND3|TM1628_COMMAND3_ADDRESS0);
    TM1628_Command( TM1628_COMMAND4|TM1628_COMMAND4_DISPLAY_ON|TM1628_COMMAND4_PULSE_14_16);
    
    // When IC power is applied for the first time, the contents of the Display
    // RAM is not defined; thus, it is strongly suggested that the contents of the
    // Display RAM must be cleared during the initial setting.
    TM1628_Clear();
}
