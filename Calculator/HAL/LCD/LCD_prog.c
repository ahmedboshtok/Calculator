/*
 * LCD_prog.c
 *
 *  Created on: Oct 2, 2021
 *      Author: abosh
 */
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "LCD_config.h"
#include "LCD_priv.h"


#include <util/delay.h>


ES_t LCD_enuInit(void)
{
	ES_t Local_u8ErrorState = ES_NOK;

	DIO_enuSetPinDirection(RS_PORT, RS_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RW_PORT, RW_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(EN_PORT, EN_PIN, DIO_u8OUTPUT);

	DIO_enuSetPinDirection(D7_PORT, D7_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D6_PORT, D6_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D5_PORT, D5_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D4_PORT, D4_PIN, DIO_u8OUTPUT);

	_delay_ms(35);
#if LCD_MODE == FOUR_BIT
	DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8LOW);
	LCD_enuWriteNLatch(0x28);

#elif LCD_MODE == EIGHT_BIT
	DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8LOW);
	LCD_enuWriteNLatch(0x38);

	DIO_enuSetPinDirection(D3_PORT, D3_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D2_PORT, D2_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D1_PORT, D1_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D0_PORT, D0_PIN, DIO_u8OUTPUT);



#endif

	_delay_ms(1);
	DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8LOW);
	LCD_enuWriteNLatch(0x0f);

	_delay_ms(1);
	DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8LOW);
	LCD_enuWriteNLatch(0x01);

	_delay_ms(2);
	DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8LOW);
	LCD_enuWriteNLatch(0x06);

	return Local_u8ErrorState;
}

ES_t LCD_enuSendData(u8 Copy_u8Data)
{
	ES_t Local_u8ErrorState = ES_NOK;
	u16 Local_u16ErrorState;
	Local_u16ErrorState = DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8HIGH);
	Local_u16ErrorState = (LCD_enuWriteNLatch(Copy_u8Data)<<2);
	if (Local_u16ErrorState == 0b0101){
		Local_u8ErrorState = ES_OK;
	}
	return Local_u8ErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	ES_t Local_u8ErrorState = ES_NOK;
	u16 Local_u16ErrorState;
	Local_u16ErrorState = DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8LOW);
	Local_u16ErrorState = (LCD_enuWriteNLatch(Copy_u8Command)<<2);
	if (Local_u16ErrorState == 0b0101){
		Local_u8ErrorState = ES_OK;
	}
	return Local_u8ErrorState;
}

ES_t LCD_enuSendString(const char * Copy_pcString)
{
	ES_t Local_u8ErrorState = ES_NOK;

	while (*Copy_pcString)//'\0' ,'0'// (*Copy_pcString!='\0') or (*Copy_pcString!='\0')
	{
		DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_u8HIGH);
		LCD_enuWriteNLatch(*Copy_pcString++);
	}

	return Local_u8ErrorState;
}


