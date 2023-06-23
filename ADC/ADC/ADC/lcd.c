#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define LCD_Data_Dir DDRC
#define LCD_Command_Dir DDRD
#define LCD_Data_Port PORTC
#define LCD_Command_Port PORTD
#define RS PD4
#define RW PD5
#define EN PD6




void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);
	LCD_Command_Port &= ~(1<<RW);
	LCD_Command_Port |= (1<<EN);
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}

void LCD_Char (unsigned char char_data)
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);
	LCD_Command_Port &= ~(1<<RW);
	LCD_Command_Port |= (1<<EN);
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_Init (void)
{
	LCD_Command_Dir = 0xFF;
	LCD_Data_Dir = 0xFF;
	_delay_ms(20);
	
	LCD_Command (0x38);  //8_bit
	//LCD_Command(0x28); //4_bit
	LCD_Command (0x80);
	LCD_Command (0x01);  //to clear
	LCD_Command (0x0C);  //cursor off
	//LCD_Command(0x0E); //cursor on
}

void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);
	LCD_String(str);
}

void LCD_Clear()
{
	LCD_Command (0x01);
	LCD_Command (0x80);
}

void lcd_into_string(char data)
{
	char buff[16];
	itoa(data,buff,10);
	LCD_String(buff);


}


void LCD_Char_xy (char row, char pos, char *ch)
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);
	LCD_Char(ch);
}
void LCD_xy(char row, char pos)
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);
}