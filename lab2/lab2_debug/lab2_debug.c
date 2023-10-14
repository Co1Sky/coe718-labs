#include <stdio.h>
#include "LPC17xx.h"                       

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

// Bit Band Macros used to calculate the alias address at run time
#define ADDRESS(x)    (*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

volatile unsigned long * led_bit1;

#define led28 (*((volatile unsigned long *)0x233806F0))
	
int r1; 
 
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	
	r1 = 0;
	while(r1 <= 2){
		if(r1 == 0){
				// MASK MODE //
				LPC_GPIO1->FIOPIN |=  ( 1 << 28);              // start conversion    
				LPC_GPIO1->FIOPIN &= ~( 1 << 28);              // stop conversion     
		}	else if(r1 == 1) {
				// FUNCTION MODE //
				led_bit1 = &BitBand(&LPC_GPIO1->FIOPIN, 28);		
				*led_bit1 = 1;
				*led_bit1 = 0; 
		}	else if (r1 == 2) {
				// BITBAND MODE //
				led28 = 1;
				led28 = 0;
		}
		r1 = r1 + 1; 
	}
	
	return 0;
}
