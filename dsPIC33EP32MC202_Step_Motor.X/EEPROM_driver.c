/**
 * \file EEPROM_driver.c
 * \brief Source file containing implementations for EEPROM API Function Library with MCC foundation services
 * \brief v4.0
 * \author m16133
 * \date Mar 2020
 *
 * @see www.microchip.com
 */
 /**
  Generated Source File

  Company:
    Microchip Technology Inc.

    (c) 2018 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <xc.h>
#include <stdbool.h>
#include <string.h>

#include "EEPROM_driver.h"
#include "mcc_generated_files/i2c1.h"

typedef struct
{
    uint8_t *data;
    uint16_t *dataSize;
}   buffer_t;

uint8_t EEPROM_DEVICE_ADDRESS=0x50;

void EEPROM_SetDeviceAddress(uint8_t MSBAddress)
{
    EEPROM_DEVICE_ADDRESS = (0xA0 | (MSBAddress << 1)) >> 1;
}

void EEPROM_ResetDeviceAddress()
{
    EEPROM_DEVICE_ADDRESS = 0x50;
}

uint8_t EEPROM_ReadOneByte(uint8_t address)
{
    uint8_t data;
    I2C1_MESSAGE_STATUS pstatus;

    I2C1_MasterWrite(&address, 1,  EEPROM_DEVICE_ADDRESS, &pstatus);
    if (pstatus == I2C1_MESSAGE_FAIL) {
        return 0x00;
    }
    while(pstatus == I2C1_MESSAGE_PENDING);
    if (pstatus != I2C1_MESSAGE_COMPLETE) {
        return 0x00;
    }
    
    I2C1_MasterRead(&data, 1,  EEPROM_DEVICE_ADDRESS, &pstatus);
    if (pstatus == I2C1_MESSAGE_FAIL) {
        return 0x00;
    }
    while(pstatus == I2C1_MESSAGE_PENDING);
    if (pstatus != I2C1_MESSAGE_COMPLETE) {
        return 0x00;
    }
    return data;
}

void EEPROM_ByteWrite (uint8_t writeAddress, uint8_t * data)
{   
    uint8_t wdata[2];
    I2C1_MESSAGE_STATUS pstatus;

    wdata[0] = EEPROM_DEVICE_ADDRESS;
    memcpy(wdata + 1, data, 1);
    I2C1_MasterWrite(wdata, 2,  EEPROM_DEVICE_ADDRESS, &pstatus);
    if (pstatus == I2C1_MESSAGE_FAIL) {
        return;
    }
    while(pstatus == I2C1_MESSAGE_PENDING);
    if (pstatus != I2C1_MESSAGE_COMPLETE) {
        return;
    }
    
    return;
}

void EEPROM_PageWrite (uint8_t writeAddress, uint8_t * data)
{   
    uint8_t wdata[PAGESIZE + 1];
    I2C1_MESSAGE_STATUS pstatus;

    wdata[0] = EEPROM_DEVICE_ADDRESS;
    memcpy(wdata + 1, data, PAGESIZE);
    I2C1_MasterWrite(wdata, PAGESIZE + 1,  EEPROM_DEVICE_ADDRESS, &pstatus);
    if (pstatus == I2C1_MESSAGE_FAIL) {
        return;
    }
    while(pstatus == I2C1_MESSAGE_PENDING);
    if (pstatus != I2C1_MESSAGE_COMPLETE) {
        return;
    }
    
    return;
}

uint8_t EEPROM_SequentialRead  (uint8_t readAddress, uint8_t * data, uint8_t count)
{  
    I2C1_MESSAGE_STATUS pstatus;

    I2C1_MasterWrite(&readAddress, 1,  EEPROM_DEVICE_ADDRESS, &pstatus);
    if (pstatus == I2C1_MESSAGE_FAIL) {
        return 0x00;
    }
    while(pstatus == I2C1_MESSAGE_PENDING);
    if (pstatus != I2C1_MESSAGE_COMPLETE) {
        return 0x00;
    }
    
    I2C1_MasterRead(data, count,  EEPROM_DEVICE_ADDRESS, &pstatus);
    if (pstatus == I2C1_MESSAGE_FAIL) {
        return 0x00;
    }
    while(pstatus == I2C1_MESSAGE_PENDING);
    if (pstatus != I2C1_MESSAGE_COMPLETE) {
        return 0x00;
    }
    return 0;
}  


