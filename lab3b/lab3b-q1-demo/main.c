#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include <stdio.h>
#include "LPC17xx.h"                       
#include "GLCD.h"
#include "LED.h" 

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */

//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}
///////////////////////////////////////////////////////////////////////////////

extern int Init_Thread (void);
 

/*
 * main: initialize and start the system
 */
int main (void) {
	LED_Init(); 
#ifdef __USE_LCD
	GLCD_Init();                               /* Initialize graphical LCD (if enabled */
	GLCD_Clear(White);                         /* Clear graphical LCD display   */
	GLCD_SetTextColor(White);
	GLCD_SetBackColor(Red);
	GLCD_DisplayString(0, 0, __FI, "   Lab 3b Q1 Demo   ");
	GLCD_DisplayString(1, 0, __FI, "                    ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(3, 0, __FI, "Thread A: "); 
	GLCD_DisplayString(4, 0, __FI, "Thread B: ");
	GLCD_DisplayString(5, 0, __FI, "Thread C: ");
	GLCD_DisplayString(6, 0, __FI, "Thread D: ");
	GLCD_DisplayString(7, 0, __FI, "Thread E: ");
	
#endif
	
	osKernelInitialize ();                    // initialize CMSIS-RTOS
 	Init_Thread ();
	osKernelStart ();                         // start thread execution 
	osDelay(osWaitForever);
	
}
