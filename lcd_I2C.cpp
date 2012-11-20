/*************************************************************************//**
 * @file 	lcd_I2C.cpp
 * @brief	xx
 * @author	Nicolas BOUTIN
 * @date	01/11/2012
 * @module	LCD_I2C
 *****************************************************************************/

/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include <Arduino.h>
#include <Wire.h>

#include "lcd_I2C.h"
/*****************************************************************************
 * GLOBALE VARIABLE
 *****************************************************************************/

/*****************************************************************************
 * PUBLIC IMPLEMENTATION
 *****************************************************************************/
/**
 *
 * @param i_ui8_lcd_address
 * @param i_ui8_nb_row
 * @param i_ui8_nb_column
 */
LCD_I2C::LCD_I2C(const uint8_t i_ui8_lcd_address, const uint8_t i_ui8_nb_row, const uint8_t i_ui8_nb_column)
{
	ui8_address = i_ui8_lcd_address;
	ui8_max_row = i_ui8_nb_row;
	ui8_max_column = i_ui8_nb_column;
}

void LCD_I2C::begin()
{
	Wire.begin(ui8_address);
	clear();
}

void LCD_I2C::clear()
{
	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(CLEAR);
	Wire.endTransmission();
	delay(15);
}

void LCD_I2C::backlight(bool i_b_on)
{
	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);

	if(i_b_on) Wire.write(BACKLIGHT_ON);
	else Wire.write(BACKLIGHT_OFF);

	Wire.endTransmission();
}

void LCD_I2C::cursor(bool i_b_on)
{

	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);

	if(i_b_on) Wire.write(CURSOR_ON);
	else Wire.write(CURSOR_OFF);

	Wire.endTransmission();
}

void LCD_I2C::home()
{
	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(HOME);
	Wire.endTransmission();
}

void LCD_I2C::cursorXY(uint8_t i_ui8_x, uint8_t i_ui8_y)
{
	if(i_ui8_x < 0 || i_ui8_x > ui8_max_column - 1) i_ui8_x = 0;
	if(i_ui8_y < 0 || i_ui8_y > ui8_max_row - 1) i_ui8_y = 0;

	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(CURSOR_POS);
	Wire.write(i_ui8_x);
	Wire.write(i_ui8_y);
	Wire.endTransmission();
	delayMicroseconds(100);
}

void LCD_I2C::moveToRow(uint8_t i_ui8_y)
{

	if(i_ui8_y < 0 || i_ui8_y > ui8_max_row - 1) i_ui8_y = 0;

	Wire.beginTransmission(ui8_address);
	switch(i_ui8_y){
	case 1:
		Wire.write(ROW_1);
		break;
	case 2:
		Wire.write(ROW_2);
		break;
	case 3:
		Wire.write(ROW_3);
		break;
	case 4:
		Wire.write(ROW_4);
		break;
	}
	Wire.endTransmission();
}

void LCD_I2C::print(byte i_byte_value)
{
	Wire.beginTransmission(ui8_address);
	Wire.write(i_byte_value);
	Wire.endTransmission();
}

void LCD_I2C::print(const char* i_c8_string)
{
	if(i_c8_string == NULL) return;

	Wire.beginTransmission(ui8_address);
	Wire.write(i_c8_string);
	Wire.endTransmission();
}

void LCD_I2C::print(byte * data, byte quantity)
{
	Wire.beginTransmission(ui8_address);
	Wire.write(data, quantity);
	Wire.endTransmission();
}

/**
 * @brief	str should be an array long enough to contain any possible value:
 * 			(sizeof(int)*8+1) for radix=2, i.e. 17 bytes in 16-bits platforms
 * 			and 33 in 32-bits platforms.
 *
 * @param i_ui32_value
 */
void LCD_I2C::print(uint32_t i_ui32_value)
{
	char string[ui8_max_column]; //Not a good idea

	itoa(i_ui32_value, string, 10);
	print(string);
}

void LCD_I2C::print(uint8_t i_ui8_x, uint8_t i_ui8_y, const char* i_c8_string)
{
	cursorXY(i_ui8_x, i_ui8_y);
	print(i_c8_string);
}

void LCD_I2C::print(uint8_t i_ui8_x, uint8_t i_ui8_y, uint32_t i_ui32_value)
{
	cursorXY(i_ui8_x, i_ui8_y);
	print(i_ui32_value);
}

void LCD_I2C::printf(char *fmt, ...)
{
	char tmp[ui8_max_column]; // resulting string limited to 20 chars
	va_list args;
	va_start(args, fmt);
	vsnprintf(tmp, ui8_max_column, fmt, args);
	va_end(args);
	print(tmp);
}

void LCD_I2C::printf(uint8_t i_ui8_x, uint8_t i_ui8_y, char *fmt, ...)
{
	cursorXY(i_ui8_x, i_ui8_y);

	char tmp[ui8_max_column + 1]; // resulting string limited to 20 chars
	va_list args;
	va_start(args, fmt);
	vsnprintf(tmp, ui8_max_column + 1, fmt, args);
	va_end(args);
	print(tmp);
}

void LCD_I2C::custom(uint8_t i_ui8_code, byte * i_byte_data)
{

	if(i_ui8_code < 8 || i_ui8_code > 15) i_ui8_code = 8;

	Wire.beginTransmission(ui8_address);
	Wire.write(COMMAND);
	Wire.write(CUSTOM_CHAR);
	Wire.write(i_ui8_code);
	Wire.write(i_byte_data, 8);
	Wire.endTransmission();
}

/*****************************************************************************
 * PRIVATE IMPLEMENTATION
 *****************************************************************************/

/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
