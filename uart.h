 /*========================================================================
 * Module: UART
 * File Name: uart.h
 * Description: Header file for the UART AVR driver
 * Author: Jouliana Nabil
   ==========================================================================*/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	bit_5,bit_6,bit_7,bit_8,reserved_1,reserved_2,reserved_3,bit_9
}UART_bit_data;

typedef enum
{
	Disabled,Reserved,Enabled_even,Enabled_odd
}UART_parity_test;

typedef enum
{
	bit_1,bit_2
}UART_stop_bit;

typedef struct
{
	uint32 baud_rate;
	UART_bit_data bit_data;
	UART_parity_test parity;
	UART_stop_bit stop_bit;
}UART_Configuration;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_Configuration * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
