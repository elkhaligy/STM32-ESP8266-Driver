/*
 * ESP_interface.h
 *
 *  Created on: Aug 28, 2022
 *      Author: Sirito
 */

#ifndef ESP_INTERFACE_H_
#define ESP_INTERFACE_H_

#define SSID2 "shehab"
#define Password2 "12345678900"

/*	Function Name: ESP_Initilization
 * 	Arguments    : void
 *	Description  : When called it turns off the echo and also set the wifi mode
 *	 	  			1 : station mode (Connect to router)
 *  				2 : softAP mode (Access point)
 * 					3 : softAP + station mode (Both)
 *	Return		 : void
 */
void ESP_Initilization(void);

/*	Function Name: ESP_ConnectToWIFI
 * 	Arguments    : String SSID, String password
 *			  	   SSID: router name
 *			   	   password: router password
 *	Description  : When called it connects to a router
 *	Return		 : void
 */
void ESP_ConnectToWIFI(u8* SSID, u8* password);

/*	Function Name: ESP_ConnectToSite
 * 	Arguments    : String IP
 *	Description  : When called it establish a connection to a site using TCP/IP
 *	Return		 : void
 */
void ESP_ConnectToSite(u8* IP);

/*	Function Name: ESP_WaitForWifi
 * 	Arguments    : void
 *	Description  : It waited for esp to connect back to wifi incase router failure
 *	Return		 : void
 */
void ESP_WaitForWifi(void);

/*	Function Name: ESP_SendData
 * 	Arguments    : u8 DataLength, String Data
 *	Description  : When called it sends the passed data to the site using TCP/IP
 *	Return		 : The data received back from the site
 */
u8 ESP_SendData(u8* DataLength, u8* Data);

/*	Function Name: isStrFound
 * 	Arguments    : string, string to find
 *	Description  : It finds if a substring is in string or not
 *	Return		 : Returns 1 if true and 0 if false
 */
u8 isStrFound(u8* str, u8* strFound);


#endif /* ESP_INTERFACE_H_ */
