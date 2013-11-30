#ifndef _TOUCH_MY_H
#define _TOUCH_MY_H


#define ADCCONBASE 0x58000000  //ADC Controler的基址



struct S3C_TOUCH
{
	unsigned int ADCCON;
	unsigned int ADCTSC;
	unsigned int ADCDLY;
	unsigned int ADCDAT0;
	unsigned int ADCDAT1;
};

#define ADCPRS					200 //Prescaler Setting
#define INT int
#define	TSP_SAMPLE_NUM					4 
#define TSP_INVALIDLIMIT				40

#define TSP_MINX						85
#define TSP_MINY						105

#define TSP_MAXX						965
#define TSP_MAXY						980


//初始化 Touch
void InitTouch();


void GetXY(INT *px,INT *py);  //中断发生时 读取相应的坐标 （和屏幕坐标不一致)

void TransXY(INT *px, INT *py); //转换坐标 转换为屏幕坐标

int is_pushdown();  //按下返回1



#endif

