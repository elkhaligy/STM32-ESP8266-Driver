/*
 * app.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Sirito
 */

/** INCLUDES **/
// Libraries
#include "BIT_MATH.h"
#include "STD_TYPES.h"
// Interfaces of MCAL
#include "GPIO/GPIO_interface.h"
#include "RCC/RCC_interface.h"
// Interfaces of HAL
#include "ESP_interface.h"
#include "SEVENSEG/SEVENSEG_interface.h"
/** GLOBAL VARIABLES **/
u8 SSID[]="Radiant";

u8 Password[]="123456789Log";


u8 IP[]="162.253.155.226";
u8 Data[]="GET http://shehab.freevar.com/status.txt";
u8 DataLength[]="42";
/** MAIN **/
int main(void){
	/** CLOCK **/
	// Initialize System Clock
	RCC_void_Initialize();
	/** ESP: USES GPIOA -> PINA 9 and 10 **/
	ESP_Initilization();
	ESP_ConnectToWIFI((u8 *)SSID2,(u8 *)Password2);
	ESP_ConnectToSite(IP);
	/** SEVENSEG: USES GPIOA -> PIN0 to PIN 6 **/
	SEVENSEG_Initialize();
	//SEVENSEG_SendNumber(9);
	u8 SevenSegNumber=ESP_SendData(DataLength,Data);
	/** MAIN LOOP **/
	while(1){
		ESP_ConnectToSite(IP);
		SevenSegNumber=ESP_SendData(DataLength,Data);
		SEVENSEG_SendNumber(SevenSegNumber-'0');
	};
	return 0;
}


