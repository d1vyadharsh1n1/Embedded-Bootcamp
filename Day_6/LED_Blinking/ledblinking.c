#include<reg52.h>
void delay(k)
{
	int i,j;
	for(i=0;i<k;i++)
		for (j =0; j<112; j++);
}
void main()
{
	while(1)
		{
			P1 = 0x00;
			delay(200);
			P1 = 0xFF;
			delay(200);
		}
}
