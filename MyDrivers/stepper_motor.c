/*
 * stepper_motor.c
 *
 *  Created on: Jan 13, 2020
 *      Author: my laptop
 */
/*******************************************
 *               #INCLUDES                 *
 *******************************************/

#include "stepper_motor.h"

/*******************************************
 *               GLAOBAL VARIABLS          *
 *******************************************/
static uint8 g_MottorState=3;
static uint8 g_Flage=TRUE;

/*******************************************
 *          FUNCTIONS DEFINATION           *
 ******************************************/

void STEPPER_MOTOR_Init(void)
{

	SET_BIT(_MOTOR1_OP_DDR_A,MOTOR1_OP_PINA_NUMB);
	SET_BIT(_MOTOR1_OP_DDR_B,MOTOR1_OP_PINB_NUMB);
	SET_BIT(_MOTOR1_OP_DDR_C,MOTOR1_OP_PINC_NUMB);
	SET_BIT(_MOTOR1_OP_DDR_D,MOTOR1_OP_PIND_NUMB);


}




void STEPPER_MOTOR_FullStepForword(void)
{
	g_MottorState= ( ( ( g_MottorState & ( 1 << 3 ) ) >> 3) | ( ( g_MottorState <<1 ) & 0x0f ) );

	( g_MottorState & (1<<0) )?SET_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB);
	( g_MottorState & (1<<1) )?SET_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB);
	( g_MottorState & (1<<2) )?SET_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB);
	( g_MottorState & (1<<3) )?SET_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB);
}


void STEPPER_MOTOR_FullStepBackword(void)
{
	g_MottorState= ( ( ( g_MottorState & 1) << 3 ) | ( ( g_MottorState >> 1 ) & 0x0f ) );

	( g_MottorState & (1<<0) )?SET_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB);
	( g_MottorState & (1<<1) )?SET_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB);
	( g_MottorState & (1<<2) )?SET_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB);
	( g_MottorState & (1<<3) )?SET_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB);
}




void STEPPER_MOTOR_HalfStepForword(void)
{
	if(g_Flage)
	{
		uint8 temp= ( g_MottorState & ( ( ( g_MottorState & ( 1 << 3 ) ) >> 3) | ( ( g_MottorState <<1 ) & 0x0f ) ) );

		( temp & (1<<0) )?SET_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB);
		( temp & (1<<1) )?SET_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB);
		( temp & (1<<2) )?SET_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB);
		( temp & (1<<3) )?SET_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB);

		g_Flage=FALSE;
	}
	else
	{
		g_Flage=TRUE;
		STEPPER_MOTOR_FullStepForword();
	}

}


void STEPPER_MOTOR_HalfStepBackword(void)
{
	if(g_Flage)
	{
		uint8 temp= ( g_MottorState &  ( ( ( g_MottorState & 1) << 3 ) | ( ( g_MottorState >> 1 ) & 0x0f ) )   );


		( temp & (1<<0) )?SET_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_A,MOTOR1_OP_PINA_NUMB);
		( temp & (1<<1) )?SET_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_B,MOTOR1_OP_PINB_NUMB);
		( temp & (1<<2) )?SET_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_C,MOTOR1_OP_PINC_NUMB);
		( temp & (1<<3) )?SET_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB):CLEAR_BIT(_MOTOR1_OP_PORT_D,MOTOR1_OP_PIND_NUMB);

		g_Flage=FALSE;
	}
	else
	{
		STEPPER_MOTOR_FullStepBackword();
		g_Flage=TRUE;
	}
}
