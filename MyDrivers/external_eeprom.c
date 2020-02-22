

#include "external_eeprom.h"
#include "lcd.h"
void EXTERNAL_EEPROM_Init(void)
{
	TWI_Init();
}

uint8 EXTERNAL_EEPROM_WriteByte(uint16 a_address, uint8 a_data)
{
	SEND_START_BIT();
	WAIT_TILL_INT_FLAG_SET();
	if(READ_TWI_STATUS()!=START_BIT_HAS_BEEN_TRANSMITTED)
	{
		return FAIL;
	}

	TWI_SendByte(EXTERNAL_EEPROM_SLAVE_ADDRESS| ( ( a_address & 0X0700 ) >> 7 ) );
	if(READ_TWI_STATUS()!=SLA_W_HAS_BEEN_TRANSMITTED_AND_ACK_RECEIVED)
	{
		return FAIL;
	}

	TWI_SendByte((uint8)a_address);
	if(READ_TWI_STATUS()!=DATA_BYTE_HAS_BEEN_TRANSMITTED_AND_ACK_RECIEVED)
	{
		return FAIL;
	}

	TWI_SendByte(a_data);
	if(READ_TWI_STATUS()!=DATA_BYTE_HAS_BEEN_TRANSMITTED_AND_ACK_RECIEVED)
	{
		return FAIL;
	}


	SEND_STOP_BIT();

	return SUCCESS;

}


uint8 EXERNAL_EEPROM_ReadByte(uint16 a_address, uint8* a_byte_Ptr)
{

	SEND_START_BIT();
	WAIT_TILL_INT_FLAG_SET();
	if(READ_TWI_STATUS()!=START_BIT_HAS_BEEN_TRANSMITTED)
	{
		return FAIL;
	}

	TWI_SendByte((EXTERNAL_EEPROM_SLAVE_ADDRESS| ( ( a_address & 0X0700 ) >> 7 ) ) );
	if(READ_TWI_STATUS()!=SLA_W_HAS_BEEN_TRANSMITTED_AND_ACK_RECEIVED)
	{
		return FAIL;
	}

	TWI_SendByte((uint8)a_address);
	if(READ_TWI_STATUS()!=DATA_BYTE_HAS_BEEN_TRANSMITTED_AND_ACK_RECIEVED)
	{

		return FAIL;
	}

	SEND_START_BIT();
	WAIT_TILL_INT_FLAG_SET();
	if(READ_TWI_STATUS()!=REAPETED_START_BIT_HAS_BEEN_TRANSMITTED)
	{
		return FAIL;
	}
	TWI_SendByte((EXTERNAL_EEPROM_SLAVE_ADDRESS| ( ( a_address & 0X0700 ) >> 7 ) ) | 1 );
	if(READ_TWI_STATUS()!=SLA_R_HAS_BEEN_TRANSMITTED_AND_ACK_RECEIVED)
	{

		return FAIL;
	}

	*a_byte_Ptr=TWI_ReadByteWithNack();
	if(READ_TWI_STATUS()!=DATA_BYTE_HAS_BEEN_RECIEVED_AND_NACK_TRANSMITTED)
	{

		return FAIL;
	}
	SEND_STOP_BIT();

	return SUCCESS;
}
