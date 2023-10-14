//conditional execution code example
#include "LPC17xx.h"

int main(void){
	
	int r1 = 1, r2 = 0;
	
	while(r1 <= 0x07){
		if((r1 - r2) > 0){
		  r1 = r1 + 2;
	}
		else{
			r2 = r2 + 1;
		}
	}
	return 0;
}