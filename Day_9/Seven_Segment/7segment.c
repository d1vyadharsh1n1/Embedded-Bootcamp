#include <reg52.h>

void delay(unsigned int count);


void main(void){
	while(1){
		P0=0x3F;		//0
		delay(1000);
		P0=0x06;		//1
		delay(1000);
		P0=0x5B;		//2
		delay(1000);
		P0=0x4F;		//3
		delay(1000);
		P0=0x66;		//4
		delay(1000);
		P0=0x6D;		//5
		delay(1000);
		P0=0x7D;		//6
		delay(1000);
		P0=0x07;		//7
		delay(1000);
		P0=0x7F;		//8
		delay(1000);
		P0=0x6F;		//9
		delay(1000);
		
	}
}

void delay(unsigned int count){
	unsigned int i,j;
	for (i=0;i<count;i++){
		for (j=0;j<112;j++);
	}
}
