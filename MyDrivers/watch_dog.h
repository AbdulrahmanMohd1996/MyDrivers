/*
 * watch_dog.h
 *
 *  Created on: Jan 13, 2020
 *      Author: my laptop
 */

#ifndef WATCH_DOG_H_
#define WATCH_DOG_H_
/******************************************
 *             #INCLUDES                  *
 ******************************************/

#include"std_types.h"
#include"common_macros.h"
#include<avr/io.h>
#include<util/delay.h>

/******************************************
 *     STATIC CONFIGRATION AND DEFINES    *
 ******************************************/





/******************************************
 *                 ENUMS                  *
 ******************************************/
typedef enum
{
	reset_after_16ms=0,
	reset_after_32ms=1,
	reset_after_65ms=2,
	reset_after_130ms=3,
	reset_after_260ms=4,
	reset_after_520ms=5,
	reset_after_1s=6,
	reset_after_2s=7,
}WatchDogTime;

/******************************************
 *               STRUCTURS                *
 ******************************************/




/******************************************
 *             FUNCTION PROTOTYPE         *
 ******************************************/
void WATCH_DOG_Enable(WatchDogTime Time);
void WATCH_DOG_Disable();

/******************************************
 *                MACROS                  *
 ******************************************/

#endif /* WATCH_DOG_H_ */
