#include <reg51.h>

sfr ldata = 0x90;
sbit rs = P2^0;
sbit rw = P2^1;
sbit en = P2^2;

void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void MSDelay(unsigned int itime);

void main()
{
    lcdcmd(0x38);
    lcdcmd(0x0E);
    lcdcmd(0x01);
    lcdcmd(0x06);
    lcdcmd(0x86);

    lcddata('H');
    lcddata('A');
    lcddata('R');
    lcddata('I');

    while(1); 
}

void lcdcmd(unsigned char value)
{
    ldata = value;
    rs = 0;
    rw = 0;
    en = 1;
    MSDelay(2);
    en = 0;
    MSDelay(2);
}

void lcddata(unsigned char value)
{
    ldata = value;
    rs = 1;
    rw = 0;
    en = 1;
    MSDelay(2);
    en = 0;
    MSDelay(2);
}

void MSDelay(unsigned int itime)
{
    unsigned int i, j;
    for(i = 0; i < itime; i++)
        for(j = 0; j < 1275; j++);
}
