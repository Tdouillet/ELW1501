/*
 * File:   extra_fct.c
 * Author: t.douillet
 *
 * Created on August 7, 2024, 1:24 PM
 */


#include "xc.h"
#include "extra_fct.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/system.h"

void WriteComm(uint8_t byte)
{
    CS_SetLow();
    DC_SetLow();
    SPI1_Exchange8bit(byte);
    CS_SetHigh();
}

void WriteData(uint8_t byte)
{
    CS_SetLow();
    DC_SetHigh();
    SPI1_Exchange8bit(byte);
    CS_SetHigh();
}

void Screen_SPI_Init(){
    
    //Unlock commands
    WriteComm(0xFD);
    WriteComm(0x12); 
        
    //Display on
    WriteComm(0xAE); 
    
    //Set contrast
    WriteComm(0x81);
    WriteComm(0x0F);
    
    //Remap
    WriteComm(0xA0); 
    WriteComm(0x40);
    
    //Set clock
    WriteComm(0xB3); 
    WriteComm(0x00);
    
    //Set MUX ratio
    WriteComm(0xA8); 
    WriteComm(0xFF); 
    
    //Set offset
    WriteComm(0xA2);
    WriteComm(0x00);
    
    //Set Line
    WriteComm(0xA1); 
    WriteComm(0x00); 
    //0x5C,
    
    
    
    
    
    //Invert display
    //0xA7,
    
    //SetGPIO
    WriteComm(0xB5); 
    WriteComm(0x10);
    
    //Enable internal VDD regulator
    WriteComm(0xAB); 
    WriteComm(0x01); 
    

            
    //Set Gamma LUT
    WriteComm(0xB9); 

    
    
    //Set phase length
    WriteComm(0xB1);
    WriteComm(0x32); 
    
    //Set pre-charge voltage
    WriteComm(0xBC);
    WriteComm(0x17);
    
    //Set second pre-charge
    WriteComm(0xB6);
    WriteComm(0x01);
    
    //Set VCOMH Select level
    WriteComm(0xBE);
    WriteComm(0x05);
    
    //Voltage selections
    WriteComm(0xD5);
    WriteComm(0x60);
    
    //Reset display mode
    WriteComm(0xA4);
    
    
}

void WriteRam(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2){
    
    WriteComm(0x15); 
    WriteComm(x1); 
    WriteComm(x2);
    
    WriteComm(0x75); 
    WriteComm(y1);
    WriteComm(y2);
    
}

void Fill(uint8_t byte){
    for (uint32_t i = 0; i<8192; i++){
        WriteData(byte);
    }
}

void Fill_Tab(uint8_t tab[]){
    WriteRam(tab[0],tab[1],tab[2],tab[3]);
    
    uint8_t offsetx = tab[1]-tab[0];
    uint8_t offsety = tab[3]-tab[2];
    
    uint32_t size = (offsetx+1)*(offsety+1);
    
    for (uint32_t i = 0; i<size; i++){
        WriteData(tab[i]);
    }
}