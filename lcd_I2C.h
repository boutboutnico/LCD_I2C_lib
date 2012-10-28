/*
 LCDI2C.h - Library for controlling LCD through I2C.
 Created by Nicolas BOUTIN, July 21, 2011.
 Released into the public domain.
 */
#ifndef __LCDI2C__
#define __LCDI2C__

//#include "WProgram.h"
//#include "wire.h"
//#include <stdlib.h>
#include <Arduino.h>
#include <Wire.h>

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

class LCDI2C
{
public:
	LCDI2C(unsigned char LCDaddress, unsigned char nbRow, unsigned char nbColumn);

	void begin();
	void clear();
	void backlight(boolean on);
	void cursor(boolean on);
	void home();
	void cursorXY(unsigned char column, unsigned char row);
	void moveToRow(unsigned char row);
	void print(byte b);
	void print(char * string);
	void print(byte * data, byte quantity);
	void print(int num);
	void print(unsigned char column, unsigned char row, char * string);
	void print(unsigned char column, unsigned char row, int num);
	void custom(unsigned char code, byte * data);

private:
	unsigned char _address;
	unsigned char _maxRow;
	unsigned char _maxColumn;

};

#endif //__LCDI2C__

