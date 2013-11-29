// define Timer register
#define rTCFG0 (*(volatile unsigned int *)0x51000000)
#define rTCFG1 (*(volatile unsigned int *)0x51000004)
#define rTCON (*(volatile unsigned int *)0x51000008)
#define rTCNTB0 (*(volatile unsigned int *)0x5100000C)
#define rTCMPB0 (*(volatile unsigned int *)0x51000010)
#define rTCNTO0 (*(volatile unsigned int *)0x51000014)
#define rTCNTB1 (*(volatile unsigned int *)0x51000018)
#define rTCMPB1 (*(volatile unsigned int *)0x5100001C)
#define rTCNTO1 (*(volatile unsigned int *)0x51000020)
#define rTCNTB2 (*(volatile unsigned int *)0x51000024)
#define rTCMPB2 (*(volatile unsigned int *)0x51000028)
#define rTCNTO2 (*(volatile unsigned int *)0x5100002C)
#define rTCNTB3 (*(volatile unsigned int *)0x51000030)
#define rTCMPB3 (*(volatile unsigned int *)0x51000034)
#define rTCNTO3 (*(volatile unsigned int *)0x51000038)
#define rTCNTB4 (*(volatile unsigned int *)0x5100003C)
#define rTCNTO4 (*(volatile unsigned int *)0x51000040)


#define INTMSK (*(volatile unsigned int *)0X4A000008)

void prints(char* char_to_print)
{
	while(*char_to_print)
	{
		putc(*char_to_print);
		char_to_print ++;
	}
	putc('\n');

}
void putc(unsigned char c) 
{ 
#define UTRSTAT1 (*(volatile unsigned int *)0x50004010)
#define UTXH1 (*(volatile unsigned int *)0x50004020)

	//while( ! (UTRSTAT1 & 0x4) ); //不断查询，直到可以发送数据 
	UTXH1 = c; //发送数据 
} 


unsigned char getc( ) 
{ 

#define URXH1 (*(volatile unsigned int *)0x50004024)

	while( ! (UTRSTAT1 & 0x1) ); //不断查询，直到接收到了数据 
		return URXH1; //返回接收到的数据 
} 


void print(unsigned int iNum)
{ 
    if (iNum < 10)
    {  putc(iNum + '0');
       return;
    }
    print(iNum / 10);
    putc(iNum %10 + '0');
  
}

void TimerInit(int imSec)
{
	int iCount = imSec * 26; //近似值
	rTCFG0 = 119 << 8;
	rTCFG1 = 3 << 16 ;
	rTCNTB4 = iCount;
	int tcon = rTCON & ~(0x0F << 20);
	rTCON = tcon | (0x2 << 20);
	rTCON = tcon | (0x5 << 20);
}

void InterruptDisable(unsigned int irNum)
{
	INTMSK |= irNum;


}

void InterruptEnable(unsigned int irNum)
{
	INTMSK &= ~irNum;

}

#include "includes.h"
#include "lcd.h"
#include "touch.h"
#include "bitmap.h"

void TaskDraw(void* p);

void Task0(void* p);

void Task1(void* p2);

void Task2(void* p3);

OS_EVENT* g_event;

int main()
{	
	
	OSInit();

	//print(Task0);

	//print(12);
	OSTaskCreate(TaskDraw, (void *)0,(OS_STK *)0x31ff0000, 4);
	OSTaskCreate(Task0, (void *)0,(OS_STK *)0x31300000, 5);
	OSTaskCreate(Task1 ,(void*)0,  (OS_STK *)0x31100000,10);
	OSTaskCreate(Task2 ,(void*)0,  (OS_STK *)0x31f00000,12);
	g_event = OSSemCreate(0); 
	
	TimerInit(500);
	InitDisplay();
	InitTouch();

	OSStart();
        while(1);

	
	return 0;
}








