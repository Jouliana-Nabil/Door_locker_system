/*==========================================================================
 * Module: timer
 * File Name: timer.h
 * Description: Source file for the functions
 * Author: Jouliana Nabil
 ===========================================================================*/

#ifndef TIMER_H_
#define TIMER_H_

#include "Std_Types.h"

/***************************************************************************************************************************************************
 *                                                                    DEFINITIONS                                                                  *
 **************************************************************************************************************************************************/
#define TIMER0_INITIAL_VALUE 0
#define TIMER0_COMPARE_VALUE 0

/*
 * Enum Name: TIMER0_ModeSelect
 * Enum Description: It contains the available options of modes in TIMER0
 */
typedef enum
{
	NORMAL, PWM, CTC, FAST_PWM
} TIMER0_ModeSelect;

/*
 * Enum Name: TIMER0_ClockSelect
 * Enum Description: It contains the available numbers of clock with and without Prescaling
 */
typedef enum
{
	CLOCK, CLOCK_1, CLOCK_8, CLOCK_64, CLOCK_256, CLOCK_1024
} TIMER0_ClockSelect;

/*
 * Enum Name: TIMER0_CompareMode
 * Enum Description: It contains the available options of modes of Compare Output Match in TIMER0
 */
typedef enum
{
	DISCONNECTED, TOGGLE, CLEAR, SET
} TIMER0_CompareMode;

/*
 * Structure Name: TIMER0_ConfigType
 * Structure Description: It is responsible for maintaining information about configuration types of TIMER0:
 * 1- TIMER0 Mode Selection
 * 2- Clock Selection
 * 3- Compare Output Match Mode Selection
 * 4- Initial Value
 * 5- Compare Value
 */
typedef struct
{
	TIMER0_ModeSelect mode;
	TIMER0_ClockSelect clock;
	TIMER0_CompareMode compare;
	uint8 initial_value;
	uint8 compare_value;
} TIMER0_ConfigType;

/***************************************************************************************************************************************************
 *                                                               FUNCTIONS PROTOTYPES                                                              *
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
void TIMER0_init (const TIMER0_ConfigType * config_ptr);

/*
 * Function Name: TIMER0_setCallBack
 * Inputs: Pointer of the call back function
 * Return Value: Void
 * Description: Set the address of call back function
 */
void TIMER0_setCallBack (void (*m_ptr)(void));

/*
 * Function Name: TIMER0_deInit
 * Inputs: Void
 * Return Value: Void
 * Description: Disable Timer0
 */
void TIMER0_deInit (void);

#endif /* TIMER_H_ */
