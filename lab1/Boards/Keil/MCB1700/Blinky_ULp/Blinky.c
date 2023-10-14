/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 * Note(s): __USE_LCD   - enable Output on LCD, uncomment #define in code to use
 *  				for demo (NOT for analysis purposes)
 *----------------------------------------------------------------------------
 * Copyright (c) 2008-2011 Keil - An ARM Company.
 * Name: Anita Tino
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "Blinky.h"
#include "LPC17xx.h"                       
#include "GLCD.h"
#include "LED.h"
#include "Board_ADC.h" 
#include "KBD.h"

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

char text[10];
char joystickText[10];

// Analog - Digital Converter Value
uint16_t AD_dbg; 

// Last converted value
uint16_t ADC_last;       

// Import external variables from IRQ.c file                                 
extern uint8_t  clock_ms;


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  int32_t  res;
  uint32_t AD_sum   = 0U;
  uint32_t AD_cnt   = 0U;
  uint32_t AD_value = 0U;
  uint32_t AD_print = 0U;

  LED_Init();                                /* LED Initialization            */
	KBD_Init();
  ADC_Initialize();                                /* ADC Initialization            */

#ifdef __USE_LCD
  GLCD_Init();                               /* Initialize graphical LCD (if enabled */

  GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, "     COE718 Demo    ");
	GLCD_SetTextColor(White);
  GLCD_DisplayString(1, 0, __FI, "    Joystick Test   ");
  GLCD_DisplayString(3, 0, __FI, "  Move Joystick for ");
	GLCD_DisplayString(4, 0, __FI, "      Direction     ");
  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
#endif

  //SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock/100);       /* Generate interrupt each 10 ms */

  while (1) {                                /* Loop forever                  */
	
    // AD converter input                                                     */
    // AD converter input
		
    res = ADC_GetValue();
    if (res != -1) {                     // If conversion has finished
      ADC_last = (uint16_t)res;
      
      AD_sum += ADC_last;                // Add AD value to sum
      if (++AD_cnt == 16U) {             // average over 16 values
        AD_cnt = 0U;
        AD_value = AD_sum >> 4;          // average devided by 16
        AD_sum = 0U;
      }
    }

    if (AD_value != AD_print) {
      AD_print = AD_value;               // Get unscaled value for printout
      AD_dbg   = (uint16_t)AD_value;

      sprintf(text, "0x%04X", AD_value); // format text for print out
				
#ifdef __USE_LCD
			/*
      GLCD_SetTextColor(Red);
      GLCD_DisplayString(6,  9, __FI,  (unsigned char *)text);
			GLCD_SetTextColor(Green);
      GLCD_Bargraph (144, 7*24, 176, 20, (AD_value >> 2)); // max bargraph is 10 bit 
			*/
#endif
    }

    // Print message with AD value every 10 ms. Used for debugging
    if (clock_ms) {
      clock_ms = 0;
      printf(": %d\n", KBD_val);
    }
		
		uint16_t joystickVal = get_button(); 
		sprintf(joystickText, "%d", joystickVal); 
		GLCD_DisplayString(6, 0, __FI, "Joystick Value:  ");
		GLCD_DisplayString(6, 16, __FI, (unsigned char *)joystickText);
		
		GLCD_DisplayString(7, 0, __FI, "Direction: ");
		if (get_button() == KBD_LEFT){
				GLCD_SetTextColor(Green); 
				GLCD_DisplayString(7, 11, __FI, "LEFT");
				LED_On(0);
		} else if(get_button() == KBD_RIGHT){
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(7, 11, __FI, "RIGTH");
				LED_On(1);
		} else if (get_button() == KBD_UP){
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(7, 11, __FI, "UP");
				LED_On(2);
		} else if (get_button() == KBD_DOWN){
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(7, 11, __FI, "DOWN");
				LED_On(3);
		} else if (get_button() == KBD_SELECT){
				GLCD_SetTextColor(Purple);
				GLCD_DisplayString(7, 11, __FI, "SELECTED");
				LED_On(4);
		} else {
			LED_Off(0); LED_Off(1); LED_Off(2); LED_Off(3); LED_Off(4);
			GLCD_DisplayString(6, 17, __FI, " ");
			GLCD_DisplayString(7, 11, __FI, "        ");
		}
  }
}
