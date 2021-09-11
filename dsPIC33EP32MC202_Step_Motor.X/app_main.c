/*
 * File:   main_adc.c
 * Author: Leo
 *
 * Created on September 2, 2021, 8:39 PM
 */
#include "mcc_generated_files/mcc.h"
#include "app_adc.h"

// Counter of the PIN16 (PULSE_C) for negative edge
volatile uint32_t pulse_c = 0;

// Timer ticks counter for 50us period
volatile uint32_t app_ticks = 0;

void Timer_50us_Handler(void)
{
    app_ticks++;
}

void APP_PWM_Gen1Event_CallBack(void)
{
    // Add Application code here
    //IO_RB4_Toggle();
}

void APP_ADC1_Callback(void)
{
    //IO_RB4_Toggle();
    adc_value.i_a = ADC1BUF0;   // Read the AN0/RA0
    adc_value.i_b = ADC1BUF1;   // Read the AN1/RA1
    adc_value.u_a = ADC1BUF2;   // Read the AN2/RB0
    adc_value.u_a = ADC1BUF3;   // Read the AN3/RB1
    adc_value.spd = ADC1BUF4;   // Read the AN4/RB2
    adc_value.u_dc = ADC1BUF5;   // Read the AN5/RB3
    return;
} 

void APP_MAIN_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    // Read 16 bytes from EEPROM from address 0
    //uint8_t rdata[16];
    //EEPROM_SequentialRead(0, rdata, 16);
    
    /* Set PWM_EN High after init */
    IO_PWM_EN_SetHigh();
    TMR5_SetInterruptHandler(Timer_50us_Handler);
    PWM_SetGenerator1InterruptHandler(APP_PWM_Gen1Event_CallBack);
    ADC1_SetInterruptHandler(APP_ADC1_Callback);
    ADC1_Enable();
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
        PWM_Disable();
        return;
    }
    // Check the Temperature and Fault from driver
    if (!IO_T_V_GetValue() || !IO_FAULT1_GetValue() || !IO_FAULT2_GetValue()) {
        // Disable PWM
        PWM_Disable();
        return;
    }
    
    if (adc_value.i_a > 512) {
        // Disable PWM
        PWM_Disable();
        return;
    }
    // PWM_GENERATOR_1 = Motor A
    // PWM_GENERATOR_2 = Motor B
    // PWM Tick was 16.4 ns (Tcy)
    // Period default value was 0xBE1/3041 (50us)
    // PWM_DutyCycleSet(PWM_GENERATOR_1, 3041/2); // Set to 50% duty cycle
    // PWM_DutyCycleSet(PWM_GENERATOR_2, 3041/2); // Set to 50% duty cycle
    
    PWM_Enable();
    PWM_DutyCycleSet(PWM_GENERATOR_1, 3041/2);
    /* 1 seconds timeout */
    if (app_ticks >= 20000) {
        app_ticks = 0;
    }
    /*
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
    */
    // Write EEPROM at address 0 with 8 bytes
    // uint8_t data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    // EEPROM_PageWrite(0x00, data);
    
    // Set PWM Duty
}