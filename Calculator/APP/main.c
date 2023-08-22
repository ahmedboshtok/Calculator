/*
 * main.c
 *
 *  Created on: Oct 2, 2021
 *      Author: Ahmed El-Gaafrawy
 */
#include "../LIBRARIES/stdTypes.h"
#include "../LIBRARIES/errorState.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEYPAD/Keypad_int.h"
#include <util/delay.h>

int stringToInt(const char* str);
void IntToString (char* str, int number );
u8 strComp(const char * str1 , const char * str2);

int main()
{
	int i=0,j=0;

	u8 key,k;
	int Result;
	char buffer[15];
	LCD_enuInit();
	Keypad_enuInit();
	LCD_enuSendString("welcome to cal.");
	LCD_enuSendCommand(FORCE_CURSOR_START_SECOND_LINE);
	_delay_ms(1000);
	while (1){
		LCD_enuSendCommand(CLEAR_DISPLAY);
		char num1[7],num2[7];
		while(i < 7){
			Keypad_enuGetPressedKey(&key);
			if (key != KEYPAD_NOT_PRESSED){
				if (key == '+' || key =='-' || key == '/' || key == '*'){
					k = key;
					LCD_enuSendData(k);
					num1[i] = '\0';
					break;
				}
				num1[i++] = key;


				LCD_enuSendData(key);
			}

		}



		while(j < 7 ){
			Keypad_enuGetPressedKey(&key);
			if (key != KEYPAD_NOT_PRESSED){
				if (key == '='){
					LCD_enuSendData(key);
					num2[j] = '\0';
					break;
				}
				num2[j++] = key;
				LCD_enuSendData(key);
			}

		}

		int num_1 = stringToInt(num1);
		int num_2 = stringToInt(num2);
		switch (k){
		case '+':
			Result = num_1 + num_2;
			break;
		case '-':
			Result = num_1 - num_2;
			break;
		case '*':
			Result = num_1 * num_2;
			break;
		case '/':
			Result = num_1 / num_2;
			break;



		}
		IntToString(buffer,Result);
		LCD_enuGoToPosition(2,1);
		LCD_enuDisplayInt(Result);
		_delay_ms(5000);






	}


	return 0;
}


u8 strComp(const char * str1 , const char * str2)
{
	int i=0;
	for (i=0; str1[i] != '\0' ;i++)
	{
		if (str1[i]!=str2[i])
			return 0;
	}
	if (str2[i] == '\0')
		return 1;
	return 0;
}

int stringToInt(const char* str){
	int sign =1, result =0,i=0;
	if (str[0]== '-'){
		sign = -1;
		i++;

	}
	while (str[i]!='\0'){
		int digit = str[i] - '0';
		result = result * 10 + digit;
		i++;
	}
	return sign * result;
}
void IntToString (char* str, int number ){
	int i =0 , sign,j;
	char temp;
	if (number < 0){
		sign =-1;
		number = -number;
	}
	else {
		sign =1;
	}
	do {
		str[i++]=number %10 +'0';
		number /= 10;
	}while (number >0);

	if (sign == -1){
		str[i++] = '-';

	}
	str[i] = '\0';
	for (j =0;j<i;j++){
		temp = str[j];
		str[j] = str[i - j -1];
		str [ i - j -1] = temp;



	}
}
