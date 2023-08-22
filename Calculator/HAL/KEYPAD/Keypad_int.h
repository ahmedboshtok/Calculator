/*
 * Keypad_int.h
 *
 *  Created on: Oct 9, 2021
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

ES_t Keypad_enuInit(void);

ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue);

#define KEYPAD_NOT_PRESSED    0xff

#define		CLEAR_DISPLAY									0x01

#define 	RETURN_HOME										0x02

#define 	DECREMENT_CURSOR_TO_LEFT						0x04
#define 	INCREMENT_CURSOR_TO_RIGHT						0x06

#define 	SHIFT_DISPLAY_TO_RIGHT							0x05
#define 	SHIFT_DISPLAY_TO_LEFT							0x07


#define 	DISPLAY_OFF_CURSOR_OFF							0x08
#define 	DISPLAY_OFF_CURSOR_ON							0x0A
#define 	DISPLAY_ON_CURSOR_OFF							0x0C
#define 	DISPLAY_ON_CURSOR_BLINK							0x0E


#define 	SHIFT_CURSOR_POSITION_TO_LEFT					0x10
#define 	SHIFT_CURSOR_POSITION_TO_RIGHT					0x14

#define 	SHIFT_ENTRIE_DISPLAY_TO_LEFT					0x18
#define 	SHIFT_ENTRIE_DISPLAY_TO_RIGHT					0x1C

#define 	FORCE_CURSOR_START_FIRST_LINE					0x80
#define 	FORCE_CURSOR_START_SECOND_LINE					0xC0

#define     GO_TO_CGRAM										0x40
#endif /* KEYPAD_INT_H_ */
