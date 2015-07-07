#include <avr/interrupt.h>
#include <Interrupts.h>

// Allocate function pointers for interrupt service routines
namespace {
void (*isr0)();
void (*isr1)();
void (*isr2)();
void (*isr3)();
}
ISR(INT0_vect) { (*isr0)();}
ISR(INT1_vect) { (*isr1)();}
ISR(INT2_vect) { (*isr2)();}
ISR(INT3_vect) { (*isr3)();}

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
void enableExternalInterrupt(unsigned int INTX, unsigned int mode)
{
	if (INTX > 3 || mode > 3 || mode == 1) return;
	cli();
	/* Allow pin to trigger interrupts        */
	EIMSK |= (1 << INTX);
	/* Clear the interrupt configuration bits */
	EICRA &= ~(1 << (INTX * 2 + 0));
	EICRA &= ~(1 << (INTX * 2 + 1));
	/* Set new interrupt configuration bits   */
	EICRA |= (mode & (1 << 1)) << (INTX * 2 + 0);
	EICRA |= (mode & (1 << 0)) << (INTX * 2 + 1);
	sei();
}

// Disables external interrupt pin
void disableExternalInterrupt(unsigned int INTX)
{
	if (INTX > 3) return;
	EIMSK &= ~(1 << INTX);
}

// Attach a function as the ISR for an enabled interrupt pin
void attachISR(unsigned int INTX, void (*f)())
{
	switch (INTX)
	{
	case INT0:
		isr0 = f;
		break;
	case INT1:
		isr1 = f;
		break;
	case INT2:
		isr2 = f;
		break;
	case INT3:
		isr3 = f;
		break;
	}
}