/*
 * dc_motor.c
 *
 *  Created on: Jan 13, 2020
 *      Author: my laptop
 */

#include"dc_motor.h"

void DC_MOTOR_Init(uint8 a_motorNumb)
{
	switch(a_motorNumb)
	{
	case M1:
		SET_BIT(_MOTOR1_OP_DDR1,MOTOR1_OP_PIN1_NUMB);
		SET_BIT(_MOTOR1_OP_DDR2,MOTOR1_OP_PIN2_NUMB);
		break;

#if MOTOR2
	case M2:
		SET_BIT(_MOTOR2_OP_DDR1,MOTOR2_OP_PIN1_NUMB);
		SET_BIT(_MOTOR2_OP_DDR2,MOTOR2_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR3
	case M3:
		SET_BIT(_MOTOR3_OP_DDR1,MOTOR3_OP_PIN1_NUMB);
		SET_BIT(_MOTOR3_OP_DDR2,MOTOR3_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR4
	case M4:
		SET_BIT(_MOTOR4_OP_DDR1,MOTOR4_OP_PIN1_NUMB);
		SET_BIT(_MOTOR4_OP_DDR2,MOTOR4_OP_PIN2_NUMB);
		break;
#endif

	}

}



void DC_MOTOR_MoveCkWise(uint8 a_motorNumb)
{
	switch(a_motorNumb)
	{
	case M1:
		CLEAR_BIT(_MOTOR1_OP_PORT1,MOTOR1_OP_PIN1_NUMB);
		SET_BIT(_MOTOR1_OP_PORT2,MOTOR1_OP_PIN2_NUMB);
		break;

#if MOTOR2
	case M2:
		CLEAR_BIT(_MOTOR2_OP_PORT1,MOTOR2_OP_PIN1_NUMB);
		SET_BIT(_MOTOR2_OP_PORT2,MOTOR2_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR3
	case M3:
		CLEAR_BIT(_MOTOR3_OP_PORT1,MOTOR3_OP_PIN1_NUMB);
		SET_BIT(_MOTOR3_OP_PORT2,MOTOR3_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR4
	case M4:
		CLEAR_BIT(_MOTOR4_OP_PORT1,MOTOR4_OP_PIN1_NUMB);
		SET_BIT(_MOTOR4_OP_PORT2,MOTOR4_OP_PIN2_NUMB);
		break;
#endif

	}

}


void DC_MOTOR_MoveAntiCkWise(uint8 a_motorNumb)
{
	switch(a_motorNumb)
	{
	case M1:
		SET_BIT(_MOTOR1_OP_PORT1,MOTOR1_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR1_OP_PORT2,MOTOR1_OP_PIN2_NUMB);
		break;

#if MOTOR2
	case M2:
		SET_BIT(_MOTOR2_OP_PORT1,MOTOR2_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR2_OP_PORT2,MOTOR2_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR3
	case M3:
		SET_BIT(_MOTOR3_OP_PORT1,MOTOR3_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR3_OP_PORT2,MOTOR3_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR4
	case M4:
		SET_BIT(_MOTOR4_OP_PORT1,MOTOR4_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR4_OP_PORT2,MOTOR4_OP_PIN2_NUMB);
		break;
#endif

	}

}


void DC_MOTOR_Stop(uint8 a_motorNumb)
{
	switch(a_motorNumb)
	{
	case 1:
		CLEAR_BIT(_MOTOR1_OP_PORT1,MOTOR1_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR1_OP_PORT2,MOTOR1_OP_PIN2_NUMB);
		break;

#if MOTOR2
	case M2:
		CLEAR_BIT(_MOTOR2_OP_PORT1,MOTOR2_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR2_OP_PORT2,MOTOR2_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR3
	case M3:
		CLEAR_BIT(_MOTOR3_OP_PORT1,MOTOR3_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR3_OP_PORT2,MOTOR3_OP_PIN2_NUMB);
		break;
#endif

#if MOTOR4
	case M4:
		CLEAR_BIT(_MOTOR4_OP_PORT1,MOTOR4_OP_PIN1_NUMB);
		CLEAR_BIT(_MOTOR4_OP_PORT2,MOTOR4_OP_PIN2_NUMB);
		break;
#endif

	}

}