ES_t LCD_enuGoToPosition(u8 Copy_u8Line,u8 Copy_u8Column)//16*2
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8ErrorState = 0;

	Local_u8ErrorState = DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);

	if(Copy_u8Line == 1)
	{
		Local_u8ErrorState |= LCD_enuWriteNLatch(FIRST_LINE_STARTING_ADDRESS + (Copy_u8Column - 1))<<2;
	}
	else if(Copy_u8Line == 2)
	{
		Local_u8ErrorState |= LCD_enuWriteNLatch(SECOND_LINE_STARTING_ADDRESS + (Copy_u8Column - 1))<<2;
	}
	else {
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	if(Local_u8ErrorState == 5)
	{
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuSendExtraCharacter(u8 Copy_Au8Arr[],u8 Copy_u8PatternNumber,u8 Copy_u8NumberOfPatterns,u8 Copy_u8Line,u8 Copy_u8Column,u8 Copy_u8IncDec)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);//sending command

	switch(Copy_u8PatternNumber)
	{
		case 0:
			LCD_enuWriteNLatch(PATTERN_ZERO);
		break;
		case 1:
			LCD_enuWriteNLatch(PATTERN_ONE);
		break;
		case 2:
			LCD_enuWriteNLatch(PATTERN_TWO);
		break;
		case 3:
			LCD_enuWriteNLatch(PATTERN_THREE);
		break;
		case 4:
			LCD_enuWriteNLatch(PATTERN_FOUR);
		break;
		case 5:
			LCD_enuWriteNLatch(PATTERN_FIVE);
		break;
		case 6:
			LCD_enuWriteNLatch(PATTERN_SIX);
		break;
		case 7:
			LCD_enuWriteNLatch(PATTERN_SEVEN);
		break;
	}

	/*FILL THE CGRAM WITH THE PATTERNS*/
	DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8HIGH);//sending data

	u8 Local_u8Iterator;
	for(Local_u8Iterator = 0;Local_u8Iterator<Copy_u8NumberOfPatterns*8;Local_u8Iterator++)
		LCD_enuWriteNLatch(Copy_Au8Arr[Local_u8Iterator]);

	/*INCREMENT OR DECREMENT*/
	if(Copy_u8IncDec == DECREMENT)
	{
		DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);//sending command
		LCD_enuWriteNLatch(ENTRY_MODE_SET_DECREMENT);
	}

	/*GO TO POSITION*/
	DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);//sending command
	if(Copy_u8Line == 1)
	{
		LCD_enuWriteNLatch(FIRST_LINE_STARTING_ADDRESS + (Copy_u8Column - 1));
	}
	else if(Copy_u8Line == 2)
	{
		LCD_enuWriteNLatch(SECOND_LINE_STARTING_ADDRESS + (Copy_u8Column - 1));
	}

	/*DISPLAY DATA*/
	DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8HIGH);//sending data
	for(Local_u8Iterator = 0;Local_u8Iterator<Copy_u8NumberOfPatterns;Local_u8Iterator++)
	{
		LCD_enuWriteNLatch(Copy_u8PatternNumber);
		Copy_u8PatternNumber++;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuDisplayInt(s32 Copy_s32Number)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8HIGH);//sending data

	if(Copy_s32Number == 0)
		LCD_enuWriteNLatch(48);
	else
	{
		if(Copy_s32Number < 0)
			{
				LCD_enuWriteNLatch('-');
				Copy_s32Number *= -1;
			}

			//REVERSE THE NUMBER
			s32 Local_s32Remainder = 0;
			s32 Local_s32Current;
			s32 Local_s32Duplicate = Copy_s32Number;

			while(Local_s32Duplicate != 0)
			{
				Local_s32Current = Local_s32Duplicate%10;
				Local_s32Remainder = (Local_s32Remainder * 10) + Local_s32Current;
				Local_s32Duplicate /= 10;
			}

			while(Local_s32Remainder != 0)
			{
				LCD_enuWriteNLatch( (Local_s32Remainder%10) + 48);
				Local_s32Remainder /= 10;
			}

			//SOLVING THE ZERO BUG
			while(1)
			{
				Local_s32Current = Copy_s32Number% 10;
				if(Local_s32Current != 0)
					break;
				else
				{
					LCD_enuWriteNLatch(48);
					Copy_s32Number /= 10;
				}
			}
	}

	return Local_enuErrorState;
}

ES_t LCD_enuDisplayFloat(f32 Copy_f32Number)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8HIGH);//sending data

	u32 Local_u32IntVer = (u32)Copy_f32Number;

	if(Local_u32IntVer == 0)
	{
		LCD_enuWriteNLatch(48);
		//ADD THE FLOATING POINT
		LCD_enuWriteNLatch('.');

		//DISPLAY NUMBERS AFTER THE FLOATING POINT
		while((u32)Copy_f32Number)
		{
			Copy_f32Number *= 10;
			LCD_enuWriteNLatch(((u32)Copy_f32Number%10) + 48);
			Copy_f32Number = Copy_f32Number - (u32)Copy_f32Number;
		}
	}

	else
	{
		if(Copy_f32Number < 0)
			{
				LCD_enuWriteNLatch('-');
				Copy_f32Number *= -1;
			}

			//REVERSE THE NUMBER
			u32 Local_u32Remainder = 0;
			u32 Local_u32Current;
			u32 Local_u32Duplicate = Local_u32IntVer;

			while(Local_u32Duplicate != 0)
			{
				Local_u32Current = Local_u32Duplicate%10;
				Local_u32Remainder = (Local_u32Remainder * 10) + Local_u32Current;
				Local_u32Duplicate /= 10;
			}

			while(Local_u32Remainder != 0)
			{
				LCD_enuWriteNLatch( (Local_u32Remainder%10) + 48);
				Local_u32Remainder /= 10;
			}

			//SOLVING THE ZERO BUG
			s32 Local_s32Duplicate2 = Local_u32IntVer;
			while(1)
			{
				Local_u32Current = Local_s32Duplicate2 % 10;
				if(Local_u32Current != 0)
					break;
				else
				{
					LCD_enuWriteNLatch(48); //ASCII ZERO
					Local_s32Duplicate2 /= 10;
				}
			}

			//ADD THE FLOATING POINT
			LCD_enuWriteNLatch('.');

			//DISPLAY NUMBERS AFTER THE FLOATING POINT
			Copy_f32Number -=  Local_u32IntVer;

			while(Copy_f32Number)
			{
				Copy_f32Number *= 10;
				LCD_enuWriteNLatch(((u32)Copy_f32Number%10) + 48);
				Copy_f32Number = Copy_f32Number - (u32)Copy_f32Number;
			}

	}




	return Local_enuErrorState;
}



