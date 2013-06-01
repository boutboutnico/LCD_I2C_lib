/*
  lcd_I2C.h - Base class that provides basic function to drive a 
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
 * @ file	lcd_I2C.h
 * @brief	Library for controlling LCD through I2C.
 * @author	Nicolas BOUTIN
 * @date	01/06/2013
 * @version	1.0
 */
#ifndef __LCD_I2C__
#define __LCD_I2C__

/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include "Arduino.h"
#include "Wire.h"

/**
 * The Streaming library must be included in order to use "operator<<"         
 * It can be find at the following address :
 * http://arduiniana.org/libraries/streaming/
 * I am not the author of it but it is a must-have
 */
#include "Streaming.h"

/**
 * In order to use "<< endl;" work with Arduino 1.05 and below, 
 * a little modification is needed in the "Print.h"
 * It can be find here : arduino-1.0.5\hardware\arduino\cores\arduino
 * The line : "size_t println(void);"
 * becomes : "virtual size_t println(void);"
 */

/*****************************************************************************
 * CLASS
 *****************************************************************************/
/**
 * @class 	LCD_I2C
 * @brief	xx
 * @author	Nicolas BOUTIN
 * @date	31/05/2013
 */
class LCD_I2C : public Print
{
private:
	uint8_t ui8_address;
	uint8_t ui8_max_row;
	uint8_t ui8_max_column;
	uint8_t ui8_current_row;
	
	// Constants
	static const uint8_t COMMAND		= 0x1B;
	static const uint8_t CLEAR			= 0x43;
	static const uint8_t CURSOR_ON		= 0x53;
	static const uint8_t CURSOR_OFF		= 0x73;
	static const uint8_t BACKLIGHT_ON	= 0x42;
	static const uint8_t BACKLIGHT_OFF	= 0x62;
	static const uint8_t HOME			= 0x48;
	static const uint8_t CURSOR_POS		= 0x4C;
	static const uint8_t CUSTOM_CHAR	= 0x44;
	static const uint8_t ROW_0			= 0x01;
	static const uint8_t ROW_1			= 0x02;
	static const uint8_t ROW_2			= 0x03;
	static const uint8_t ROW_3			= 0x04;

public:
	LCD_I2C(){}
	LCD_I2C(const uint8_t i_ui8_lcd_address, const uint8_t i_ui8_nb_row = 4, const uint8_t i_ui8_nb_column = 20);
	
	void begin();
	void clear();
	void backlight(const boolean i_b_on);
	void cursor(const boolean i_b_on);
	void home();
	void cursorXY(const uint8_t i_ui8_x, const uint8_t i_ui8_y);
	void moveToRow(const uint8_t i_ui8_y);
	void custom(const uint8_t i_ui8_code, const byte * i_byte_data);
	
	// Inherited from Print
	virtual size_t write(uint8_t);
	
	size_t print(const __FlashStringHelper *);
	size_t print(const String &);
	size_t print(const char[]);
	size_t print(char);
	size_t print(unsigned char, int = DEC);
	size_t print(int, int = DEC);
	size_t print(unsigned int, int = DEC);
	size_t print(long, int = DEC);
	size_t print(unsigned long, int = DEC);
	size_t print(double, int = 2);
	size_t print(const Printable&);
	
	size_t println(const __FlashStringHelper *);
	size_t println(const String &s);
	size_t println(const char[]);
	size_t println(char);
	size_t println(unsigned char, int = DEC);
	size_t println(int, int = DEC);
	size_t println(unsigned int, int = DEC);
	size_t println(long, int = DEC);
	size_t println(unsigned long, int = DEC);
	size_t println(double, int = 2);
	size_t println(const Printable&);
	size_t println(void);
	
private:
	uint8_t incrementCurrentRow();
};

/*****************************************************************************
 * OTHER
 *****************************************************************************/

/**
 * @struct	_XY
 * @brief	Structure to used with operator<<, it allows to set the cursor
 *			at the desired position.
 */
typedef struct _XY
{
	uint8_t x;
	uint8_t y;
	_XY(uint8_t x, uint8_t y) : x(x), y(y) {}
};

/**
 * @brief	Implement operator<< with the structure _XY to set the cursor
 *			at the desired position before or after writing
 *			To be used like this : lcd << _XY(10, 2)
 */
inline Print& operator<<(LCD_I2C& obj, const _XY& arg)
{
	obj.cursorXY(arg.x, arg.y);
	return obj;
}

#endif //__LCD_I2C__
/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
