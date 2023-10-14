#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "cmsis_os.h"                       // CMSIS RTOS header file
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "LPC17xx.h"

int Init_Thread (void); 

// Bit Band Macros used to calculate the alias address at run time
#define ADDRESS(x)    (*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))
	
//Pointer declaration
volatile unsigned long * bit;
int a=0, b=2, c=0; // Barrel Shifting variables

int x; 

int  mem=0,dev=0, app=0, cpu=0, usr=0;
char var_logger[15];

/* 	THREAD DECLARATION */ 
/////////////////////////////////////////////////////
osThreadId tid_MemoryThread; 
void MemoryThread (void const *argument); 
osThreadDef (MemoryThread, osPriorityHigh, 1, 0);                  

osThreadId tid_CPUThread; 
void CPUThread (void const *argument); 
osThreadDef (CPUThread, osPriorityHigh, 1, 0);    

osThreadId tid_AppThread; 
void AppThread (void const *argument);
osThreadDef (AppThread, osPriorityAboveNormal, 1, 0); 

osThreadId tid_DeviceThread; 
void DeviceThread (void const *argument); 
osThreadDef (DeviceThread, osPriorityAboveNormal, 1, 0);

osThreadId tid_UIThread; 
void UIThread (void const *argument);
osThreadDef (UIThread, osPriorityNormal, 1, 0); 

/* MAIN INITIALIZE AND START THE SYSTEM */
/////////////////////////////////////////////////////////
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
 	Init_Thread ();
  osKernelStart ();                         // start thread execution 
	osDelay(osWaitForever);
}

/* THREAD INITIALIZATION */ 
////////////////////////////////////////////////////////
int Init_Thread (void) {
  tid_MemoryThread = osThreadCreate (osThread(MemoryThread), NULL);
	tid_CPUThread = osThreadCreate (osThread(CPUThread), NULL);
	tid_AppThread = osThreadCreate (osThread(AppThread), NULL); 
	tid_DeviceThread = osThreadCreate (osThread(DeviceThread), NULL);
	tid_UIThread = osThreadCreate (osThread(UIThread), NULL); 
  if(!tid_MemoryThread) return(-1);
  return(0);
} 

/* THREAD EXECUTION */
/////////////////////////////////////////////////////////
void MemoryThread (void const *argument) {
	mem++; 
	bit = &BitBand(&LPC_GPIO1->FIOPIN, 28); 
	osThreadYield();
	while(1){
		osSignalWait(0x01, osWaitForever);
			osDelay(1);
			osThreadTerminate(tid_MemoryThread); 	
	}	
}	

void CPUThread (void const *argument) {
	cpu++;
		while(c <= 5){
		a = pow(b,c);
		c++;
	}
	c=0;
	osSignalSet(tid_MemoryThread, 0x01); 
	osThreadTerminate(tid_CPUThread); 
}

void AppThread (void const *argument) {
	strcpy(var_logger,"part 1"); 
	osThreadYield(); 
	while(1){
		osSignalWait(0x02, osWaitForever); 
			app++; 
			osDelay(1); 
			osThreadTerminate(tid_AppThread); 
	}	
}

void DeviceThread (void const *argument) {
	var_logger[7] = 'p';		
	var_logger[8] = 'a';
	var_logger[9] = 'r';
	var_logger[10] = 't';
	var_logger[11] = ' ';
	var_logger[12] = '2';
	
//	printf("var_logger = "); 
//	while (x < sizeof(var_logger)) {
//		printf("%c", var_logger[x]); 
//	}	
	
	osSignalSet(tid_AppThread, 0x02); 
	dev++; 
	osDelay(1); 
	osThreadTerminate(tid_DeviceThread); 
}

void UIThread (void const *argument) {
	usr++;
	osDelay(1); 
	osThreadTerminate(tid_UIThread); 
}
