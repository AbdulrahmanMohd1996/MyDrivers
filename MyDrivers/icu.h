/*
 * icu.h
 *
 *  Created on: Jan 23, 2020
 *      Author: my laptop
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum
{
	NO_CLOCK=0,
	CPU_CLOCK=1,
	CPU_CLOCK_BY8=2,
	CPU_CLOCK_BY64=3,
	CPU_CLOCK_BY256=4,
	CPU_CLOCK_BY1024=5,
	EXTERNAL_CLOCK_FALLING=6,
	EXTERNAL_CLOCK_RISSING=7
}clock;

typedef enum
{
	FALLING=0,
	RISSING=1
}icu_edge;

typedef struct
{
	clock clockSettings:8;
	icu_edge detectEdge:1;
}icu_settings;


typedef enum
{
	DUTY_CYCLE=0,
	FREQUENCY=1,
	PERIOD=2
}measurments;


#define ICU_AT_RISSING()   SET_BIT(TCCR1B,ICES1)
#define ICU_AT_FALLING()   CLEAR_BIT(TCCR1B,ICES1)


#define ICU_REG_VAL       					(ICR1)
#define TIMER_TICKS       					(TCNT1)
#define ENBLE_ICU_INTERRUPT()         		SET_BIT(TIMSK,TICIE1);
#define DISABLE_ICU_INTERRUPT()             CLEAR_BIT(TIMSK,TICIE1)
#define RESET_TIMER()						TCNT1=0
#define PAUSE_TIMER1()                      TCCR1B&=~(0X07)
#define CLEAR_ICU_FALG()                      TIFR|=(1<<ICF1)

void ICU_Init(icu_settings *a_settings_Ptr);
uint32 ICU_Read(measurments a_val,icu_settings *a_settings_Ptr);
void ICU_SetCallbackFunc(void (a_func_Ptr)(void));
void ICU_Deinit(void);

#endif /* ICU_H_ */
