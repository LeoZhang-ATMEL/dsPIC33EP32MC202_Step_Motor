/*
 * File:   main_adc.c
 * Author: Leo
 *
 * Created on September 2, 2021, 8:39 PM
 */
#include "app_adc.h"
#include "mcc_generated_files/mcc.h"

typedef enum
{
    APP_ADC_INIT=0,
    APP_ADC1_SAMPLE_I_A,
    APP_ADC1_SAMPLE_I_A_READY,
    APP_ADC2_SAMPLE_I_B,
    APP_ADC2_SAMPLE_I_B_READY,
    APP_ADC3_SAMPLE_U_A,
    APP_ADC3_SAMPLE_U_A_READY,
    APP_ADC4_SAMPLE_U_B,
    APP_ADC4_SAMPLE_U_B_READY,
    APP_ADC5_SAMPLE_SPD,
    APP_ADC5_SAMPLE_SPD_READY,
    APP_ADC6_SAMPLE_U_DC,
    APP_ADC6_SAMPLE_U_DC_READY,
    APP_ADC_SAMPLE_DONE,
    APP_ADC_FAULT_RECOVER,
    APP_ADC_IDLE,
} APP_ADC_STATES;

typedef struct
{
    /* The application's current state */
    APP_ADC_STATES state;
    /* The temporary variable to store the ADC data */
    APP_ADC_VALUES adc;
} APP_ADC_DATA;

APP_ADC_DATA app_adcData;

APP_ADC_VALUES adc_value;

#define ADC_THRESHOLD_MAX (uint16_t)((float)1024 * 0.8 / 3.3)
#define ADC_THRESHOLD_DELTA (uint16_t)((float)1024 * 0.2 / 3.3)

void APP_ADC_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    ADC1_Enable();
    app_adcData.state = APP_ADC_INIT;
}

void APP_ADC_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( app_adcData.state )
    {
        /* Application's initial state. */
        case APP_ADC_INIT:
        {
            app_adcData.state = APP_ADC1_SAMPLE_I_A;
            break;
        }

        case APP_ADC1_SAMPLE_I_A:
        {
            ADC1_ChannelSelect(channel_AN_I_A);
            ADC1_SoftwareTriggerEnable();
            app_adcData.state = APP_ADC1_SAMPLE_I_A_READY;
            break;
        }
        /* I-A */
        case APP_ADC1_SAMPLE_I_A_READY:
        {
            if (!ADC1_IsConversionComplete(channel_AN_I_A)) {
                break;
            }
            app_adcData.adc.i_a = ADC1_ConversionResultGet(channel_AN_I_A);
            app_adcData.state = APP_ADC2_SAMPLE_I_B;
            break;
        }
        /* I-B */
        case APP_ADC2_SAMPLE_I_B:
        {
            ADC1_ChannelSelect(channel_AN_I_B);
            ADC1_SoftwareTriggerEnable();
            app_adcData.state = APP_ADC2_SAMPLE_I_B_READY;
            break;
        }

        case APP_ADC2_SAMPLE_I_B_READY:
        {
            if (!ADC1_IsConversionComplete(channel_AN_I_B)) {
                break;
            }
            app_adcData.adc.i_b = ADC1_ConversionResultGet(channel_AN_I_B);
            app_adcData.state = APP_ADC3_SAMPLE_U_A;
            break;
        }
        /* U-A */
        case APP_ADC3_SAMPLE_U_A:
        {
            ADC1_ChannelSelect(channel_AN_U_A);
            ADC1_SoftwareTriggerEnable();
            app_adcData.state = APP_ADC3_SAMPLE_U_A_READY;
            break;
        }

        case APP_ADC3_SAMPLE_U_A_READY:
        {
            if (!ADC1_IsConversionComplete(channel_AN_U_A)) {
                break;
            }
            app_adcData.adc.u_a = ADC1_ConversionResultGet(channel_AN_U_A);
            app_adcData.state = APP_ADC4_SAMPLE_U_B;
            break;
        }
        /* U-B */
        case APP_ADC4_SAMPLE_U_B:
        {
            ADC1_ChannelSelect(channel_AN_U_B);
            ADC1_SoftwareTriggerEnable();
            app_adcData.state = APP_ADC4_SAMPLE_U_B_READY;
            break;
        }
        case APP_ADC4_SAMPLE_U_B_READY:
        {
            if (!ADC1_IsConversionComplete(channel_AN_U_B)) {
                break;
            }
            app_adcData.adc.u_b = ADC1_ConversionResultGet(channel_AN_U_B);
            app_adcData.state = APP_ADC5_SAMPLE_SPD;
            break;
        }
        /* SPD */
        case APP_ADC5_SAMPLE_SPD:
        {
            ADC1_ChannelSelect(channel_AN_SPD);
            ADC1_SoftwareTriggerEnable();
            app_adcData.state = APP_ADC5_SAMPLE_SPD_READY;
            break;
        }
        case APP_ADC5_SAMPLE_SPD_READY:
        {
            if (!ADC1_IsConversionComplete(channel_AN_SPD)) {
                break;
            }
            app_adcData.adc.spd = ADC1_ConversionResultGet(channel_AN_SPD);
            app_adcData.state = APP_ADC6_SAMPLE_U_DC;
            break;
        }
        /* U-DC */
        case APP_ADC6_SAMPLE_U_DC:
        {
            ADC1_ChannelSelect(channel_AN_U_DC);
            ADC1_SoftwareTriggerEnable();
            app_adcData.state = APP_ADC6_SAMPLE_U_DC_READY;
            break;
        }
        case APP_ADC6_SAMPLE_U_DC_READY:
        {
            if (!ADC1_IsConversionComplete(channel_AN_U_DC)) {
                break;
            }
            app_adcData.adc.u_dc = ADC1_ConversionResultGet(channel_AN_U_DC);
            app_adcData.state = APP_ADC_SAMPLE_DONE;
            break;
        }
        case APP_ADC_SAMPLE_DONE:
        {
            adc_value.i_a = app_adcData.adc.i_a;
            adc_value.i_b = app_adcData.adc.i_b;
            adc_value.u_a = app_adcData.adc.u_a;
            adc_value.u_b = app_adcData.adc.u_b;
            adc_value.spd = app_adcData.adc.spd;
            adc_value.u_dc = app_adcData.adc.u_dc;
            app_adcData.state = APP_ADC1_SAMPLE_I_A;
            break;
        }

        case APP_ADC_FAULT_RECOVER:
        {
            app_adcData.state = APP_ADC1_SAMPLE_I_A;
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
