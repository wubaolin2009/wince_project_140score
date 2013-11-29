#include "LCD.h"
void InitDisplay()  
{
	GPCUP = 0xFFFFFFFF;

	GPCCON = 0xAAAAAAAA;

	GPDUP = 0xFFFFFFFF;

	GPDCON = 0xAAAAAAAA;
	struct S3C_LCD*  s3cLcd = (struct S3C_LCD*)LCDBASE;
	
	s3cLcd->LCDCON1 =   (6           <<  8) |      	 /* VCLK = HCLK / ((CLKVAL + 1) * 2) -> About 7 Mhz  */
		(0   <<  7)  |       /* 0 : Each Frame                                   */
		(3      <<  5) |       /* TFT LCD Pannel                                   */
		(12     <<  1) |       /* bpp Mode                                         */
		(0           <<  0) ;       /* Disable LCD Output                               */

	s3cLcd->LCDCON2 = 	   (1        << 24) |   /* VBPD          :   1                              */
		((320-1)       << 14) |   /* Vertical Size : 320 - 1                          */
		(2        <<  6) |   /* VFPD          :   2                              */
		(1        <<  0) ;   /* VSPW          :   1                              */

	s3cLcd->LCDCON3 =    	(6 << 19) |   
		((240-1) <<  8) |   /* HOZVAL_TFT    : 240 - 1                          */
		(2       <<  0) ;   /* HFPD          :   2                              */	

	s3cLcd->LCDCON4 = (13       <<  8) |   /* MVAL          :  13              */
		(4        <<  0) ;   /* HSPW          :   4                              */


	s3cLcd->LCDCON5 = 	(0           << 12) |       /* BPP24BL       : LSB valid                        */
		(1           << 11) |       /* FRM565 MODE   : 5:6:5 Format                     */
		(0           << 10) |       /* INVVCLK       : VCLK Falling Edge                */
		(1           <<  9) |       /* INVVLINE      : Inverted Polarity                */
		(1           <<  8) |       /* INVVFRAME     : Inverted Polarity                */
		(0           <<  7) |       /* INVVD         : Normal                           */
		(0           <<  6) |       /* INVVDEN       : Normal                           */
		(0           <<  5) |       /* INVPWREN      : Normal                           */
		(0           <<  4) |       /* INVENDLINE    : Normal                           */
		(0           <<  3) |       /* PWREN         : Disable PWREN                    */
		(0           <<  2) |       /* ENLEND        : Disable LEND signal              */
		(0           <<  1) |       /* BSWP          : Swap Disable                     */
		(1           <<  0) ;       /* HWSWP         : Swap Enable                      */

	s3cLcd->LCDSADDR1= ((PHYBASE     >> 22)   << 21) ;


	s3cLcd->LCDSADDR2 = ((PHYBASE + 320 * 240 * 2) >>1) + 1;

	s3cLcd->LCDSADDR3= (((320 - 320) / 1) << 11) | (320 / 1);     


	LPCSEL    |= 0x3;

	TPAL      = 0x0;        
	s3cLcd->LCDCON1  |= 1;  //´ò¿ªLCD
}

void Rect(int x,int y,int x1,int y1,short color)
{
	char* mem = (char*)(PHYBASE);
	int i,j;
	if(x1>239)
		x1 = 239;
	if(y1>319)
		y1 = 319;
	for(i = x;i < x1;i++)
	{
		for(j = y;j<y1;j++)
		{
			int offset = (i) + j*240;
			 *( (short*)(mem + offset * 2)) = color;
		}
	}
	
}
