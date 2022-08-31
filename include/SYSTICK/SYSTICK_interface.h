/*
 * SYSTICK_interface.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Omar Gamal
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

//Macros
#define SYSTICK_AHB_8 		0
#define SYSTICK_AHB 		1



/*
 * STK_voidInit
 * description: Selects the clock source of the SysTick (AHB, AHB/8)
 */
void STK_voidInit(u8 Copy_u8ClkSRC);


/*
 * STK_voidStopTimer
 * description: Stops the Timer
 */
void STK_voidStopTimer(void);

/*
 * STK_voidSetBusyWait
 * description: Starts a synchronous wait (delay)
 */
void STK_voidSetBusyWait(u32 Copy_u32TickCount);


/*
 * STK_voidSetPeriodicInterval
 * description: Starts a periodic interval asynchronous wait
 */
void STK_voidSetPeriodicInterval(u32 Copy_u32TickCount, void (*ptr)(void));


/*
 * STK_voidSetSingleInterval
 * description: Starts a single interval asynchronous wait
 */
void STK_voidSetSingleInterval(u32 Copy_u32TickCount, void (*ptr)(void));


/*
 * STK_u32GetRemainingTicks
 * description: Gets the number of ticks remaining until we reach zero
 */
u32 STK_u32GetRemainingTicks(void);

/*
 * STK_u32GetElapsedTicks
 * description: Gets the number of ticks elapsed since we started counting
 */
u32 STK_u32GetElapsedTicks(void);

void STK_DelayMS(u32 m_seconds);

#endif /* SYSTICK_INTERFACE_H_ */
