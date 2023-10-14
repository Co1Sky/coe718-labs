#include "cmsis_os.h"                                           // CMSIS RTOS header file

/*----------------------------------------------------------------------------
 *      Sample threads
 *---------------------------------------------------------------------------*/
unsigned int varA = 0; 
unsigned int varB = 0; 
unsigned int varC = 1; 

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
	tid2_Thread = osThreadCreate (osThread(Thread2), NULL);
	tid3_Thread = osThreadCreate (osThread(Thread3), NULL); 
  if(!tid_Thread) return(-1);
  
  return(0);
}

void Thread3 (void const *argument) {
	while(1){
			varC = ((varC * 2)/2)+1; 
	}	
}	

void Thread2 (void const *argument) {
	while(1){
			varB = (varB + varA) - 1; 
	}	
}

void Thread1 (void const *argument) {
	while(1){
			varA++;
	}		
}
