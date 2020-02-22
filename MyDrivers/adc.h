/*-------------------------------------------------------------------------------------
 |         [FILE NAME]     <adc.h>    		 									   |
 | 		   [AUTHOR]        <Abdolee>                                                   |
 |         [DATE CREATED]  <Jan 15, 2020>											   |
 |         [DESCRIPTION]   <the H driver file for the ADC>						   |
 |-------------------------------------------------------------------------------------*/


#ifndef ADC_H_
#define ADC_H_

/*************************************************
 *                   INCLUDES                    *
 *************************************************/
#include<avr/io.h>
#include"common_macros.h"
#include"std_types.h"
#include<avr/interrupt.h>
/*************************************************
 *      DEFINITIONS AND STATIC CONFIGRUATION     *
 *************************************************/

/*ADC Channel*/
#define ADC0           0
#define ADC1           1
#define ADC2           2
#define ADC3           3
#define ADC4           4
#define ADC5           5
#define ADC6           6
#define ADC7           7

#define AUTO_TRIGGER                             DISABLE
#define ADC_HIGH_SPEED_MODE                      DISABLE
#define ADC_INTERRUPT		                     DISABLE

#define ADC_VAL_REG                              ADC
/*************************************************
 *         EXTERN/SHARED GLOABAL VARIABLS        *
 *************************************************/


/*************************************************
 *                    ENUMS                      *
 *************************************************/

typedef enum
{
	Aref=0,
	AVCC=1,
	internal_2_56V=3
}refrenceVoltageSettings;

#if AUTO_TRIGGER
typedef enum
{
	FREE_RUNNING_MODE=0,
	ANALOGE_COMPARTOR=1,
	EXT_INT0=2,
	TIMER0_CTC=3,
	TIMER0_OVF=4,
	TIMER1_CTC_B=5,
	TIMER1_OVF=6,
	TIMER1_ICU=7
}autoTriggerModes;
#endif

typedef enum
{
	DIV_BY_2=1,
	DIV_BY_4=2,
	DIV_BY_8=3,
	DIV_BY_16=4,
	DIV_BY_32=5,
	DIV_BY_64=6,
	DIV_BY_128=7,
}preScallers;
/*************************************************
 *              STRUCTURES AND UNIONS            *
 *************************************************/
typedef struct
{
	refrenceVoltageSettings refVolt:2;
	preScallers divBy:8;

	#if AUTO_TRIGGER
	autoTriggerModes autoMode;
	#endif

#if ADC_INTERRUPT
	void(*intFunc_Ptr)(void);
#endif

}ADC_Settings;

/*************************************************
 *              FUNCTION LKE MACROS              *
 *************************************************/
#define ENABLE_ADC()                						ADCSRA|=(1<<ADEN)
#define DISABLE_ADC()               						ADCSRA&=~(1<<ADEN)
#if ADC_INTERRUPT
#define ENABLE_ADC_INT                  					ADCSRA|=(1<<ADIE)
#define DISABLE_ADC_INT                	 					ADCSRA&=~(1<<ADIE)
#endif
#define READ_SENSOR(ADC_VAL,SENSOR_RES,MAX_VOLT)         	(ADC_VAL/(float32)(SENSOR_RES/(MAX_VOLT/1024.0)))
#define SELECT_ADC_CHANNEL(NUMB)                             ADMUX&=~(0x1F);ADMUX|=NUMB
#define START_CONVERSION()                                   ADCSRA|=(1<<ADSC);

/*************************************************
 *          FUNCTION DECLARATION/PROTOTYPE       *
 *************************************************/
void ADC_Init(ADC_Settings* a_settings_Ptr);
uint16 ADC_ReadChannel(uint8 a_channelNumb);
#if ADC_INTERRUPT
void ADC_SetCallBackFunc(void (*a_func_Ptr)(void));
#endif
#endif /* ADC_H_ */
