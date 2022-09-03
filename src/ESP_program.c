/*
 * ESP_program.c
 *	HAL ESP DRIVER
 *  Created on: Aug 28, 2022
 *      Author: Sirito
 */

/** INCLUDES **/
// Libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"
// Interface of lower layer (MCAL)
#include "USART/USART_interface.h"
#include "NVIC/NVIC_interface.h"
#include "GPIO/GPIO_interface.h"
#include "RCC/RCC_interface.h"
#include "SYSTICK/SYSTICK_interface.h"
// Own driver files
#include <ESP_interface.h>
#include <ESP_config.h>
#include <ESP_private.h>
#include <string.h>
/** GLOBAL **/
u8 ReceiveArray[100] = { 0 };
u32 arr_size = 0;
u8 ReceivedByte;

extern u8 IP[];

/** FUNCTIONS **/
void ESP_Initilization(void) {
	/* Variables Declaration */
	u8 ErrorFlag = 0;

	/* GPIO and RCC Configurations */
	RCC_void_PeripheralClockEnable(RCC_APB2, RCC_GPIOA); 			 // Enable GPIOA Clock
	RCC_void_PeripheralClockEnable(RCC_APB2, RCC_USART1);			 // Enable USART1 Clock
	GPIO_void_SetPinMode(GPIO_PORTA, PIN9, GPIO_OUTPUT_ALT_PP_2MHZ); // Set mode of Pin A9: USART1 Tx to alternating function
	GPIO_void_SetPinMode(GPIO_PORTA, PIN10, GPIO_INPUT_FLOATING);	 // Set mode of Pin A10: USART1 Rx to input floating

	/* USART Configurations */
	USART_SetBaudRate(BAUD_RATE_115200); 	// Set Usart Baud Rate to 115200 BPS
	USART_EnableUSART(USART_1); 		 	// Enable USART, Tx and Rx
	NVIC_voidEnableInterrupt(NVIC_USART1);	// Enable USART1 receive Interrupt nvic enabler
	USART1_ReceiveInterruptEnable(USART_1);	// Enable USART1 receive Interrupt from usart itself

	/* Send Echo Command */
	USART_SendString(USART_1, (u8 *) EchoOff); 	// Set Echo Mode

	/* Polling on receive */
	while (!StringMatch(ReceiveArray, (u8 *) "OK\r\n")) {
		/* Fail and error check */
		if (StringMatch(ReceiveArray, (u8 *) "FAIL\r\n")) { // Backdoor out of the loop incase of failiuer
			ErrorFlag = 1;
			break;
		} else if (StringMatch(ReceiveArray, (u8 *) "ERROR\r\n")) {
			ErrorFlag = 1;
			break;
		}
	}

	/* Applied if a FAIL received */
	if (ErrorFlag) {
		arr_size = 0;
		for (u8 i = 0; i < 50; i++)
			ReceiveArray[i] = 0;
		ESP_Initilization();
	}

	/* Reseting error flag, buffer size and buffer valeus */
	ErrorFlag=0;
	arr_size = 0;
	for (u8 i = 0; i < 10; i++)
		ReceiveArray[i] = 0;

	/* Sending wifi connect command */
	USART_SendString(USART_1, (u8 *) WifiMode1);

	/* Polling on wifi command response */
	while (!StringMatch(ReceiveArray, (u8 *) "OK\r\n")) {
		if (StringMatch(ReceiveArray, (u8 *) "FAIL")) {
			ErrorFlag = 1;
			break;
		}else if (StringMatch(ReceiveArray, (u8 *) "ERROR\r\n")) {
			ErrorFlag = 1;
			break;
		}
	}
	if (ErrorFlag) {
		arr_size = 0;
		for (u8 i = 0; i < 50; i++)
			ReceiveArray[i] = 0;
		ESP_Initilization();
	}

	/* Reseting buffer size and buffer values */
	arr_size = 0;
	for (u8 i = 0; i < 10; i++)
		ReceiveArray[i] = 0;

}

void ESP_ConnectToWIFI(u8* SSID, u8* password) {
	/* Variables */
	u8 ErrorFlag=0;

	/* Sending wifi command */
	USART_SendString(USART_1, (u8 *) "AT+CWJAP_CUR=\"");
	USART_SendString(USART_1, SSID);
	USART_SendString(USART_1, (u8 *) "\",\"");
	USART_SendString(USART_1, password);
	USART_SendString(USART_1, (u8 *) "\"\r\n");

	/* Polling on wifi command response*/
	while (!StringMatch(ReceiveArray, (u8 *) "OK\r\n")) {
		/* If failed raise a flag */
		if (StringMatch(ReceiveArray, (u8 *) "FAIL\r\n")) {
			ErrorFlag = 1;
			break;
		} else if (StringMatch(ReceiveArray, (u8 *) "ERROR\r\n")) {
			ErrorFlag = 1;
			break;
		}
	}
	/* If the error flag is raised reset buffer and call the same function again*/
	if (ErrorFlag) {
		arr_size = 0;
		for (u8 i = 0; i < 50; i++)
			ReceiveArray[i] = 0;
		ESP_ConnectToWIFI(SSID,password);
	}

	/* Reset buffer */
	arr_size = 0;
	for (u8 i = 0; i < 50; i++)
		ReceiveArray[i] = 0;
}

