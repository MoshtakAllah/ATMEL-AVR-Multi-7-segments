/*
 * SEVEN_SEG.cpp
 * GNU Public License
 * Created: 2/4/2017 
 * Author: Moshtak ALLAH
 */ 
#include "SEVEN_SEG.h"
#include <stdint.h>
#include <util/delay.h>

 //										 A, B, C, D, E, F, G
static const int8_t symbol[17][7]= {    {1, 1, 1, 1, 1, 1, 0}, //0
									    {0, 1, 1, 0, 0, 0, 0}, //1
									    {1, 1, 0, 1, 1, 0, 1}, //2
									    {1, 1, 1, 1, 0, 0, 1}, //3
									    {0, 1, 1, 0, 0, 1, 1}, //4
										{1, 0, 1, 1, 0, 1, 1}, //5
										{1, 0, 1, 1, 1, 1, 1}, //6
										{1, 1, 1, 0, 0, 0, 0}, //7
										{1, 1, 1, 1, 1, 1, 1}, //8
										{1, 1, 1, 0, 0, 1, 1}, //9
										{1, 1, 1, 0, 1, 1, 1}, //A
										{0, 0, 1, 1, 1, 1, 1}, //b
										{1, 0, 0, 1, 1, 1, 0}, //C
										{0, 1, 1, 1, 1, 0, 1}, //d
										{1, 0, 0, 1, 1, 1, 1}, //E
										{1, 0, 0, 0, 1, 1, 1}, //F
										{0, 0, 0, 0, 0, 0, 0}  //BLANK
									};

SEVEN_SEG ::SEVEN_SEG (char mode, volatile uint8_t*  port, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG){
	init(DIRECTLY, mode, port, pinA, pinB, pinC, pinD, pinE, pinF, pinG, NODP);	
}

SEVEN_SEG ::SEVEN_SEG (char mode, volatile uint8_t*  port, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG, uint8_t pinDP){
	init(DIRECTLY, mode, port, pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP);
}

SEVEN_SEG::SEVEN_SEG(char mode, volatile uint8_t* port,  uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD){

init(BYDRIVER, mode, port, pinA, pinB, pinC, pinD,0,0,0,NODP);	
}

void SEVEN_SEG::init(char connection, char mode, volatile uint8_t*  port, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG, uint8_t pinDP){
	_connection = connection;
	_mode = mode;
	_port = port;
	_pinarray[0] = pinA;
	_pinarray[1] = pinB;
	_pinarray[2] = pinC;
	_pinarray[3] = pinD;
	_pinarray[4] = pinE;
	_pinarray[5] = pinF;
	_pinarray[6] = pinG;
	_pinarray[7] = pinDP;
 DIReg = DDRP_finder(_port);
	
 if (_connection == DIRECTLY)
 {
	// pins set as output and initialized to blank state
	for (uint8_t i=0; (_pinarray[7]==NODP)? (i<7): (i<8); i++)
	{
	 bitSet(*DIReg, _pinarray[i] ) ;
	 bitWrite(*_port, _pinarray[i], _mode ^ LOW); 
	}
 }
 else if (_connection == BYDRIVER)
 {
	// pins set as output and initialized to blank state
	for (uint8_t i=0; i<4; i++)
	{
	 bitSet(*DIReg, _pinarray[i] ) ;
	 bitWrite(*_port, _pinarray[i], _mode ^ LOW);
	}
 }	
}
	
void SEVEN_SEG ::print (unsigned char number, uint8_t digitNO){
	_number = number;
	if (_number=='A') _number=10;
	if (_number=='b') _number=11;
	if (_number=='c') _number=12;
	if (_number=='d') _number=13;
	if (_number=='E') _number=14;
	if (_number=='F') _number=15;
	if ((_number==' ') || (_number == BLANK)) _number=16;
		
	if (_connection == DIRECTLY)
	{
		for (uint8_t i=0; i<7; i++)
		{
			bitWrite(*_port, _pinarray[i], (symbol[_number][i] ^ _mode));
		}
	}
	else if (_connection == BYDRIVER)
	{
		for (unsigned char i=0; i<4; i++)
		{
		bitWrite(*_port,_pinarray[i], bitRead(_number, i));
		}
	}
	
	bitWrite(*_seldigit_Port, _seldigit_Pins[digitNO], _mode);
	_delay_ms(1);
	bitWrite(*_seldigit_Port, _seldigit_Pins[digitNO], _mode ^ HIGH);
	
}	

void SEVEN_SEG::ledtest()
{
				if (_connection == DIRECTLY)
				{
					for (uint8_t i=0;(_pinarray[7]==NODP)? (i<7) : (i<8) ; i++)
					{
						bitWrite(*_port, _pinarray[i], (HIGH ^ _mode));
					}
				}
				else if (_connection == BYDRIVER)
				{
					for (unsigned char i=0; i<4; i++)
					{
						bitWrite(*_port,_pinarray[i], HIGH);
					}
				}
		for (uint8_t i=0; i<_NOpins; i++) // select all digits
		{
			bitWrite(*_seldigit_Port, _seldigit_Pins[i], _mode);
		}
	_delay_ms(2000);
	clear(); // then clear
}

void SEVEN_SEG::clear()
{
	for (uint8_t i=0; i<_NOpins; i++)
	{
		bitWrite(*_seldigit_Port, _seldigit_Pins[i], _mode ^ HIGH);
	}
	clearPoint();
}

void SEVEN_SEG::setPoint()
{	if (_pinarray[7] != NODP)
	{
		bitWrite(*_port, _pinarray[7], HIGH ^ _mode);
	}
}

void SEVEN_SEG::clearPoint()
{
	if (_pinarray[7] != NODP){
		bitWrite(*_port, _pinarray[7], LOW ^ _mode);
	}
}

void SEVEN_SEG::seldigit_Port(volatile uint8_t* seldigit_Port, uint8_t* seldigit_Pins, uint8_t NOpins){
	_seldigit_Port = seldigit_Port;
	_seldigit_Pins = seldigit_Pins;
	_NOpins = NOpins;

	volatile uint8_t* selectDDreg = DDRP_finder(_seldigit_Port);
	
	for (uint8_t i=0 ; i<NOpins; i++)  // make digit selection port pins output
	{
		bitSet((*selectDDreg),seldigit_Pins[i]);
	}
		
}

volatile uint8_t* SEVEN_SEG::DDRP_finder(volatile uint8_t *segPort){
	
	if (segPort == &PORTB)	    return &DDRB;
	else if (segPort == &PORTC) return &DDRC;
	else if (segPort == &PORTD) return &DDRD;
	#if defined(PORTE)
	else if (segPort == &PORTE) return &DDRE;
	#endif
	return 0;
}

