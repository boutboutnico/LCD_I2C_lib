//#include "WProgram.h"
#include <Arduino.h>
#include <Wire.h>

#include "LCDI2C.h"

/****************/
/*    PUBLIC    */
/****************/
LCDI2C::LCDI2C(unsigned char LCDaddress, unsigned char nbRow, unsigned char nbColumn)
{
	_address = LCDaddress;
	_maxRow = nbRow;
	_maxColumn = nbColumn;

}

void LCDI2C::begin()
{
	Wire.begin(_address);
	clear();
}

void LCDI2C::clear()
{
	Wire.beginTransmission(_address);
	Wire.write(COMMAND);
	Wire.write(CLEAR);
	Wire.endTransmission();
	delay(15);
}

void LCDI2C::backlight(boolean on)
{
	Wire.beginTransmission(_address);
	Wire.write(COMMAND);

	if(on) Wire.write(BACKLIGHT_ON);
	else Wire.write(BACKLIGHT_OFF);

	Wire.endTransmission();
}

void LCDI2C::cursor(boolean on)
{

	Wire.beginTransmission(_address);
	Wire.write(COMMAND);

	if(on) Wire.write(CURSOR_ON);
	else Wire.write(CURSOR_OFF);

	Wire.endTransmission();
}

void LCDI2C::home()
{
	Wire.beginTransmission(_address);
	Wire.write(COMMAND);
	Wire.write(HOME);
	Wire.endTransmission();
}

void LCDI2C::cursorXY(unsigned char column, unsigned char row)
{

	if(column < 0 || column > _maxColumn - 1) column = 0;
	if(row < 0 || row > _maxRow - 1) row = 0;

	Wire.beginTransmission(_address);
	Wire.write(COMMAND);
	Wire.write(CURSOR_POS);
	Wire.write(column);
	Wire.write(row);
	Wire.endTransmission();
	delayMicroseconds(100);
}

void LCDI2C::moveToRow(unsigned char row)
{

	if(row < 0 || row > _maxRow - 1) row = 0;

	Wire.beginTransmission(_address);
	switch(row){
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

void LCDI2C::print(byte b)
{
	Wire.beginTransmission(_address);
	Wire.write(b);
	Wire.endTransmission();
}

void LCDI2C::print(char * string)
{
	Wire.beginTransmission(_address);
	Wire.write(string);
	Wire.endTransmission();
}

void LCDI2C::print(byte * data, byte quantity)
{
	Wire.beginTransmission(_address);
	Wire.write(data, quantity);
	Wire.endTransmission();
}

void LCDI2C::print(int num)
{
	char string[32]; //Not a good idea

	itoa(num, string, 10);
	print(string);

}

void LCDI2C::print(unsigned char column, unsigned char row, char * string)
{
	cursorXY(column, row);
	print(string);
}

void LCDI2C::print(unsigned char column, unsigned char row, int num)
{
	cursorXY(column, row);
	print(num);
}

void LCDI2C::custom(unsigned char code, byte * data)
{

	if(code < 8 || code > 15) code = 8;

	Wire.beginTransmission(_address);
	Wire.write(COMMAND);
	Wire.write(CUSTOM_CHAR);
	Wire.write(code);
	Wire.write(data, 8);
	Wire.endTransmission();
}

/*****************/
/*    PRIVATE    */
/*****************/

