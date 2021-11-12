/*==========================================================================
 * File Name: timer.c
 * Date: 25 October 2021
 * Description: The main Source file of the project
 * Author: Jouliana Nabil
 ===========================================================================*/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/***************************************************************************************************************************************************
 *                                                                GLOBAL VARIABLES                                                                 *
 **************************************************************************************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/***************************************************************************************************************************************************
 *                                                            INTERRUPT SERVICE ROUTINE                                                            *
 **************************************************************************************************************************************************/
ISR (TIMER0_OVF_vect)
{
	if (g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR (TIMER0_COMP_vect)
{
	if (g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}
/***************************************************************************************************************************************************
 *                                                              FUNCTION DEFINITIONS                                                               *
 **************************************************************************************************************************************************/
/*
 * Function Name: TIMER0_init
 * Inputs:
 * * config_ptr: Pointer of ICU_ConfigType Structure
 * * initial_value: Initial value of the timer
 * * compare_value: Compare value of the timer that has a value greater than 0 in CTC mode
 * Return Value: Void
 * Description: Initialize TIMER0 Driver
 */
void TIMER0_init (const TIMER0_ConfigType * config_ptr)
{
	/* Timer/Counter Control Register:
	 * * Force Output Compare is active as the required is Non_PWM mode: FOC0 = 1
	 * * Waveform Generation Mode will be selected according to the value of mode given by the user using configuration type structure
	 * * Compare Match Output Mode will be activated when the user use CTC mode and its value selected by the user using configuration type structure
	 * * Clock Select will be selected according to the value of clock given by the user using configuration type structure
	 */
	TCCR0 |= (1<<FOC0);
	TCCR0 = (TCCR0 & 0xB7) | (((config_ptr -> mode) & 0x01) << 6) | (((config_ptr -> mode) & 0x02) << 3); /* Value of WGM00 & WGM01 */
	TCCR0 = (TCCR0 & 0xCF) | ((config_ptr -> compare) << 5); /* Value of COM00 & COM01 */
	TCCR0 = (TCCR0 & 0xF8) | (config_ptr -> clock); /* Value of CS00 , CS01 & CS02 */

	if ((config_ptr -> mode) == CTC)
	{
		DDRB |= (1<<PB3); /* Set OC0 @ PB3 as Output Pin */
		TIMSK |= (1<<OCIE0); /* Enable Compare Interrupt for Timer0 */
		/* Output Compare Register: contains the compare value of the timer when using CTC mode */
		OCR0 = (config_ptr -> compare_value);
	}
	else if ((config_ptr -> mode) == NORMAL)
	{
		TIMSK |= (1<<TOIE0); /* Enable Overflow Interrupt for Timer0 */
	}
	/* Timer/Counter Register: contains the initial value of the timer */
	TCNT0 = (config_ptr -> initial_value);
}

/*
 * Function Name: TIMER0_setCallBack
 * Inputs: Pointer of the call back function
 * Return Value: Void
 * Description: Set the address of call back function
 */
void TIMER0_setCallBack (void (*m_ptr)(void))
{
	/* Save address of call back function in a global variable  */
	g_callBackPtr = m_ptr;
}

/*
 * Function Name: TIMER0_deInit
 * Inputs: Void
 * Return Value: Void
 * Description: Disable Timer0
 */
void TIMER0_deInit (void)
{
	/* Clear all registers of Timer0 */
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;

	/* Disable Compare Match and Overflow Interrupts */
	TIMSK &= ~(1<<OCIE0) & ~(1<<TOIE0);
}