static ES_t LCD_enuWriteNLatch(u8 Copy_u8Data)
{
	ES_t Local_u8ErrorState = ES_NOK;
	u32 Local_u32ErrorState,Local_u32ErrorState1,Local_u32ErrorState2;
	Local_u32ErrorState = DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW);
	Local_u32ErrorState = (DIO_enuSetPinValue(RW_PORT , RW_PIN , DIO_u8LOW)<<2);

	if (Copy_u8Data == 0x28)//'('
	{
		u8 Local_u8RS_Val;
		Local_u32ErrorState = (DIO_enuGetPinValue(RS_PORT, RS_PIN, &Local_u8RS_Val)<<2);

		if (Local_u8RS_Val == DIO_u8LOW)
		{
			Local_u32ErrorState = (DIO_enuSetPinValue(D7_PORT, D7_PIN , ((Copy_u8Data>>7)&1))<<2);
			Local_u32ErrorState = (DIO_enuSetPinValue(D6_PORT, D6_PIN , ((Copy_u8Data>>6)&1))<<2);
			Local_u32ErrorState = (DIO_enuSetPinValue(D5_PORT, D5_PIN , ((Copy_u8Data>>5)&1))<<2);
			Local_u32ErrorState = (DIO_enuSetPinValue(D4_PORT, D4_PIN , ((Copy_u8Data>>4)&1))<<2);

			LCD_enuLatch();

		}
	}

#if LCD_MODE == FOUR_BIT //'A' =65=0b 0100  0001

	Local_u32ErrorState1 = (DIO_enuSetPinValue(D7_PORT, D7_PIN , ((Copy_u8Data>>7)&1))<<2);
	Local_u32ErrorState1 = (DIO_enuSetPinValue(D6_PORT, D6_PIN , ((Copy_u8Data>>6)&1))<<2);
	Local_u32ErrorState1 = (DIO_enuSetPinValue(D5_PORT, D5_PIN , ((Copy_u8Data>>5)&1))<<2);
	Local_u32ErrorState1 = (DIO_enuSetPinValue(D4_PORT, D4_PIN , ((Copy_u8Data>>4)&1))<<2);

	LCD_enuLatch();



	Local_u32ErrorState1 = (DIO_enuSetPinValue(D7_PORT, D7_PIN , ((Copy_u8Data>>3)&1))<<2);
	Local_u32ErrorState1 = (DIO_enuSetPinValue(D6_PORT, D6_PIN , ((Copy_u8Data>>2)&1))<<2);
	Local_u32ErrorState1 = (DIO_enuSetPinValue(D5_PORT, D5_PIN , ((Copy_u8Data>>1)&1))<<2);
	Local_u32ErrorState1 = (DIO_enuSetPinValue(D4_PORT, D4_PIN , ((Copy_u8Data>>0)&1))<<2);

	LCD_enuLatch();

#elif LCD_MODE == EIGHT_MODE
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,(Copy_u8Data>>DIO_u8PIN7)&1)<<2);
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D6_GROUP,LCD_u8D6_PIN,(Copy_u8Data>>DIO_u8PIN6)&1)<<2);
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D5_GROUP,LCD_u8D5_PIN,(Copy_u8Data>>DIO_u8PIN5)&1)<<2);
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D4_GROUP,LCD_u8D4_PIN,(Copy_u8Data>>DIO_u8PIN4)&1)<<2);
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D3_GROUP,LCD_u8D3_PIN,(Copy_u8Data>>DIO_u8PIN3)&1)<<2);
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D2_GROUP,LCD_u8D2_PIN,(Copy_u8Data>>DIO_u8PIN2)&1)<<2);
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D1_GROUP,LCD_u8D1_PIN,(Copy_u8Data>>DIO_u8PIN1)&1)<<2);
	Local_u32ErrorState2 = (DIO_enuSetPinValue(LCD_u8D0_GROUP,LCD_u8D0_PIN,(Copy_u8Data>>DIO_u8PIN0)&1)<<2);
#else
#error"LCD mode is wrong"
#endif
	if (Local_u32ErrorState == 0x15555 && ( Local_u32ErrorState1 == 0x555555 || Local_u32ErrorState2 == 0x5555) ){
		Local_u8ErrorState = ES_OK;
	}


	return Local_u8ErrorState;
}

static ES_t LCD_enuLatch(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8ErrorState = 0;

	Local_u8ErrorState = DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8HIGH);
	_delay_ms(5);
	Local_u8ErrorState |= (DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW))<<2;
	_delay_ms(5);

	if(Local_u8ErrorState == 5)
	{
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
