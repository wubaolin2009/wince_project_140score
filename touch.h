#ifndef _TOUCH_MY_H
#define _TOUCH_MY_H


#define ADCCONBASE 0x58000000  //ADC Controler�Ļ�ַ



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


//��ʼ�� Touch
void InitTouch();


void GetXY(INT *px,INT *py);  //�жϷ���ʱ ��ȡ��Ӧ������ ������Ļ���겻һ��)

void TransXY(INT *px, INT *py); //ת������ ת��Ϊ��Ļ����

int is_pushdown();  //���·���1



#endif

