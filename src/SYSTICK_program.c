/*
 * SYS_TICK_program.c
 *
 *  Created on: Aug 10, 2022
 *      Author: Omar Gamal
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK/SYSTICK_interface.h"
#include "SYSTICK/SYSTICK_config.h"
#include "SYSTICK/SYSTICK_private.h"


//#include "GPIO/GPIO_interface.h"

void (*CallBack)(void) = (void *) 0;
u8 IntervalState = SYSTICK_PERIODIC_INTERVAL;

/*
 * STK_voidInit
 * description: Selects the clock source of the SysTick (AHB, AHB/8)
 */
void STK_voidInit(u8 Copy_u8ClkSRC){

	switch(Copy_u8ClkSRC)
	{
	case SYSTICK_AHB_8:
		CLR_BIT(SYSTICK->CTRL,2);
		break;
	case SYSTICK_AHB:
		SET_BIT(SYSTICK->CTRL,2);
		break;
	}

}


/*
 * STK_voidStopTimer
 * description: Stops the Timer
 */
void STK_voidStopTimer(void){



}



/*
 * STK_voidSetBusyWait
 * description: Starts a synchronous wait (delay)
 */
void STK_voidSetBusyWait(u32 Copy_u32TickCount){

	/* Disable the systick interrupt
	 * Set LOAD value
	 * start the timer
	 * empty loop until the flag is raised
	 * reset the flag
	 * Reset the LOAD register
	 * stop the timer
	 */
	CLR_BIT(SYSTICK->CTRL, 1);
	SYSTICK->LOAD = (Copy_u32TickCount) & 0x00FFFFFF;
	SET_BIT(SYSTICK->CTRL, 0);
	while(!(GET_BIT(SYSTICK->CTRL, 16)));
	CLR_BIT(SYSTICK->CTRL, 0);
}


/*
 * STK_voidSetPeriodicInterval
 * description: Starts a periodic interval asynchronous wait
 */
void STK_voidSetPeriodicInterval(u32 Copy_u32TickCount, void (*ptr)(void)){

	/* Set LOAD value
	 * assign the callback function to the handler
	 * Enable the interrupt
	 * start the timer
	 */
	IntervalState = SYSTICK_PERIODIC_INTERVAL;
	SYSTICK->LOAD = (Copy_u32TickCount - 1) & 0x00FFFFFF;
	CallBack = ptr;
	SET_BIT(SYSTICK->CTRL, 1);
	SET_BIT(SYSTICK->CTRL, 0);
}


/*
 * STK_voidSetSingleInterval
 * description: Starts a single interval asynchronous wait
 */
void STK_voidSetSingleInterval(u32 Copy_u32TickCount, void (*ptr)(void)){

	/* Set LOAD value
	 * assign the callback function to the handler
	 * Enable the interrupt
	 * start the timer
	 */

	IntervalState = SYSTICK_SINGLE_INTERVAL;
	SYSTICK->LOAD = (Copy_u32TickCount) & 0x00FFFFFF;
	CallBack = ptr;
	SET_BIT(SYSTICK->CTRL, 1);
	SET_BIT(SYSTICK->CTRL, 0);
}


/*
 * STK_u32GetRemainingTicks
 * description: Gets the number of ticks remaining until we reach zero
 */
u32 STK_u32GetRemainingTicks(void){


	return 0;
}
/*
 * STK_u32GetElapsedTicks
 * description: Gets the number of ticks elapsed since we started counting
 */
u32 STK_u32GetElapsedTicks(void){

	return 0;
}

void SysTick_Handler(void){
	CallBack();
	if(IntervalState == SYSTICK_PERIODIC_INTERVAL){

	}else{
		CLR_BIT(SYSTICK->CTRL, 0);
	}
	SYSTICK->VAL = 0; // Clearing the flag
}



void STK_DelayMS(u32 m_seconds){

	u32 Copy_u32TickCount= m_seconds*1000;
	/* Disable the systick interrupt
	 * Set LOAD value
	 * start the timer
	 * empty loop until the flag is raised
	 * reset the flag
	 * Reset the LOAD register
	 * stop the timer
	 */
	CLR_BIT(SYSTICK->CTRL, 1);
	SYSTICK->LOAD = (Copy_u32TickCount) & 0x00FFFFFF;
	SET_BIT(SYSTICK->CTRL, 0);
	while(!(GET_BIT(SYSTICK->CTRL, 16)));
	CLR_BIT(SYSTICK->CTRL, 0);
}
