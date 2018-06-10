/*
 * ShiftRegisterFactroy.cpp
 *
 *  Created on: 22.04.2016
 *      Author: butch
 */

#include "ShiftRegisterFactory.h"
#include "arduino.h"


/**
	shiftPin // Pin SCK an 74HC595
	storePin // PIN RCK an 74HC595
	dataPin  // Pin SER an 74HC595
 */
ShiftRegisterFactory::ShiftRegisterFactory()
{

}



ShiftRegisterFactory::ShiftRegisterFactory(int latchPin, int clockPin, int dataPin, int numberOfRegisters)
{
	// keep the variables for connection with shift register
	_latchPin=latchPin;
	_clockPin=clockPin;
	_dataPin=dataPin;

	// set the pin mode for shift register connections
	pinMode(_latchPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);

	// remember number of installed shift registers, managed by this factory
	_numberOfRegisters=numberOfRegisters;

	// creating arrays. Size is based on number of shift registers.

	_currentValue = new int [numberOfRegisters];
	_newValue = new int [numberOfRegisters];
	// initialize values of shift registers with 0;
	for (int i=0;i<numberOfRegisters;i++)
	{
		_currentValue[i]=0;
		_newValue[i]=0;
	}

	// activate the new value (0)
	writeNewValue();






}

ShiftRegisterFactory::~ShiftRegisterFactory()
{
	// TODO Auto-generated destructor stub
}

int ShiftRegisterFactory::getCurrentValueSize()
{
	Serial.println(sizeof(_currentValue));
	return sizeof(_currentValue);
}

/**
 * returns the currently active value. Returns -1 if out of bounds
 */
int ShiftRegisterFactory::getCurrentValue(int shiftRegisterId)
{
	if (shiftRegisterId >= _numberOfRegisters)
		{
			// fallback if out of bounds
			return -1;
		}
		else
		{
			return _currentValue[shiftRegisterId];
		}
}

/**
 * returns the newValue. Returns -1 if out of bounds
 */
int ShiftRegisterFactory::getNewValue(int shiftRegisterId)
{
	Serial.println(_newValue[shiftRegisterId],BIN);

	if (shiftRegisterId >= _numberOfRegisters)
	{
		// fallback if out of bounds
		return -1;
	}
	else
	{
		return _newValue[shiftRegisterId];
	}

}

/**
 * sets a new value (8bit) for a shift register)
 * prints serial error message if out of bounds
 */
void ShiftRegisterFactory::setNewValue(int shiftRegisterId, int value)
{
	if (shiftRegisterId < _numberOfRegisters)
	{
		_newValue[shiftRegisterId] = value;
	}
	else
	{
		// we are out of bounds
		Serial.print("\nOutOfBoundsException in ShiftRegisterFactory::setNewValue. Unable to write to register ");
		Serial.print(shiftRegisterId);
		Serial.print("\n");
	}
}

/**
 * sets a specific bit of the new value of a register to a specific value (0 or 1)
 */
void ShiftRegisterFactory::setNewValueBit(int shiftRegisterId, int bitPosition, int Value)
{
	bitWrite(_newValue[shiftRegisterId],bitPosition,Value);
}


void ShiftRegisterFactory::writeNewValue()
{
	// take the latchPin low so
	// the LEDs don't change while you're sending in bits:
	digitalWrite(_latchPin, LOW);



	for (int i=0; i<_numberOfRegisters; i++)
	{
		// shift out the bits for each register, one after another
		shiftOut(_dataPin, _clockPin, MSBFIRST, _newValue[i]);

		// update the _currentValue to _newValue
		_currentValue[i]=_newValue[i];
	}

	//take the latch pin high so the LEDs will light up:
	digitalWrite(_latchPin, HIGH);

}
