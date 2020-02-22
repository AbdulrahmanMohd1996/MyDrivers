

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "twi.h"

#define SUCCESS 				(1u)
#define FAIL                    (0u)


#define EXTERNAL_EEPROM_SLAVE_ADDRESS               (0XA0)





void EXTERNAL_EEPROM_Init(void);
uint8 EXTERNAL_EEPROM_WriteByte(uint16 a_address, uint8 a_data);
uint8 EXERNAL_EEPROM_ReadByte(uint16 a_address, uint8* a_byte_Ptr);
#endif /* EXTERNAL_EEPROM_H_ */
