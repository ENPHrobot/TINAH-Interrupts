#include <avr/interrupt.h>
#include <Interrupts.h>

// Interrupts class constructor
Interrupts::Interrupts() {
    // Does nothing atm
}

/*  Enables an external interrupt pin
INTX: Which interrupt should be configured?
    INT0    - will trigger ISR(INT0_vect) // ISR(INT0_vect) is the ISR function
    INT1    - will trigger ISR(INT1_vect)
    INT2    - will trigger ISR(INT2_vect)
    INT3    - will trigger ISR(INT3_vect)
mode: Which pin state should trigger the interrupt?
    LOW     - trigger whenever pin state is LOW
    FALLING - trigger when pin state changes from HIGH to LOW
    RISING  - trigger when pin state changes from LOW  to HIGH 
sample usage:
	enableExternalInterrupt(INT0, RISING);
defining ISR's:
	ISR(INT0_vect) {function_here()};
*/
void Interrupts::enableExternalInterrupt(unsigned int INTX, unsigned int mode)
{
	if (INTX > 3 || mode > 3 || mode == 1) return;
	cli();
	/* Allow pin to trigger interrupts        */
	EIMSK |= (1 << INTX);
	/* Clear the interrupt configuration bits */
	EICRA &= ~(1 << (INTX*2+0));
	EICRA &= ~(1 << (INTX*2+1));
	/* Set new interrupt configuration bits   */
	EICRA |= (mode & (1 << 1)) << (INTX*2+0);
	EICRA |= (mode & (1 << 0)) << (INTX*2+1);
	sei();
}

// Disables external interrupt pin
void Interrupts::disableExternalInterrupt(unsigned int INTX)
{
	if (INTX > 3) return;
	EIMSK &= ~(1 << INTX);
}

/*void Interrupts::attachISR(unsigned int INTX, void (*tempISR)(void))
{
TODO    
}*/