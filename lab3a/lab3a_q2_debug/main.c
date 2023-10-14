#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "cmsis_os.h"                       // CMSIS RTOS header file

osMutexId memory_mutex; 

unsigned int test_counter = 0; 

void memThread (void const *argument);
void cpuThread (void const *argument); 

osThreadId tid_Thread1;
osThreadDef (memThread, osPriorityNormal, 1, 0); 
osThreadId tid_Thread2; 
osThreadDef (cpuThread, osPriorityNormal, 1, 0);

int Init_Thread (void) {
		tid_Thread1 = osThreadCreate (osThread(memThread), NULL); 
		tid_Thread2 = osThreadCreate (osThread(cpuThread), NULL);
		if(!tid_Thread1) return(-1);
		return(0);
}	

void memThread (void const *argument) {
		while(1) {
				osMutexWait(memory_mutex, osWaitForever); 
				test_counter++; 
				osMutexRelease(memory_mutex);		
		}	
}

void cpuThread (void const *argument) {
		while(1) {
			
		}	
}

int main (void) {

	osKernelInitialize ();                    // initialize CMSIS-RTOS
 	Init_Thread ();
	osKernelStart ();                         // start thread execution 
	osDelay(osWaitForever);
	
}
