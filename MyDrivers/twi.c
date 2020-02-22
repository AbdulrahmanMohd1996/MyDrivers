
#include "twi.h"

volatile static void (*g_callBck_Ptr)(void)=NULL_PTR;



ISR(TWI_vect)
{

	if(g_callBck_Ptr!=NULL_PTR)
	{
		(*g_callBck_Ptr)();
	}
	CLEAR_INT_FLAG();
}


void TWI_Init(void)
{

	#if NORMAL_MODE_RATE_100KB
	TWBR=32;
	#elif FAST_MODE_RATE_400KB
	TWBR=2;
	#endif
	TWAR=(MY_DEVICE_ADDRESS<<1);

	TWCR=(1<<TWEN)|(1<<TWEA);

	#if TWI_INTERRUPT
	TWCR|=(1<<TWIE);
	#endif


#if GENERAL_CALL_RECOGNITION
	TWAR|=1;
#endif

}

void TWI_SendByte(uint8 a_data)
{
	TWDR=a_data;
	TWCR=(1<<TWINT)| (1<<TWEN)|(1<<TWEA);
	WAIT_TILL_INT_FLAG_SET();
}

uint8 TWI_ReadByteWithAck(void)
{
	(READ_BIT(TWCR,TWEA))?(TWCR|=(1<<TWINT)):(TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA));

	WAIT_TILL_INT_FLAG_SET();
	return TWDR;
}

uint8 TWI_ReadByteWithNack(void)
{
	TWCR=(1<<TWEN)|(1<<TWINT);
	WAIT_TILL_INT_FLAG_SET();
	return TWDR;
}


void TWI_SetCallBackFunc(void(*a_Func_Ptr)(void))
{
	g_callBck_Ptr=a_Func_Ptr;
}
