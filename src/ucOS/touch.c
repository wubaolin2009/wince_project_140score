#include "touch.h"

//初始化 Touch
void InitTouch()
{
	struct S3C_TOUCH* s3cTouch = (struct S3C_TOUCH*)ADCCONBASE;

	s3cTouch->ADCDLY = 50000; 

	s3cTouch->ADCCON =    (1      << 14) |    /* A/D Converter Enable					*/
		(ADCPRS <<  6) |    /* Prescaler Setting					*/
		(0      <<  3) |    /* Analog Input Channel : 0				*/ 
		(0      <<  2) |    /* Normal Operation Mode				*/
		(0      <<  1) |    /* Disable Read Start					*/
		(0      <<  0);     /* No Operation							*/

	s3cTouch->ADCTSC =    (0      <<  8) |    /* UD_Sen								*/
		(1      <<  7) |    /* YMON  1 (YM = GND)					*/
		(1      <<  6) |    /* nYPON 1 (YP Connected AIN[n])		*/
		(0      <<  5) |    /* XMON  0 (XM = Z)						*/
		(1      <<  4) |    /* nXPON 1 (XP = AIN[7])				*/
		(0      <<  3) |    /* Pull Up Disable						*/
		(0      <<  2) |    /* Normal ADC Conversion Mode			*/
		(3      <<  0);     /* Waiting Interrupt*/
}



void GetXY(INT *px,INT *py)  //中断发生时 读取相应的坐标 （和屏幕坐标不一致)
{
	struct S3C_TOUCH* s3cTouch = (struct S3C_TOUCH*)ADCCONBASE;

	INT i;
	INT xsum, ysum;
	INT x, y;
	INT dx, dy;

	xsum = ysum = 0;

	for (i = 0; i < TSP_SAMPLE_NUM; i++)
	{
		s3cTouch->ADCTSC =    (0      <<  8) |        /* UD_Sen								*/
			(1      <<  7) |        /* YMON  1 (YM = GND)					*/
			(1      <<  6) |        /* nYPON 1 (YP Connected AIN[n])		*/
			(0      <<  5) |        /* XMON  0 (XM = Z)						*/
			(1      <<  4) |        /* nXPON 1 (XP = AIN[7])				*/
			(1      <<  3) |        /* Pull Up Enable						*/
			(1      <<  2) |        /* Auto ADC Conversion Mode				*/
			(0      <<  0);         /* No Operation Mode					*/

		s3cTouch->ADCCON |= (1 << 0);             /* Start Auto conversion				*/

		while (s3cTouch->ADCCON & 0x1);               /* check if Enable_start is low			*/
		while (!(s3cTouch->ADCCON & (1 << 15)));      /* Check ECFLG							*/

		x = (0x3ff & s3cTouch->ADCDAT1);
		y = 0x3ff - (0x3ff & s3cTouch->ADCDAT0);

		xsum += x;
		ysum += y;
	}


	*px = xsum / TSP_SAMPLE_NUM;

	*py = ysum / TSP_SAMPLE_NUM;

	s3cTouch->ADCTSC =    (1      <<  8) |            /* UD_Sen								*/
		(1      <<  7) |            /* YMON  1 (YM = GND)					*/
		(1      <<  6) |            /* nYPON 1 (YP Connected AIN[n])		*/
		(0      <<  5) |            /* XMON  0 (XM = Z)						*/
		(1      <<  4) |            /* nXPON 1 (XP = AIN[7])				*/
		(0      <<  3) |            /* Pull Up Disable						*/
		(0      <<  2) |            /* Normal ADC Conversion Mode			*/
		(3      <<  0);             /* Waiting Interrupt					*/

	dx = (*px > x) ? (*px - x) : (x - *px);
	dy = (*py > y) ? (*py - y) : (y - *py);

	if(*px <0)
		*px = 0;
	if(*py < 0)
		*py  =0;

	//return((dx > TSP_INVALIDLIMIT || dy > TSP_INVALIDLIMIT) ? 0: 1);

}




void TransXY(INT *px, INT *py)
{
	static int TSP_LCDX = (240);
	static int TSP_LCDY = (320);
    *px = (*px - TSP_MINX) * TSP_LCDX / (TSP_MAXX - TSP_MINX);
    *py = (*py - TSP_MINY) * TSP_LCDY / (TSP_MAXY - TSP_MINY);

    if (*px  <        0) *px = 0;
    if (*px >= TSP_LCDX) *px = TSP_LCDX - 1;

    if (*py  <        0) *py = 0;
    if (*py >= TSP_LCDY) *py = TSP_LCDY - 1;
}

int is_pushdown()
{
	struct S3C_TOUCH* s3cTouch = (struct S3C_TOUCH*)ADCCONBASE;
	if(s3cTouch->ADCDAT0 & 0x8000)  //up
		return 0;
	return 1;

}


