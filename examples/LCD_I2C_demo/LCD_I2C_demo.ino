/************************************************
 * This example code is in the public domain.
 * @file	LCD_I2C.ino
 * @brief	Demonstrates use of the LCD Library
 * @author	Nicolas BOUTIN
 * @date	31/05/2013
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
#include "Arduino.h"
#include "Wire.h"
#include "Printable.h"

#include "lcd_I2C.h"

/**
 * The Streaming library must be included in order to use "operator<<"         
 * It can be find at the following address :
 * http://arduiniana.org/libraries/streaming/
 * I am not the author of it but it is a must-have
 */
#include "Streaming.h"

/*****************************************************************************
 * CLASS Printable
 *****************************************************************************/
class PrintableObject : public Printable
{
	private:
	uint8_t ui8_val;
	String my_name;

	public:
	PrintableObject(uint8_t val, String name)
	{
		ui8_val = val;
		my_name = name;
	}
	
	virtual size_t printTo(Print& p) const
	{
		p << "My name is " << my_name << endl;
		p << "Value :" << ui8_val << endl;
	}
};

/*****************************************************************************
 * Object instantiation
 *****************************************************************************/
LCD_I2C lcd(0x00, 4, 20);

/*****************************************************************************
 * Setup
 *****************************************************************************/
void setup()
{
	lcd.begin();
}

/*****************************************************************************
 * Main Loop
 *****************************************************************************/
void loop()
{
	static uint32_t cnt_loop = 0;
	cnt_loop++;
	
	uint32_t ui32_lcd_delay = 3000;
	
	uint8_t uc_val = 0xFF;
	int32_t i32_val = -456798;
	uint32_t ui32_val = 0xFFFFFFFF;
	float f_val = 1234.89;

	lcd.clear();
	lcd << "-- Operator << --" << endl;
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.println(F("Const char in flash"));
	lcd.println(F("I am in flash !"));
	delay(ui32_lcd_delay);
	
	lcd.clear();
	lcd.println(F("-- Print String --"));
	String string("I am a string !");
	lcd << string << endl;
	delay(ui32_lcd_delay);
	
	lcd.clear();
	lcd << "-- Print char --" << endl;
	lcd << "char : " << 'a' << endl;
	delay(ui32_lcd_delay);
	
	lcd.clear();
	lcd << "-- Print Printable --" << endl;
	PrintableObject my_object(15, "my object");
	lcd << my_object << endl;
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd << "-- Print number --" << endl;
	lcd << "uint8_t: " << uc_val << endl;
	lcd << "uint8_t: 0x" << _HEX(uc_val) << endl;
	lcd << "uint8_t: 0b" << _BIN(uc_val) << endl;
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd << "-- Print number --" << endl;
	lcd << "int32_t: " << i32_val << endl;
	lcd << "int32_t: 0x" << _HEX(i32_val) << endl;
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd << "-- Print float --" << endl;
	lcd << "float: " << f_val << endl;
	delay(ui32_lcd_delay);
	
	lcd.clear();
	lcd << "-- Backlight OFF --" << endl;
	lcd.backlight(false);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd << "-- Backlight ON --" << endl;
	lcd.backlight(true);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd << "-- CursorXY (5,3) --" << endl;
	lcd.cursorXY(5, 3);
	lcd << 'X';
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd << "- CursorXY (10,2) -" << endl;
	lcd << _XY(10, 2) << 'X';
	delay(ui32_lcd_delay);
	
	lcd.clear();
	lcd.print("-- Cursor OFF --");
	lcd.cursor(false);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd.print("-- Cursor ON --");
	lcd.cursor(true);
	delay(ui32_lcd_delay);

	lcd.clear();
	lcd << "-- Cursor Home --" << endl;
	lcd.home();
	delay(ui32_lcd_delay);
	
	lcd.clear();
	lcd.cursor(false);
	
	for(uint8_t j = 0; j < 4; j++)
	{
		uint8_t i = 0;
		for (i = 0; i < 13; i++) //move string to right
		{
			lcd.cursorXY(i, 1);
			lcd << " Hello ";
			delay(100); //delay 100ms
		}
		for (; i > 0; i--) //move string to left
		{
			lcd.cursorXY(i, 1);
			lcd << " Hello ";
			delay(100);
		}
	}
	
	lcd.clear();
	lcd << _XY(1,0) << "Thanks for watching" << endl;
	delay(10000);
}

/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
