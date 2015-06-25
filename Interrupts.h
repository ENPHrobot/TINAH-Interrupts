#ifndef Interrupts_h
#define Interrupts_h

#include <phys253.h>
#include <avr/interrupt.h>

class Interrupts
{
public:
	Interrupts();
	void enableExternalInterrupt(unsigned int INTX, unsigned int mode);
	void disableExternalInterrupt(unsigned int INTX);
private:

};

#endif