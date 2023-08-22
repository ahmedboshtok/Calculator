/*
 * LCD_priv.h
 *
 *  Created on: Oct 2, 2021
 *      Author: abosh
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_



#define FOUR_BIT		9
#define	EIGHT_BIT		15

#define		CLEAR_DISPLAY									0x01

#define EIGHT_BIT_FUNCTION_SET		0x38
#define FOUR_BIT_FUNCTION_SET		0x28
#define DISPLAY_CONTROL				0X0F
#define DISPLAY_CLEAR				0X01
#define ENTRY_MODE_SET				0x06
#define ENTRY_MODE_SET_DECREMENT	0x04

static ES_t LCD_enuWriteNLatch(u8 Copy_u8Value);
static ES_t LCD_enuLatch(void);



#define FIRST_LINE_STARTING_ADDRESS	0x80
#define SECOND_LINE_STARTING_ADDRESS	0xC0

#define PATTERN_ZERO		0x40
#define PATTERN_ONE			0x48
#define PATTERN_TWO			0x50
#define PATTERN_THREE		0x58
#define PATTERN_FOUR		0x60
#define PATTERN_FIVE		0x68
#define PATTERN_SIX			0x70
#define PATTERN_SEVEN		0x78

#define DECREMENT					80
#define INCREMENT					90



#endif /* LCD_PRIV_H_ */
