/*
 * twi.h
 *
 *  Created on: Jan 30, 2020
 *      Author: my laptop
 */

#ifndef TWI_H_
#define TWI_H_

#include "avr/io.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/interrupt.h>


#define NORMAL_MODE_RATE_100KB             ENABLE
#define FAST_MODE_RATE_400KB               DISABLE


#define MY_DEVICE_ADDRESS                  (0x03U)   //7-BIT ADDRESS
#define GENERAL_CALL_RECOGNITION           DISABLE

#define TWI_INTERRUPT                      DISABLE







/* at maser mode*/
#define START_BIT_HAS_BEEN_TRANSMITTED       	          			 (0X08)
#define REAPETED_START_BIT_HAS_BEEN_TRANSMITTED                 	 (0X10)
#define SLA_W_HAS_BEEN_TRANSMITTED_AND_ACK_RECEIVED        			 (0X18)
#define SLA_W_HAS_BEEN_TRANSMITTED_AND_NACK_RECEIVED             	 (0X20)
#define DATA_BYTE_HAS_BEEN_TRANSMITTED_AND_ACK_RECIEVED              (0X28)
#define DATA_BYTE_HAS_BEEN_TRANSMITTED_AND_NACK_RECIEVED             (0X30)
#define SLA_R_HAS_BEEN_TRANSMITTED_AND_ACK_RECEIVED     			 (0X40)
#define SLA_R_HAS_BEEN_TRANSMITTED_AND_NACK_RECEIVED     			 (0X48)
#define DATA_BYTE_HAS_BEEN_RECIEVED_AND_ACK_TRANSMITTED              (0X50)
#define DATA_BYTE_HAS_BEEN_RECIEVED_AND_NACK_TRANSMITTED             (0X58)

/*at slave mode*/
#define OWN_SLA_W_RECEIVED_ACK_TRANSMITTED                   		 (0X60)
#define SLA_W_DATA_RECIEVED_AND_ACK_TRANSMITTED                      (0X80)
#define SLA_W_DATA_RECIEVED_AND_NACK_TRANSMITTED                     (0X88)
#define STOP_BIT_RECIVED											 (0XA0)
#define OWN_SLA_R_RECEIVED_ACK_TRANSMITTED                   	     (0XA8)
#define SLA_R_DATA_TRANSMITTED_AND_ACK_RECEIVED                      (0XB8)
#define SLA_R_DATA_TRANSMITTED_AND_NACK_RECEIVED                     (0XC0)
#define LAST_DATA_BYTE_HAS_BEEN_TRANMITTED_TWEA_ZERO                 (0XC8)

/*GENERAL STATES*/
#define NO_STATE_AVAILABLE_TWINT_ZERO                      			 (0XF8)
#define BUS_ERROR                             						 (0X00)





#define SEND_START_BIT()                         TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define SEND_STOP_BIT()                          TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO)
#define WAIT_TILL_INT_FLAG_SET()                 while(!( READ_BIT(TWCR,TWINT) ) )
#define READ_TWI_STATUS()                        (TWSR)
#define ENABLE_ACK_BIT()                         TWCR|=(1<<TWEA)
#define DISABLE_ACK_BIT()                        TWCR&=~(1<<TWEA)
#define ENABLE_INTERRUPT()                       SET_BIT(TWCR,TWIE)
#define DISABLE_INTERRUPT()                      CLEAR_BIT(TWCR,TWIE)
#define CLEAR_INT_FLAG()						 TWCR|=(1<<TWINT)











void TWI_Init(void);
void TWI_SendByte(uint8 a_data);
uint8 TWI_ReadByteWithAck(void);
uint8 TWI_ReadByteWithNack(void);
void TWI_SetCallBackFunc(void(*a_Func_Ptr)(void));



#endif /* TWI_H_ */
