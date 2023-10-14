#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions


extern int Init_Thread (void);
 

int main (void) {

	osKernelInitialize ();                    // initialize CMSIS-RTOS
 	Init_Thread ();
	osKernelStart ();                         // start thread execution 
	osDelay(osWaitForever);
	
}
