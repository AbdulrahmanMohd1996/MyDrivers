/*
 * dc_motor.h
 *
 *  Created on: Jan 13, 2020
 *      Author: my laptop
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*******************************************
 *               #INCLUDES                 *
 *******************************************/
#include"common_macros.h"
#include"std_types.h"
#include<avr/io.h>

/*******************************************
 *              DIFENATIONS                *
 *******************************************/

#define L293D_HBRIDGE  ENABLE

#define MOTOR1    ENABLE
#define MOTOR2    ENABLE
#define MOTOR3    DISABLE
#define MOTOR4    DISABLE

/*******************************************
 *              STATIC CONFIG              *
 *******************************************/

	#if L293D_HBRIDGE

		#if MOTOR1

		#define M1      	              	    1

		#define _MOTOR1_OP_DDR1          	   DDRC
		#define _MOTOR1_OP_PORT1          	   PORTC
		#define MOTOR1_OP_PIN1_NUMB         	0

		#define _MOTOR1_OP_DDR2          	   DDRC
		#define _MOTOR1_OP_PORT2           	   PORTC
		#define MOTOR1_OP_PIN2_NUMB         	1

		#endif


		#if MOTOR2

		#define M2      	              	   2

		#define _MOTOR2_OP_DDR1          	   DDRC
		#define _MOTOR2_OP_PORT1          	   PORTC
		#define MOTOR2_OP_PIN1_NUMB         	2

		#define _MOTOR2_OP_DDR2          	   DDRC
		#define _MOTOR2_OP_PORT2           	   PORTC
		#define MOTOR2_OP_PIN2_NUMB         	3

		#endif


		#if MOTOR3

		#define M3      	              	3

		#define _MOTOR3_OP_DDR1          	   DDRC
		#define _MOTOR3_OP_PORT1          	   PORTC
		#define MOTOR3_OP_PIN1_NUMB         	0

		#define _MOTOR3_OP_DDR2          	   DDRC
		#define _MOTOR3_OP_PORT2           	   PORTC
		#define MOTOR3_OP_PIN2_NUMB         	1

		#endif


		#if MOTOR4

		#define M4      	              	4

		#define _MOTOR4_OP_DDR1          	   DDRC
		#define _MOTOR4_OP_PORT1          	   PORTC
		#define MOTOR4_OP_PIN1_NUMB         	0

		#define _MOTOR4_OP_DDR2          	   DDRC
		#define _MOTOR4_OP_PORT2           	   PORTC
		#define MOTOR4_OP_PIN2_NUMB         	1

		#endif

	#endif

/*******************************************
 *                 ENUMS                   *
 *******************************************/


/*******************************************
 *                STRUCTURES               *
 *******************************************/





/*******************************************
 *           FUNCTIONS PROTOTYPES          *
 *******************************************/

void DC_MOTOR_Init(uint8 a_motorNumb);
void DC_MOTOR_MoveCkWise(uint8 a_motorNumb);
void DC_MOTOR_MoveAntiCkWise(uint8 a_motorNumb);
void DC_MOTOR_Stop(uint8 a_motorNumb);

/*******************************************
 *                MACROS                   *
 *******************************************/

#endif /* DC_MOTOR_H_ */
