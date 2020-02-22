
#include"icu.h"
static float64 GetFreq(icu_settings* a_icuSittings_Ptr);

static volatile void (*g_ISR_Ptr)(void)=NULL_PTR;


volatile uint8 flag=0;


ISR(TIMER1_CAPT_vect)
{
	if(g_ISR_Ptr!=(NULL_PTR))
	{
		g_ISR_Ptr();
	}

}




void ICU_Init(icu_settings *a_settings_Ptr)
{
	CLEAR_BIT(DDRD,PD6);
	TCCR1A=(3<<FOC1B);
	TCCR1B=(a_settings_Ptr->detectEdge<<ICES1)|a_settings_Ptr->clockSettings;
}


uint32 ICU_Read(measurments a_val,icu_settings *a_settings_Ptr)
{
	volatile uint16 g_T1=0;   //FIRST PULSE
	volatile uint16 g_T2=0;   // FIRST WAVE (HIGH AND LOW)
	volatile uint16 g_T3=0;   // FIRST WAVE +SECOND PULSE
	CLEAR_ICU_FALG();
	while((TIFR&(1<<ICF1))==0);
	RESET_TIMER();
	ICU_AT_FALLING();
	CLEAR_ICU_FALG();
	(READ_BIT(TIFR,TOV1)==1)?SET_BIT(TIFR,TOV1):0;

	while((TIFR&(1<<ICF1))==0);
	g_T1=ICR1;
	ICU_AT_RISSING();
	CLEAR_ICU_FALG();

	while((TIFR&(1<<ICF1))==0);
	g_T2=ICR1;
	ICU_AT_FALLING();
	CLEAR_ICU_FALG();

	while((TIFR&(1<<ICF1))==0);
	g_T3=ICR1;
	if(!(READ_BIT(TIFR,TOV1)))
	{
		switch(a_val)
		{
		case DUTY_CYCLE:
			return (((g_T3-g_T2)/(float32)(g_T3-g_T1))*100);
		case FREQUENCY:
			return (GetFreq(a_settings_Ptr)/(float32)(g_T3-g_T1));
		case PERIOD:
			return ((1.0/(GetFreq(a_settings_Ptr)/(float32)(g_T3-g_T1)))*1e3);
		}
	}
	else
	{
		return 0;
	}
}


void ICU_SetCallbackFunc(void (a_func_Ptr)(void))
{
	g_ISR_Ptr=a_func_Ptr;
}


void ICU_Deinit(void)
{
	TCCR1A=0;
	TCCR1B=0;
	RESET_TIMER();
	DISABLE_ICU_INTERRUPT();
}



static float64 GetFreq(icu_settings* a_icuSittings_Ptr)
{
	float64 freq=0;

	switch ((uint8)a_icuSittings_Ptr->clockSettings)
	{
	case (CPU_CLOCK_BY8):
			freq=(F_CPU)/8.0;
	return freq;
	case (CPU_CLOCK_BY64):
			freq=(F_CPU)/64.0;
	return freq;
	case (CPU_CLOCK_BY256):
			freq=(F_CPU)/256.0;
	return freq;
	case (CPU_CLOCK_BY1024):
			freq=(F_CPU)/1024.0;
	return freq;
	}
	return F_CPU;
}
