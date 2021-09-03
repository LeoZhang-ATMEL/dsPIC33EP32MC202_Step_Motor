
/*
 * \file EEPROM_driver.h
 * \brief Header file containing function headers for EEPROM API Function Library with MCC Foundation Services
 * \brief v4.00
 * \author m16133
 * \date Mar 2020
 *
 * @see www.microchip.com
 */
 /**
  Generated Header File

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

#ifndef EEPROM_H
#define	EEPROM_H

#include <stdint.h>
    
#define PAGESIZE (8)

typedef struct
{
    uint8_t *data;
    uint8_t *dataCount;
}   sequentialBuffer_t;

void EEPROM_SetDeviceAddress        (uint8_t MSBAddress);

void EEPROM_ResetDeviceAddress      ();

uint8_t EEPROM_ReadOneByte          (uint8_t address);

void EEPROM_PageWrite               (uint8_t writeAddress, uint8_t * data);

uint8_t EEPROM_SequentialRead       ( uint8_t readAddress, uint8_t * data, uint8_t count);

#endif
