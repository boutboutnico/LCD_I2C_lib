/*
  lcd_I2C.cpp - Base class that provides basic function to drive a 
  textual LCD equipped with an I2C backpack
  Copyright (c) 2013 Nicolas BOUTIN.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/**
 * @file	lcd_I2C.cpp
 * @brief	Library for controlling LCD through I2C.
 * @author	Nicolas BOUTIN
 * @date	01/06/2013
 * @version	1.0
 */

/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include "lcd_I2C.h"

/*****************************************************************************
 * PUBLIC IMPLEMENTATION
 *****************************************************************************/

LCD_I2C::LCD_I2C(const uint8_t i_ui8_lcd_address, const uint8_t i_ui8_nb_row, const uint8_t i_ui8_nb_column)
{
	ui8_address = i_ui8_lcd_address;
	ui8_max_row = i_ui8_nb_row;
	ui8_max_column = i_ui8_nb_column;
	ui8_current_row = 0;
}

size_t LCD_I2C::write(uint8_t ui8_value)
{
	Wire.beginTransmission(ui8_address);
	Wire.write(ui8_value);
	Wire.endTransmission();
	return 1;
}

void LCD_I2C::begin()
{
	Wire.begin(ui8_address);
	clear();
}

void LCD_I2C::clear()
{
	ui8_current_row = 0;
	
	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(CLEAR);
	Wire.endTransmission();
	delay(15);
}

void LCD_I2C::backlight(boolean i_b_on)
{
	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);

	if(i_b_on) Wire.write(BACKLIGHT_ON);
	else Wire.write(BACKLIGHT_OFF);

	Wire.endTransmission();
}

void LCD_I2C::cursor(boolean i_b_on)
{
	Wire.beginTransmission(ui8_address);
	
	Wire.write(COMMAND);
	if(i_b_on) Wire.write(CURSOR_ON);
	else Wire.write(CURSOR_OFF);

	Wire.endTransmission();
}

void LCD_I2C::home()
{
	ui8_current_row = 0;
	
	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(HOME);
	Wire.endTransmission();
}

void LCD_I2C::cursorXY(const uint8_t i_ui8_x, const uint8_t i_ui8_y)
{
	uint8_t x = i_ui8_x;
	uint8_t y = i_ui8_y;
	
	if(i_ui8_x > ui8_max_column - 1) x = 0;
	if(i_ui8_y > ui8_max_row - 1) y = 0;
	
	ui8_current_row = y;

	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(CURSOR_POS);
	Wire.write(x);
	Wire.write(y);
	Wire.endTransmission();
	delayMicroseconds(100);
}

void LCD_I2C::moveToRow(const uint8_t i_ui8_y)
{
	uint8_t y = i_ui8_y;
	
	if(i_ui8_y > ui8_max_row - 1) y = 0;
	
	ui8_current_row = y;

	Wire.beginTransmission(ui8_address);
	switch(y){
	case 0:
		Wire.write(ROW_0);
		break;
	case 1:
		Wire.write(ROW_1);
		break;
	case 2:
		Wire.write(ROW_2);
		break;
	case 3:
		Wire.write(ROW_3);
		break;
	default:
		Wire.write(ROW_0);
		break;
	}
	Wire.endTransmission();
}

void LCD_I2C::custom(const uint8_t i_ui8_code, const byte * i_byte_data)
{
	uint8_t code = i_ui8_code;
	
	if(i_ui8_code < 8 || i_ui8_code > 15) code = 8;

	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(CUSTOM_CHAR);
	Wire.write(code);
	Wire.write(i_byte_data, 8);
	Wire.endTransmission();
}

size_t LCD_I2C::print(const __FlashStringHelper *fsh)
{
	Print::print(fsh);
}

size_t LCD_I2C::print(const String& string)
{
	Print::print(string);
}

size_t LCD_I2C::print(const char string[])
{
	Print::print(string);
}

size_t LCD_I2C::print(char c)
{
	Print::print(c);
}

size_t LCD_I2C::print(unsigned char c, int base)
{
	Print::print(c, base);
}

size_t LCD_I2C::print(int i, int base)
{
	Print::print(i, base);
}

size_t LCD_I2C::print(unsigned int ui, int base)
{
	Print::print(ui, base);
}

size_t LCD_I2C::print(long l, int base)
{
	Print::print(l, base);
}

size_t LCD_I2C::print(unsigned long ul, int base)
{
	Print::print(ul, base);
}

size_t LCD_I2C::print(double num, int digits)
{
	Print::print(num, digits);
}

size_t LCD_I2C::print(const Printable& printable)
{
	Print::print(printable)	;
}

size_t LCD_I2C::println(const __FlashStringHelper* fsh)
{
	Print::print(fsh);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(const String &s)
{
	Print::print(s);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(const char string[])
{
	Print::print(string);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(char c)
{
	Print::print(c);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(unsigned char b, int base)
{
	Print::print(b, base);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(int num, int base)
{
	Print::print(num, base);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(unsigned int num, int base)
{
	Print::print(num, base);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(long num, int base)
{
	Print::print(num, base);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(unsigned long num, int base)
{
	Print::print(num, base);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(double num, int digits)
{
	Print::print(num, digits);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(const Printable& printable)
{
	Print::print(printable);
	moveToRow(incrementCurrentRow());
}

size_t LCD_I2C::println(void)
{
	moveToRow(incrementCurrentRow());
}

/*****************************************************************************
 * PRIVATE IMPLEMENTATION
 *****************************************************************************/

uint8_t LCD_I2C::incrementCurrentRow()
{
	if(++ui8_current_row > (ui8_max_row - 1)) ui8_current_row = 0;
	return ui8_current_row;
}

/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
