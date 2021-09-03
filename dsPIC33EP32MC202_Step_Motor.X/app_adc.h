/* 
 * File:   app_adc.h
 * Author: A41547
 *
 * Created on September 2, 2021, 7:56 PM
 */

#ifndef APP_ADC_H
#define	APP_ADC_H

#include "mcc_generated_files/system.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    /* The application's current state */
    uint16_t i_a;
    uint16_t i_b;
    uint16_t u_a;
    uint16_t u_b;
    uint16_t spd;
    uint16_t u_dc;
} APP_ADC_VALUES;

extern APP_ADC_VALUES adc_value;

void APP_ADC_Initialize ( void );
void APP_ADC_Tasks ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* APP_ADC_H */

