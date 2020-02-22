/*-------------------------------------------------------------------------------------
 |         [FILE NAME]     <adc.c>    		 									   |
 | 		   [AUTHOR]        <Abdolee>                                                   |
 |         [DATE CREATED]  <Jan 15, 2020>											   |
 |         [DESCRIPTION]   <the C driver file for the ADC>						   |
 |-------------------------------------------------------------------------------------*/


/*************************************************
 *                   INCLUDES                    *
 *************************************************/
#include "adc.h"
/*************************************************
 *               GLOABL VARIABLES                *
 *************************************************/
#if ADC_INTERRUPT
static volatile void (*g_AdcIsr_Ptr)(void)=NULL_PTR;
#endif
/*************************************************
 *            PRIVATE FUNCTION PROTOTYPE         *
 *************************************************/



/*************************************************
 *                	   ISR                       *
 *************************************************/
#if ADC_INTERRUPT
ISR(ADC_vect)
{
	if(g_AdcIsr_Ptr!=NULL_PTR)
	{
		(*g_AdcIsr_Ptr)();
	}
}
#endif

/*************************************************
 *              FUNCTION DEFINITIONS             *
 *************************************************/



/*-------------------------------------------------------------------------------------
 |     [FUNCTION NAME]     <ADC_Init>         									   |
 | 	   [DESCRIPTION]       < this function is used to InitIalize the ADC from       |
 |	 	 	 	 	 	 	  the static CONFIG in the H file>                         |
 |     [ARGS]  			   <VOID>
 |	   [RETURNS]           <VOID>										           |
 |-------------------------------------------------------------------------------------*/



void ADC_Init(ADC_Settings* a_settings_Ptr)
{

	ADMUX= (a_settings_Ptr->refVolt<<ADSC);
	ADCSRA=(1<<ADEN)|(a_settings_Ptr->divBy);

	#if ADC_INTERRUPT
	ADCSRA|=(1<<ADIE);
	#endif

	#if ADC_HIGH_SPEED_MODE
	SFIOR|=(1<<4);
	#endif

	#if AUTO_TRIGGER
	SFIOR|=(a_settings_Ptr->autoMode<<ADTS0);
	#endif

	#if ADC_INTERRUPT
	g_AdcIsr_Ptr=a_settings_Ptr->intFunc_Ptr;
	#endif

}


uint16 ADC_ReadChannel(uint8 a_channelNumb)
{
	ADMUX&=~(0x1F);
	ADMUX|=a_channelNumb;

	ADCSRA|=(1<<ADSC);

	if(!(READ_BIT(SREG,7) && READ_BIT(ADCSRA,ADIE)))
	{
		while(!(ADCSRA&(1<<ADIF))){}
		ADCSRA|=(1<<ADIF);
	}

	return ADC;
}


#if ADC_INTERRUPT
void ADC_SetCallBackFunc(void (*a_func_Ptr)(void))
{
	g_AdcIsr_Ptr=a_func_Ptr;
}
#endif
