
#include "uart.h"

#if UART_RX_INTERRUPT
volatile static void (*g_rxCallBack_Ptr)(void)=NULL_PTR;
#endif

#if UART_TX_INTERRUPT
volatile static void (*g_txCallBack_Ptr)(void)=NULL_PTR;
#endif

#if UART_DATA_REG_EMPTY
volatile static void (*g_registerEmptyCallBack_Ptr)(void)=NULL_PTR;
#endif


#if UART_RX_INTERRUPT

ISR(USART_RXC_vect)
{
	if(g_rxCallBack_Ptr!=NULL_PTR)
	{
		(*g_rxCallBack_Ptr)();
	}

}

#endif


#if UART_DATA_REG_EMPTY

ISR(USART_UDRE_vect)
{
	if(g_txCallBack_Ptr!=NULL_PTR)
	{
		g_rxCallBack_Ptr();
	}
}

#endif


#if UASRT_TX_INTERRUPT
ISR(USART_TXC_vect)
{
	if(g_registerEmptyCallBack_Ptr!=NULL_PTR)
	{
		g_rxCallBack_Ptr();
	}
}

#endif


void UART_Init(uartSettings* a_setings_Ptr)
{

	UCSRA=(1<<U2X);
	UCSRB=(1<<TXEN)|(1<<RXEN);
	UCSRC=(1<<URSEL)|(a_setings_Ptr->parityMode<<UPM0)|(a_setings_Ptr->frameSize<<UCSZ0);

	/*****************************************************************
	 * BAUD=( ( Fosc ) / ( 8 * ( UBRR+1 ) ) ) (DOUBLE SPEED MODE)    *
	 * SO UBRR = (((Fosc)/(8*BAUD))-1)      						 *
	 *****************************************************************/
	UBRRL=( (uint16) ( ( ( F_CPU ) / ( 8.0 * (a_setings_Ptr->boadRate) ) ) - 1 ) & 0X00FF);
	UBRRH=( (uint16)( ( ( F_CPU ) / ( 8.0 * (a_setings_Ptr->boadRate ) ) ) - 1 ) & 0X0F00);

#if UART_TX_INTERRUPT
	UCSRB|=(1<<TXCIE);
#endif

#if UART_RX_INTERRUPT
	UCSRB|=(1<<RXCIE);
#endif

#if UART_DATA_REG_EMPTY
	UCSRB|=(1<<UDRIE);
#endif

}



void UART_TransmitChar(uint8 a_data)
{
	while(!(READ_BIT(UCSRA,UDRE)));
	UDR=a_data;
}



uint8 UART_ReceiveChar(void)
{
	while(!(READ_BIT(UCSRA,RXC)));
	return UDR;
}



void UART_TransmitStrig(const uint8* a_String_Ptr)
{
	while(*(a_String_Ptr)!='\0')
	{
		UART_TransmitChar(*a_String_Ptr);
		a_String_Ptr++;
	}
	UART_TransmitChar(STRING_END_CHAR);
}


uint8* UART_RecieveString(uint8* a_emptyString_Ptr)
{
	uint8 i=0;

	while(a_emptyString_Ptr[(i-1)]!=STRING_END_CHAR)
	{
		a_emptyString_Ptr[i]=UART_ReceiveChar();
		i++;
	}
	a_emptyString_Ptr[i-1]='\0';
	return &(a_emptyString_Ptr[0]);
}


#if UART_RX_INTERRUPT
void UART_SetRxCallBackFunc(void(*a_func_Ptr)(void))
{
	g_rxCallBack_Ptr=a_func_Ptr;

}
#endif

#if UART_TX_INTERRUPT
void UART_SetTxCallBackFunc(void(*a_func_Ptr)(void))
{
	g_txCallBack_Ptr=a_func_Ptr;

}
#endif

#if UART_DATA_REG_EMPTY
void UART_SetRegisterEmptyCallBackFunc(void(*a_func_Ptr)(void))
{
	g_registerEmptyCallBack_Ptr=a_func_Ptr;

}
#endif

