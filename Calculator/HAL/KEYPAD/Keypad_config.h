/*
 * Keypad_config.h
 *
 *  Created on: Oct 9, 2021
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define COL_NUM			4
#define ROW_NUM			4


#define KEYPAD_VALUES			{ {'7','8','9','/'},\
								  {'4','5','6','*'},\
								  {'1','2','3','-'},\
								  {'c','0','=','+'}  }



#define C1_PORT			DIO_u8GROUP_B
#define C1_PIN			DIO_u8PIN4

#define C2_PORT			DIO_u8GROUP_B
#define C2_PIN			DIO_u8PIN5

#define C3_PORT			DIO_u8GROUP_B
#define C3_PIN			DIO_u8PIN6

#define C4_PORT			DIO_u8GROUP_B
#define C4_PIN			DIO_u8PIN7



#define R1_PORT			DIO_u8GROUP_C
#define R1_PIN			DIO_u8PIN3

#define R2_PORT			DIO_u8GROUP_C
#define R2_PIN			DIO_u8PIN4

#define R3_PORT			DIO_u8GROUP_C
#define R3_PIN			DIO_u8PIN5

#define R4_PORT			DIO_u8GROUP_C
#define R4_PIN			DIO_u8PIN6



#endif /* KEYPAD_CONFIG_H_ */
