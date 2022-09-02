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

void ESP_Initilization(void);
void ESP_ConnectToWIFI(u8* SSID, u8* password);
void ESP_ConnectToSite(u8* IP);
u8 ESP_SendData(u8* DataLength, u8* Data);
u8 isStrFound(u8* str, u8* strFound);
#endif /* ESP_INTERFACE_H_ */
