/*
 * LCD_int.h
 *
 *  Created on: Oct 2, 2021
 *      Author: abosh
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

ES_t LCD_enuInit(void);

ES_t LCD_enuSendData(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuSendString(const char * Copy_pcString);

ES_t LCD_enuGoToPosition(u8 Copy_u8Line,u8 Copy_u8Column);

ES_t LCD_enuSendExtraCharacter(u8 Copy_Au8Arr,u8 Copy_u8PatternNumber,u8 Copy_u8NumberOfPatterns,u8 Copy_u8Line,u8 Copy_u8Column,u8 Copy_u8IncDec);

ES_t LCD_enuDisplayInt(s32 Copy_s32Number);

ES_t LCD_enuDisplayFloat(f32 Copy_f32Number);




#endif /* LCD_INT_H_ */
