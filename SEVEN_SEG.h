/*
 * SEVEN_SEG.h
 * GNU Public License
 * Created: 2/4/2017 
 * Author: Moshtak ALLAH
 */ 
#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

#include <avr/io.h>
#include <stdint.h>
#define bitRead(var, pin) (((var)>>(pin)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(var, bit, bitvalue) (bitvalue ? bitSet(var, bit) : bitClear(var, bit))
#define pinRead(port, pin) ((port) & 0x01<<(pin)) // read from port and value of (port)== PINR  COMMAND
#define makePort(value) (&value)
#define makePORTS(colport, colportDIR, rowport, rowportDIR, rowINPUTreg)   &colport, &colportDIR, &rowport, (&rowportDIR), (&rowINPUTreg)
#define LOW 0
#define HIGH 1
#define BLANK 16

#define COMMON_ANODE 1
#define COMMON_CATHODE 0
#define DIRECTLY 1
#define BYDRIVER 2
#define NODP 8

class SEVEN_SEG{
	public:
	SEVEN_SEG(char mode, volatile uint8_t* port, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG);
    SEVEN_SEG (char mode, volatile uint8_t*  port, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG, uint8_t pinDP);
	SEVEN_SEG(char mode, volatile uint8_t* port,  uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD);
	void ledtest();
	void print(unsigned char number, uint8_t digitNO);
	void clear();
	void setPoint();
	void clearPoint();
	void seldigit_Port(volatile uint8_t* seldigit_Port, uint8_t* seldigit_Pins, uint8_t NOpins);
	
	private:
	void init(char connection, char mode, volatile uint8_t*  port, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG, uint8_t pinDP);
	volatile uint8_t* DDRP_finder(volatile uint8_t *prt);
	char _pinarray[8];
	volatile uint8_t *_port;
	volatile uint8_t* _DDRP;
	volatile uint8_t* DIReg;
	volatile uint8_t* _seldigit_Port;
	uint8_t* _seldigit_Pins;
	uint8_t _NOpins;																
	char _mode;
	unsigned char _number;
	char _connection;
	
	};

#endif 