/*
 * File:   main_adc.c
 * Author: Leo
 *
 * Created on September 2, 2021, 8:39 PM
 */
#include "mcc_generated_files/mcc.h"
#include "app_adc.h"

void APP_MAIN_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    // Read 16 bytes from EEPROM from address 0
    //uint8_t rdata[16];
    //EEPROM_SequentialRead(0, rdata, 16);
    
    /* Set PWM_EN High after init */
    IO_PWM_EN_SetHigh();

    return;
}
void test_func(void)
{
    IO_EN_C_GetValue();
    IO_T_V_GetValue();
    IO_FAULT1_GetValue();
    IO_FAULT2_GetValue();
    IO_DIR_C_GetValue();
    return;
}

void APP_MAIN_Tasks ( void )
{
    // Read ADC
    // adc_value.i_a
    // adc_value.i_b
    
    // Check if EN == 0
    if (IO_EN_C_GetValue() == 1) {
        _LATB12 = 0;
        _LATB13 = 0;
        _LATB14 = 0;
        _LATB15 = 0;
        return;
    }
    // Check the Temperature and Fault from driver
    if (!IO_T_V_GetValue() || !IO_FAULT1_GetValue() || !IO_FAULT2_GetValue()) {
        // Disable PWM
        _LATB12 = 0;
        _LATB13 = 0;
        _LATB14 = 0;
        _LATB15 = 0;
        return;
    }
    
    if (adc_value.i_a > 512) {
        // Disable PWM
        _LATB12 = 0;
        _LATB13 = 0;
        _LATB14 = 0;
        _LATB15 = 0;
        return;
    }
    
    if (IO_DIR_C_GetValue()) {
        _LATB12 = 0;
        _LATB13 = 0;
        _LATB14 = 1;
        _LATB15 = 1;
    } else {
        _LATB12 = 1;
        _LATB13 = 1;
        _LATB14 = 0;
        _LATB15 = 0;
    }
    
    // Write EEPROM at address 0 with 8 bytes
    // uint8_t data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    // EEPROM_PageWrite(0x00, data);
    
    // Set PWM Duty
}