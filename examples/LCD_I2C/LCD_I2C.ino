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

// gets rid of annoying "depreciated conversion from string constant warning
#pragma GCC diagnostic ignored "-Wwrite-strings"

/************************************************
 * INCLUDE
 ***********************************************/
#include <stdlib.h>
#include "lcd_I2C.h"
#include "Wire.h"

LCD_I2C lcd(0x00, 4, 20);

void setup()
{
	lcd.begin();
}

void loop()
{
	uint32_t ui32_lcd_delay = 1500;
	uint32_t ui32_val = 12345;

	lcd.clear();
	lcd.print("-- Print String --");
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Print Integer --");
	lcd.print(0, 1, ui32_val);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Printf --");
	lcd.printf(0, 1, "%s", "Hello world all row!");
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Printf --");
	lcd.printf(0, 1, "Decimal a: %d", ui32_val);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Printf --");
	lcd.printf(0, 1, "Hex a: 0x%x", ui32_val);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Backlight OFF --");
	lcd.backlight(false);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Backlight ON --");
	lcd.backlight(true);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Cursor XY --");
	lcd.print(0, 1, "(5,3)");
	lcd.cursorXY(5, 3);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Cursor OFF --");
	lcd.cursor(false);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Cursor ON --");
	lcd.cursor(true);
	delay(ui32_lcd_delay);

	lcd.home();
	delay(ui32_lcd_delay);
}

