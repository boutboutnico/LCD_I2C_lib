/************************************************
 * This example code is in the public domain.
 * @file	LCD_I2C.ino
 * @brief	Demonstrates use of the LCD Library
 * @author	nboutin
 * @date	21/07/2011
 * 
 * Board	Arduino UNO R3
 * IDE		Atmel Studio 6.1
 * LCD I2C	PCM2004E6-2
 * Pin		Board	LCD
 *			SDA_20	SDA (blanc) + resistance pull-up 2k
 *			SCL_21	SCL (jaune) + resistance pull-up 2k
 *			5V		5V (rouge
 *			GND		GND	(noir)
 ***********************************************/

/************************************************
 * INCLUDE
 ***********************************************/
#include "stdlib.h"
#include "Wire.h"
#include "lcd_I2C.h"

LCD_I2C lcd(0x00, 4, 20);

void setup()
{
	lcd.begin();
}

void loop()
{
	static uint32_t cnt_loop = 0;
	cnt_loop++;
	
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

