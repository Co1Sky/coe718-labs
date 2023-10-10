#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include <math.h>
#include <stdio.h>

int testcount; 
int x, n, r;   
int A = 0, B = 0, C = 0, D = 0, E = 0; 
int fact = 1; 
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

int factorial(int n) {
	for(x = 1; x <= n; x++){
		fact = fact * x; 	
	}	
	return(fact); 
}	

void ThreadA (void const *argument) {
	for(x = 0; x < 256; x++){
		A = A + (x + (x + 2)); 
	}	
}	

void ThreadB (void const *argument) {
	for(n = 1; n < 16; n++){ 
		B = B +  pow(2,n) / factorial(n); 
	}	
}

void ThreadC (void const *argument) {
	for(n = 1; n <= 16; n++){
		C = C + ((n+1) / n); 
	}	
}

void ThreadD (void const *argument) {
	D = 1 + (5 / factorial(1)) + (pow(5, 2) / factorial(2)) + (pow(5,3) + factorial(3)) + 
					 (pow(5,4), factorial(4)) + (pow(5,5), factorial(5)); 
}

void ThreadE (void const *argument) {
	r = 2; 
	for(x = 1; x <= 12; x++){
		E = E + (x*PI*pow(r,2)); 
	}		
}
