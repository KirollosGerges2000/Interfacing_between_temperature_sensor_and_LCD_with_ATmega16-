/*
 * ADC.c
 *
 * Created: 6/20/2023 8:44:01 PM
 * Author : kerollos
 */ 


#include "ADC.c"
#include "lcd.c"
#include <stdlib.h>
volatile signed int volt=0;
float x=0;
int main()
{
	
LCD_Init(); /* initialize LCD driver */
ADC_init(); /* initialize ADC driver */
LCD_Clear(); /* clear LCD at the beginning */
	
while(1)
{
	
process();
	
	

}
}

void process (void)
	{
		LCD_String(" outdoorClimate ");
		
		/* display character 'C' on the screen "Temp =   C" */
	/* display this string "Temp =    " only once at LCD */

	LCD_Command(0xC0); //next line
LCD_String("Temperature=");
	LCD_xy(1,12); /* display the number every time at this position */
		volt = ADC_readChannel(3); /* read channel two where the temp sensor is connect */
		x=(float)(5*volt)/1023; // to gain the ADC
		x=x*100;
		lcd_into_string(x); /* display the temp on LCD screen */

if(x>100)
{
LCD_xy(1,15);
LCD_String("C");
}
else if(x>=10||x<=100)
{
	LCD_xy(1,14);
	LCD_String("C");
}
else 
{
	LCD_xy(1,12);
	LCD_String("C");
	}



	}
















