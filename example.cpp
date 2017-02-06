/*
 * MULTI_7_SEG.cpp
 * GNU Public License
 * Created: 2/4/2017 
 * Author : Moshtak ALLAH
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "SEVEN_SEG.h"

uint8_t digitpins[] = {0,1,2,3,4,5,6,7};
SEVEN_SEG sevenanode = SEVEN_SEG(COMMON_ANODE, makePort(PORTB),0,1,2,3,4,5,6,7);


int main(void)
{
	sevenanode.seldigit_Port(&PORTD, digitpins, 8);
    sevenanode.ledtest();
    while (1) 
    {
		sevenanode.print(5,0);
		sevenanode.print(7,2);
    }
}

