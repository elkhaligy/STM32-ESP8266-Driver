/*
 * ESP_config.h
 *
 *  Created on: Aug 28, 2022
 *      Author: Sirito
 */

#ifndef ESP_CONFIG_H_
#define ESP_CONFIG_H_

// WIFI Mode Macros
#define WifiMode1 "AT+CWMODE_CUR=1\r\n"
#define WifiMode2 "AT+CWMODE_CUR=2\r\n"
#define WifiMode3 "AT+CWMODE_CUR=3\r\n"
// Echo Mode Macros
#define EchoOff "ATE0\r\n"
#define EchoOn "ATE1\r\n"

#endif /* ESP_CONFIG_H_ */
