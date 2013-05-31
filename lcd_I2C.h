/*
 LCDI2C.h - Library for controlling LCD through I2C.
 Created by Nicolas BOUTIN, July 21, 2011.
 Released into the public domain.
 */
#ifndef __LCDI2C__
#define __LCDI2C__

/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include "Arduino.h"
#include "Wire.h"

#include "stdarg.h"

/*****************************************************************************
 * DEFINITION
 *****************************************************************************/
#define COMMAND			0x1B
#define CLEAR			0x43
#define CURSOR_ON		0x53
#define	CURSOR_OFF		0x73
#define BACKLIGHT_ON	0x42
#define BACKLIGHT_OFF	0x62
#define HOME			0x48
#define CURSOR_POS		0x4C
#define CUSTOM_CHAR		0x44
#define ROW_1			0x01
#define ROW_2			0x02
#define ROW_3			0x03
#define ROW_4			0x04

/*****************************************************************************
 * CLASS
 *****************************************************************************/
/**
 * @class 	xx
 * @brief	xx
 * @author	boutboutnico
 * @date	25 juil. 2012
 */
class LCD_I2C
{
private:
	uint8_t ui8_address;
	uint8_t ui8_max_row;
	uint8_t ui8_max_column;

public:
	LCD_I2C(const uint8_t i_ui8_lcd_address, const uint8_t i_ui8_nb_row, const uint8_t i_ui8_nb_column);

	void begin();
	void clear();
	void backlight(bool i_b_on);
	void cursor(bool i_b_on);
	void home();
	void cursorXY(uint8_t i_ui8_x, uint8_t i_ui8_y);
	void moveToRow(uint8_t i_ui8_y);

	void print(byte i_byte_value);
	void print(const char* i_c8_string);
	void print(byte * data, byte quantity);
	void print(uint32_t i_ui32_value);
	void print(uint8_t i_ui8_x, uint8_t i_ui8_y, const char* i_c8_string);
	void print(uint8_t i_ui8_x, uint8_t i_ui8_y, uint32_t i_ui32_value);
	
	void printf(char *fmt, ...);
	void printf(uint8_t i_ui8_x, uint8_t i_ui8_y, char *fmt, ...);

	void custom(uint8_t i_ui8_code, byte * i_byte_data);

};

#endif //__LCDI2C__
/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
