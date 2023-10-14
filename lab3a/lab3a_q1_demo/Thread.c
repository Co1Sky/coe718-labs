
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include <stdio.h>
#include "LPC17xx.h"                       
#include "GLCD.h"
#include "LED.h" 

/*----------------------------------------------------------------------------
 *      Sample threads
 *---------------------------------------------------------------------------*/
unsigned int counta=0;
unsigned int countb=0;

#define __FI        1                      /* Font index 16x24               */
  
void Thread1 (void const *argument); // thread function
void Thread2 (void const *argument); // thread function
void Thread3 (void const *argument);


osThreadId tid_Thread; // thread id
osThreadDef (Thread1, osPriorityNormal, 1, 0);                   // thread object

osThreadId tid2_Thread; // thread id
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread object

osThreadId tid3_Thread;
osThreadDef (Thread3, osPriorityNormal, 1, 0); 

int Init_Thread (void) {

	tid_Thread = osThreadCreate (osThread(Thread1), NULL);
	osDelay(10000); 
	tid2_Thread = osThreadCreate (osThread(Thread2), NULL);
	osDelay(10000); 
	tid3_Thread = osThreadCreate (osThread(Thread3), NULL); 
	osDelay(10000); 
  if(!tid_Thread) return(-1);
  
  return(0);
}

void Thread3 (void const *argument) {
		GLCD_DisplayString(5, 0, __FI, "Thread 3"); 
		GLCD_DisplayString(3, 0, __FI, "        "); 
		GLCD_DisplayString(4, 0, __FI, "        "); 
		LED_On(3); 
		LED_Off(1);
		LED_Off(2); 
}	

void Thread2 (void const *argument) {
		GLCD_DisplayString(4,0, __FI, "Thread 2");
		GLCD_DisplayString(3, 0, __FI, "        "); 
		GLCD_DisplayString(5, 0, __FI, "        "); 
		LED_On(2); 
		LED_Off(1);
		LED_Off(3); 	
}

void Thread1 (void const *argument) {
		GLCD_DisplayString(3, 0, __FI, "Thread 1");
		GLCD_DisplayString(4, 0, __FI, "        "); 
		GLCD_DisplayString(5, 0, __FI, "        "); 
		LED_On(1); 
		LED_Off(2);
		LED_Off(3); 
			
}
