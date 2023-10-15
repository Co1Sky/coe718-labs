#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include <math.h>
#include <stdio.h>
#include "GLCD.h"
#include "LED.h" 

#define __FI        1                      /* Font index 16x24               */

int testcount; 
int x, n, r;   
int counter; 
char Ac_str[10], Bc_str[10], Cc_str[10], Dc_str[10], Ec_str[10];    
int A = 0, B = 1, C = 0, D = 0, E = 0; 
int bf=1, df=1; // Task factorial storage 
double PI = 3.14159265359; 

/* 	THREAD DECLARATION */ 
/////////////////////////////////////////////////////
osThreadId tid_ThreadA; 
void ThreadA (void const *argument); 
osThreadDef (ThreadA, osPriorityAboveNormal, 1, 0);                  

osThreadId tid_ThreadB; 
void ThreadB (void const *argument); 
osThreadDef (ThreadB, osPriorityNormal, 1, 0);    

osThreadId tid_ThreadC; 
void ThreadC (void const *argument);
osThreadDef (ThreadC, osPriorityHigh, 1, 0); 

osThreadId tid_ThreadD; 
void ThreadD (void const *argument); 
osThreadDef (ThreadD, osPriorityAboveNormal, 1, 0);

osThreadId tid_ThreadE; 
void ThreadE (void const *argument);
osThreadDef (ThreadE, osPriorityNormal, 1, 0); 

/* THREAD INITIALIZATION */ 
////////////////////////////////////////////////////////
int Init_Thread (void) {
  tid_ThreadA = osThreadCreate (osThread(ThreadA), NULL);
	tid_ThreadB = osThreadCreate (osThread(ThreadB), NULL);
	tid_ThreadC = osThreadCreate (osThread(ThreadC), NULL); 
	tid_ThreadD = osThreadCreate (osThread(ThreadD), NULL);
	tid_ThreadE = osThreadCreate (osThread(ThreadE), NULL); 
  if(!tid_ThreadA) return(-1);
  return(0);
}

void ThreadA (void const *argument) { 
	LED_On(0); 
	LED_Off(1); LED_Off(2); LED_Off(3); LED_Off(4);  
	counter++;
	sprintf(Ac_str, "%d", counter); 
	GLCD_DisplayString(3, 9, __FI, Ac_str);  
	while(x < 256){
		A = (A + (x + (x + 2))); 
		x++; 
	}
	sprintf(Ac_str, "0x%04X", A); 
	GLCD_DisplayString(3, 11, __FI, Ac_str);
}	

void ThreadB (void const *argument) { 
	LED_On(1); 
	LED_Off(0); LED_Off(2); LED_Off(3); LED_Off(4); 	
	counter++; 
	sprintf(Bc_str, "%d", counter); 
	GLCD_DisplayString(4, 9, __FI, Bc_str); 
	while(n < 16) { 
		bf*=n; 
		B = (B + (pow(2,n)/bf)); 
		n++; 
	}
	sprintf(Bc_str, "0x%04X", B);
	GLCD_DisplayString(4, 11, __FI, Bc_str);
}

void ThreadC (void const *argument) { 
	LED_On(2); 
	LED_Off(0); LED_Off(1); LED_Off(3); LED_Off(4);
	n = 0; 
	counter++; 
	sprintf(Cc_str, "%d", counter); 
	GLCD_DisplayString(5, 9, __FI, Cc_str); 
	while(n < 16) {
		C += ((n+1) / n); 
		n++; 
	}	
	sprintf(Cc_str, "0x%04X", C);
	GLCD_DisplayString(5, 11, __FI, Cc_str); 
}

void ThreadD (void const *argument) {
	LED_On(3); 
	LED_Off(0); LED_Off(1); LED_Off(2); LED_Off(4);
	n = 0;
	counter++; 
	sprintf(Dc_str, "%d", counter); 
	GLCD_DisplayString(6, 9, __FI, Dc_str); 
	while(n < 6){
		if (n == 0) {
			D = 1;
		}	else {
			df*=n;
			D += (pow(5,n)/df);
		}
		n++; 
	}	
	sprintf(Dc_str, "0x%04X", D);
	GLCD_DisplayString(6, 11, __FI, Dc_str);
}

void ThreadE (void const *argument) {
	LED_On(4); 
	LED_Off(0); LED_Off(1); LED_Off(3); LED_Off(3); 
	r = 2; 
	counter++;
	sprintf(Ec_str, "%d", counter); 
	GLCD_DisplayString(7, 9, __FI, Ec_str); 	
	for(x = 1; x <= 12; x++){
		E = E + (x*PI*pow(r,2)); 
	}
	sprintf(Ec_str, "0x%04X", E);
	GLCD_DisplayString(7, 11, __FI, Ec_str); 
}
