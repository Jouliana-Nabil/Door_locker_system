/*==========================================================================
 * File Name: MICROCONTROLLER1_main.c
 * Date: 25 October 2021
 * Description: The main Source file of the project
 * Author: Jouliana Nabil
 ===========================================================================*/
#include "std_types.h"
#include "common_macros.h"
#include "std_types.h"
#include "uart.h"
#include "main_1.h"
/*******************************************************************************
 *                     Functions Definitions                                   *
 *******************************************************************************/
void recieved(){
interrupt++;
}

void delay_sec(uint8 sec){
	TIMER0_ConfigType configure ={CTC,CLOCK_1024,DISCONNECTED,0,250};
	TIMER0_setCallBack(recieved);
	TIMER0_init(&configure);
	while(interrupt<sec*31){}
	TIMER0_deInit();
    interrupt=0;
	}
void Get_password(void){
	uint8 key=0;
	uint8 compare;
	uint8 check=1;
	while(check==1){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Password");
	LCD_displayStringRowColumn(1,0,"MAX 5 numbers");
		_delay_ms(500);
		LCD_clearScreen();
		for (uint8 i=0;i<=4;i++){
			key =KEYPAD_getPressedKey();
			_delay_ms(500);
			if((key <= 9) && (key >= 0))
				{
				LCD_displayCharacter('*'); /* display the pressed keypad switch */
				Input_Password_1stTime[i] =key+48;
					}
		}
		LCD_clearScreen();

		Input_Password_1stTime[5]='#';
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"ReEnterPassword");
			LCD_displayStringRowColumn(1,0,"MAX 5 numbers");
			_delay_ms(500);
			LCD_clearScreen();
		for (uint8 i=0;i<=4;i++){
	    key =KEYPAD_getPressedKey();
		_delay_ms(500);
        if((key <= 9) && (key >= 0))
			{
        	LCD_displayCharacter('*'); /* display the pressed keypad switch */
	      Input_Password_2ndTime[i] =key+48;
			}
	}
				LCD_clearScreen();

				Input_Password_2ndTime[5]='#';
				LCD_clearScreen();
				compare=strcmp(Input_Password_1stTime,Input_Password_2ndTime);
				LCD_clearScreen();
				if (compare==0){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"SENDING");
				_delay_ms(500);
				UART_sendString(Input_Password_1stTime);
				LCD_clearScreen();
			    LCD_displayStringRowColumn(0,0,"SENT");
			   _delay_ms(500);
				check=1;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"MATCHED");
		        _delay_ms(500);
		        break;
				}
				else {
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"MISSMATCH");
					_delay_ms(500);
				}
	}

}
void check_password(){
	uint8 key;
	LCD_displayStringRowColumn(0,0,"ReEnter Password");
	LCD_displayStringRowColumn(1,0,"MAX 5 numbers");
	_delay_ms(500);
	LCD_clearScreen();
	for (uint8 i=0;i<=4;i++){
	key =KEYPAD_getPressedKey();
	_delay_ms(500);
	if((key <= 9) && (key >= 0))
		{
		LCD_displayCharacter('*'); /* display the pressed keypad switch */
	check_pass[i] =key+48;
					}
			}
	LCD_clearScreen();
	check_pass[5]='#';
	UART_sendString(check_pass);
}
void choice_default_menu(){
	uint8 key_choice;
	uint8 Selected_key=0;
		while(Selected_key==0){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"+ open door");
				LCD_displayStringRowColumn(1,0,"- change pass");

				key_choice =KEYPAD_getPressedKey();
				_delay_ms(500);
				if(key_choice=='+'){ /*To open door*/
				UART_sendByte('c'); /*byte to check on password to open door*/
				check_password();
				Selected_key=1;
				}
				else if (key_choice=='-'){ /*to change password*/
				UART_sendByte('d'); /*byte to check on password to change it*/
				check_password();
				Selected_key=1;
				}
		}
}
/*************************************main***************************************/


int main(void){

	SREG|=(1<<7);
	uint8 key;
	uint8 counter=0;
	UART_Configuration configure = {9600,bit_8,Disabled,bit_1};
		UART_init(&configure);
		LCD_init();
	    LCD_clearScreen();
	    LCD_displayStringRowColumn(0,4,"DOOR LOCK");
	    _delay_ms(800);
	    char Uart_command;
	    Uart_command=0;
	    UART_sendByte('s');/*sending the two passwords*/
	    Get_password();

		while(1){
			Uart_command=0;
			choice_default_menu();
			Uart_command=UART_recieveByte();
			switch(Uart_command){
			case 'o': /*byte recieved to tell that password is right*/
				LCD_clearScreen();
				LCD_displayStringRowColumn(1,4,"open door");
                delay_sec(15);
                LCD_clearScreen();
                LCD_displayStringRowColumn(1,0,"start to close");
                delay_sec(3);
                LCD_clearScreen();
                LCD_displayStringRowColumn(1,3,"close door");
                delay_sec(15);
                LCD_clearScreen();
			break;
			case 'w': /*byte recieved to say password is wrong*/
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"WRONG PASSWORD");
			_delay_ms(500);
			LCD_clearScreen();
			counter++; /*counter for the mismatch of 3 times*/
			break;
			case 'x': /*byte says password is right so change it*/
				 UART_sendByte('s');/*sending the two passwords*/
				 Get_password();
			break;
			}
			if(counter==3){
				counter=0;
				UART_sendByte('A');	/*buzzer*/
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"ERROR");
				delay_sec(60);
						}
		}
}



