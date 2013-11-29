void my_putc(unsigned char c) 
{
	 (*(volatile unsigned int *)0x50004020) = c; //发送数据 
} 

int GetIntNum()
{
#define INTOFF1 (*(volatile unsigned int *)0X4A000014)
	int i = INTOFF1;
	return i;
} //莫名的问题。。。

extern g_x,g_y;
void C_IRQHandler()
{
	int irq =  GetIntNum();
if(irq == 14)
{
	OSTimeTick();
}
else
{
	if(is_pushdown() )
	{
		GetXY(&g_x,&g_y);
		TransXY(&g_x,&g_y);
	
		OSTaskResume(4);
	}
	//my_putc('a');
}

volatile unsigned int *srcpnd = (unsigned int *)0x4A000000;

volatile unsigned int *intpnd = (unsigned int *)0x4A000010;
	
volatile unsigned int *subsrcpnd = (unsigned int *)0X4A000018;

*srcpnd =  *srcpnd;
*subsrcpnd = *subsrcpnd;
*intpnd =  *intpnd;

}

