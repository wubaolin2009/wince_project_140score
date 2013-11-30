#ifndef _LCD_MY_H
#define _LCD_MY_H

#define LCDBASE 0x4D000000  //LCD base register

#define PHYBASE    0x30000000 

#define GPCUP  (*(volatile unsigned int *)0x56000028 )
#define GPCCON ( *(volatile unsigned int *)0x56000020) 
#define GPDUP  (*(volatile unsigned int *)0x56000038) 
#define GPDCON  (*(volatile unsigned int *)0x56000030) 
#define GPGCON  (*(volatile unsigned int *)0x56000060) 
#define GPGDAT  (*(volatile unsigned int *)0x56000064) 

#define TPAL (*(volatile unsigned int *)0x4D000050)
#define LPCSEL (*(volatile unsigned int *)0x4D000060)

struct S3C_LCD  //ª˘±æ…Ë÷√
{
	unsigned int LCDCON1; 
	unsigned int LCDCON2; 
	unsigned int LCDCON3; 
	unsigned int LCDCON4; 
	unsigned int LCDCON5; 

	unsigned int LCDSADDR1; 
	unsigned int LCDSADDR2; 
	unsigned int LCDSADDR3;
};

void InitDisplay();
void Rect(int x,int y,int x1,int y1,short color);

#endif

