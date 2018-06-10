/*
 * ShiftRegisterFactroy.h
 *
 *  Created on: 22.04.2016
 *      Author: butch
 */

#ifndef SHIFTREGISTERFACTORY_H_
#define SHIFTREGISTERFACTORY_H_

/**
 * this class is a push button implementation. it will use INPUT_PULLUP as pinMode for the given pin.
 * It will debounce the (un)pressing of the button. Only if state stays for longer than the debounceTimeMs it will switch the state.
 *
 * real state will give debounced value if button is pressed or not
 * logical state is the logical on / off status which will be flipped by each button press. It will flip after debounce time.
 *   If the button stays pressed it will flip only once. For further flip the button needs to be relased and pressed again.
 */
class ShiftRegisterFactory {
private:

	//Pin connected to ST_CP of 74HC595
	int _latchPin = 8;
	//Pin connected to SH_CP of 74HC595
	int _clockPin = 12;
	////Pin connected to DS of 74HC595
	int _dataPin = 11;

	// number of shift registers used
	int _numberOfRegisters;

	// number of shift registers is not known on compile time of this library. So we need to declare in this way.
	int* _currentValue=0;
	int* _newValue=0;




public:

	// sckPin=shiftPIN, rckPIN=storePIN, serPIN=dataPINm
	ShiftRegisterFactory(int latchPin, int clockPin, int dataPin, int numberOfRegisters);
	ShiftRegisterFactory();

	void clearNewValue();
	long readNewValue();
	int getCurrentValueSize();
	int getCurrentValue(int shiftRegisterId);

	int getNewValue(int shiftRegisterId);


	void setNewValue(int shiftRegisterId, int value);
	void setNewValueBit(int shiftRegisterId, int bitPosition, int Value);

	void writeNewValue();

	virtual ~ShiftRegisterFactory();

};

#endif /* SHIFTREGISTERFACTORY_H_ */
