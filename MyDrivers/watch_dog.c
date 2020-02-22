/*
 * watch_dog.c
 *
 *  Created on: Jan 13, 2020
 *      Author: my laptop
 */

/******************************************
 *             #INCLUDES                  *
 ******************************************/
#include"watch_dog.h"
/******************************************
 *           FUNTION DIFENATION           *
 ******************************************/


void WATCH_DOG_Enable(WatchDogTime Time)
{
	WDTCR|=Time;
	SET_BIT(WDTCR,WDE);
}


void WATCH_DOG_Disable()
{
	WDTCR|=((1<<WDE)|(1<<WDTOE));
	_delay_us(4);
	CLEAR_BIT(WDTCR,WDE);
}
