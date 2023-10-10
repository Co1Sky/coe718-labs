#include "cmsis_os.h"                                           // CMSIS RTOS header file

unsigned int counta=0;
unsigned int countb=0;


osThreadId tid_Thread; // thread id
void Thread1 (void const *argument); // thread function
osThreadDef (Thread1, osPriorityNormal, 1, 0);                   // thread object

osThreadId tid2_Thread; // thread id
void Thread2 (void const *argument); // thread function
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread object


int Init_Thread (void) {
  tid_Thread = osThreadCreate (osThread(Thread1), NULL);
	tid2_Thread = osThreadCreate (osThread(Thread2), NULL);
  if(!tid_Thread) return(-1);
  return(0);
}


void Thread2 (void const *argument) {
	  for(;;) {
				countb++;
				osDelay(1); 
  	
  }
}

void Thread1 (void const *argument) {
	 for(;;) {
			counta++;	
			osDelay(2); 
  }                                          
}
