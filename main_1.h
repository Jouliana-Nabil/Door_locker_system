/*==========================================================================
 * Module: Functions
 * File Name: Functions_1.h
 * Description: Source file for the functions
 * Author: Jouliana Nabil
 ===========================================================================*/

#ifndef MAIN_1_H_
#define MAIN_1_H_

#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "std_types.h"
#include <util/delay.h>
#include "timer.h"
#include <avr/io.h>
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define n 7
#define F_CPU 8000000
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
uint8 key_choice;
uint8 Input_Password_1stTime[n];
uint8 Input_Password_2ndTime[n];
uint8 check_pass[n];
uint16 interrupt=0;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Get_password();
void check_password();
void choice_default_menu();

#endif /* MAIN_1_H_ */
