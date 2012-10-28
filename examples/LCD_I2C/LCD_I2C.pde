/************************************************
 * This example code is in the public domain.
 * @file	LCD_I2C.pde
 * @brief	Demonstrates use of the LCD Library
 * @author	nboutin
 * @date	21/07/2011
 * 
 * Board	chipKit Max32
 * IDE		mpide-0022-chipkit-win-20110619
 * LCD I2C	PCM2004E6-2
 * Pin		Board	LCD
 *			SDA_20	SDA (blanc) + resistance pull-up 2k
 *			SCL_21	SCL (jaune) + resistance pull-up 2k
 *			5V		5V (rouge
 *			GND		GND	(noir)
 *	BUG FIX In file twi.c
 *			Function uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait)
 *			Comment the following
 *				//  if(address < 8)
 *				//  {
 *				//	  return 0;
 *				//  }
 ***********************************************/

/************************************************
 * INCLUDE
 ***********************************************/
#include <stdlib.h>
#include "lcd_I2C.h"
#include "Wire.h"

LCDI2C lcd(0x00, 4, 20);

void setup()
{
	lcd.begin();
}

void loop()
{
	lcd.clear();
	lcd.print("coucou ");
	delay(1000);

	lcd.printInt(2);
	delay(1000);

	lcd.backlight(false);
	delay(1000);
	lcd.backlight(true);
	delay(1000);

	lcd.clear();
	delay(1000);

	lcd.cursor(false);
	delay(1000);
	lcd.cursor(true);
	delay(1000);
	lcd.cursorXY(5, 3);
	delay(1000);

	lcd.moveToRow(0);
	delay(1000);
	lcd.moveToRow(1);
	delay(1000);
	lcd.moveToRow(2);
	delay(1000);
	lcd.moveToRow(3);
	delay(1000);

	lcd.home();
	delay(1000);
}