void ESP_ConnectToSite(u8* IP) {
	/* Variables */
	u8 ErrorFlag=0;

	/* Sending connect to site AT command */
	USART_SendString(USART_1, (u8 *) "AT+CIPSTART=\"TCP\",\"");
	USART_SendString(USART_1, IP);
	USART_SendString(USART_1, (u8 *) "\",");
	USART_SendString(USART_1, (u8 *) "80");
	USART_SendString(USART_1, (u8 *) "\r\n");

	/* Waiting for command response */
	while (!StringMatch(ReceiveArray, (u8 *) "OK\r\n")) {
		/* If you find error raise a flag and break */
		if (StringMatch(ReceiveArray, (u8 *) "ERROR\r\n")) {
			ErrorFlag = 1;
			break;
		}
	}

	/* Incase of error you may have no ip so call wait for wifi function*/
	/* The other type of error is unkown so call same function again*/
	if (ErrorFlag) {
		if( StringMatch(ReceiveArray, (u8 *) "no ip") ){
			arr_size = 0;
			for (u8 i = 0; i < 50; i++)
				ReceiveArray[i] = 0;
			ESP_WaitForWifi();
		}else{
			arr_size = 0;
			for (u8 i = 0; i < 50; i++)
				ReceiveArray[i] = 0;
			ESP_ConnectToSite(IP);
		}
	}

	/* Reset buffer size */
	arr_size = 0;
	for (u8 i = 0; i < 50; i++)
		ReceiveArray[i] = 0;
}

void ESP_WaitForWifi(void){
	/* Poll until response received */
	while (!StringMatch(ReceiveArray, (u8 *) "GOT IP"));

	/* Reset buffer for next response */
	arr_size = 0;
	for (u8 i = 0; i < 55; i++)
		ReceiveArray[i] = 0;
}


u8 ESP_SendData(u8* DataLength, u8* Data) {
	/* Send (Send Data) AT command*/
	USART_SendString(USART_1, (u8 *) "AT+CIPSEND=");
	USART_SendString(USART_1, DataLength);
	USART_SendString(USART_1, (u8 *) "\r\n");

	/* Poll on command response */
	while (!StringMatch(ReceiveArray, (u8 *) "> ")){
		/* Incase of an error that means you are not connected to IP so call connect to site function*/
		if (StringMatch(ReceiveArray, (u8 *) "ERROR\r\n")) {
			arr_size = 0;
			for (u8 i = 0; i < 50; i++)
				ReceiveArray[i] = 0;
			ESP_ConnectToSite(IP);
			break;
		}
	}

	/* Reset buffer for next response*/
	arr_size = 0;
	for (u8 i = 0; i < 50; i++)
		ReceiveArray[i] = 0;

	/* Send Data itself*/
	USART_SendString(USART_1, Data);
	USART_SendString(USART_1, (u8 *) "\r\n");

	/* Poll on data response */
	while (!StringMatch(ReceiveArray, (u8 *) "CLOSED\r\n")) {
		/* Incase error faced repeat same function */
		if (StringMatch(ReceiveArray, (u8 *) "ERROR\r\n")) {
			arr_size = 0;
			for (u8 i = 0; i < 50; i++)
				ReceiveArray[i] = 0;
			ESP_SendData(DataLength,Data);
			break;
		}
	}

	/* Take the received data using buffer */
	u8 data = ReceiveArray[37];\

	/* Reset buffer for next response */
	arr_size = 0;
	for (u8 i = 0; i < 55; i++)
		ReceiveArray[i] = 0;

	/* Return received data */
	return data;
}

u8 StringMatch(u8* SourceString, u8* StringToFind) {
	/* Variables */
	u8 state = 0;

	/* Loop */
	for (u8 i = 0; SourceString[i] != '\0'; i++) {
		if (SourceString[i] == StringToFind[0]) {
			u8 j = 1;
			for (; StringToFind[j] != '\0'; j++) {
				i++;
				if (StringToFind[j] != SourceString[i])
					break;
			}
			if (StringToFind[j] == '\0') {
				state = 1;
				break;
			}
		}
	}

	/* Return */
	return state;
}
/** INTERRUPTS HANDLING **/
// This interrupt is triggered each time RXNE is 1 meaning that "Received data is ready to be read"
void USART1_IRQHandler(void) {
	/* Take the received byte from the receive buffer */
	ReceivedByte = USART_ReceiveByte(USART_1);

	/* Put that byte in array of bytes (buffer) */
	ReceiveArray[arr_size] = ReceivedByte;

	/* Increase buffer size*/
	arr_size++;
}




