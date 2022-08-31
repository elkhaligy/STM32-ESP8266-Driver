/*
 * SEVENSEG_prorgam.c
 *
 *  Created on: Aug 30, 2022
 *      Author: Sirito
 */

// libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"
// interface of lower layers
#include <GPIO/GPIO_interface.h>
#include <RCC/RCC_interface.h>
// own driver files
#include <SEVENSEG/SEVENSEG_interface.h>
#include <SEVENSEG/SEVENSEG_config.h>
#include <SEVENSEG/SEVENSEG_private.h>
void SEVENSEG_Initialize(void){
	RCC_void_PeripheralClockEnable(RCC_APB2, RCC_GPIOA);

	GPIO_void_SetPinMode(GPIO_PORTA, a, GPIO_OUTPUT_GP_PP_10MHZ);
	GPIO_void_SetPinMode(GPIO_PORTA, b, GPIO_OUTPUT_GP_PP_10MHZ);
	GPIO_void_SetPinMode(GPIO_PORTA, c, GPIO_OUTPUT_GP_PP_10MHZ);
	GPIO_void_SetPinMode(GPIO_PORTA, d, GPIO_OUTPUT_GP_PP_10MHZ);
	GPIO_void_SetPinMode(GPIO_PORTA, e, GPIO_OUTPUT_GP_PP_10MHZ);
	GPIO_void_SetPinMode(GPIO_PORTA, f, GPIO_OUTPUT_GP_PP_10MHZ);
	GPIO_void_SetPinMode(GPIO_PORTA, g, GPIO_OUTPUT_GP_PP_10MHZ);

}
void SEVENSEG_SendNumber(u8 num1) {
	switch (num1) {
	case 0:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, e, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, f, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, g, LOW);
		break;
	case 1:
		GPIO_void_SetPinValue(GPIO_PORTA, a, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, e, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, f, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, g, LOW);
		break;
	case 2:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, d, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, e, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, f, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, g, HIGH);
		break;
	case 3:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, e, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, f, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, g, HIGH);
		break;
	case 4:
		GPIO_void_SetPinValue(GPIO_PORTA, a, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, e, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, f, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, g, HIGH);
		break;
	case 5:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, e, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, f, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, g, HIGH);
		break;
	case 6:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, e, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, f, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, g, HIGH);
		break;
	case 7:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, e, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, f, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, g, LOW);
		break;
	case 8:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, e, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, f, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, g, HIGH);
		break;
	case 9:
		GPIO_void_SetPinValue(GPIO_PORTA, a, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, b, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, c, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, d, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, e, LOW);
		GPIO_void_SetPinValue(GPIO_PORTA, f, HIGH);
		GPIO_void_SetPinValue(GPIO_PORTA, g, HIGH);
		break;
	}
}
