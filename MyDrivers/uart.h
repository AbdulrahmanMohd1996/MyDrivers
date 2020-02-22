#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "common_macros.h"
#include "std_types.h"

#define UART_TX_INTERRUPT  	    	    	   		DISABLE
#define UART_RX_INTERRUPT  	    	    	        DISABLE
#define UART_DATA_REG_EMPTY                         DISABLE

#if (UART_TX_INTERRUPT || UART_RX_INTERRUPT || UART_DATA_REG_EMPTY )
#include <avr/interrupt.h>
#endif

#define STRING_END_CHAR                             '$'


typedef enum
{
	RATE_2400_BPS=2400,
	RATE_4800_BPS=4800,
	RATE_9600_BPS=9600,
	RATE_19200_BPS=19200,
	RATE_38400_BPS=38400,
	RATE_57600_BPS=57600,
	RATE_115200_BPS=115200,
}standerdBaudRate;



typedef enum
{
	DISABLE_PARITY=0,
	EVEN_PARITY=2,
	ODD_PARITY=3,
}parityModes;



typedef enum
{
	FIVE_BITS=0,
	SIX_BITS=1,
	SEVEN_BITS=2,
	EIGHT_BITS=3,
}charSize;




typedef struct
{
	parityModes parityMode;
	charSize frameSize;
	standerdBaudRate boadRate;
}uartSettings;




#define ENABLE_RX_INTERRUPT()                			  UCSRB|=(1<<RXCIE)
#define DISABLE_RX_INTERRUPT()                			  UCSRB&=~(1<<RXCIE)

#define ENABLE_TX_INTERRUPT()          			          UCSRB|=(1<<TXCIE)
#define DISABLE_TX_INTERRUPT()          			      UCSRB&=~(1<<TXCIE)

#define ENABLE_DATA_REG_EMPTY_INTERRUPT()                 UCSRB|=(1<<UDRIE)
#define DISABLE_DATA_REG_EMPTY_INTERRUPT()                UCSRB&=~(1<<UDRIE)


void UART_Init(uartSettings* a_setings_Ptr);
void UART_TransmitChar(uint8 a_data);
uint8 UART_ReceiveChar(void);
void UART_TransmitStrig(const uint8* a_String_Ptr);
uint8* UART_RecieveString(uint8* a_emptyString_Ptr);

void UART_SetRxCallBackFunc(void(*a_func_Ptr)(void));


#endif /* UART_H_ */
