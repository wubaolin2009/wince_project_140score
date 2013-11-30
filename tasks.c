int g_x = 0,g_y = 0;  //Touch
void TaskDraw(void* p)
{

	static int color = 0xfff;
	while(1)
	{
	
		DrawBitMap();	
		//OSTimeDly(1);
		Rect(g_x,g_y,g_x + 100,g_y + 100,color++);
		
		//DrawBitMap();
		OSTaskSuspend(4);
		
	}
}
int g_reseting = 0;
int Shell(buffer_cmd)
{

	if (strcmp(buffer_cmd,"reset") == 0)
	{
		g_reseting = 1;

		__asm__
		(
			"ldr pc,=0\n"
			:
			:
		);
		//PrintRegs();

	}	
	return 0;
}

void prints_no_newline(char* char_to_print)
{
	while(*char_to_print )
	{
		putc(*char_to_print);
		char_to_print++;
	}

}

void Task0(void* p)
{
	static unsigned char buffer_cmd[1024];
	static int  buffer_pointer = 0;
	if(g_reseting)
	{
		buffer_cmd[ buffer_pointer = 0 ] = '\0';
		g_reseting = 0;
	}
	prints("Task0 is Running Sleep 5 time! ");
	OSTimeDly(5);
	prints("Task0 is Running Again!");
	prints("root#:");
	while(1)
	{	
		unsigned char char_input = getc();
		if( buffer_pointer == 1024)
			return;

		buffer_cmd[buffer_pointer ++] = char_input;
		if(char_input == 13)
		{
			//Excute Shell
			buffer_cmd[buffer_pointer - 1] = '\0';
			Shell(buffer_cmd);
			putc('\n');
			buffer_cmd[0] = '\0';
			buffer_pointer = 0;
		}
		else if(char_input == 8 ) //BackSpace
		{
			if( buffer_pointer <= 1)
			{
				continue;				
			}
			putc(13);  //»Ø³µ

			buffer_cmd[buffer_pointer - 2] = '\0';
			buffer_pointer -= 2;
			prints_no_newline(buffer_cmd);
			putc(' ');
			putc( 8); //BackSpace

			
		}
		else
		{
			putc(char_input);
		}
	}
}




extern g_event;

void Task1(void* p2)
{
	int check;
	prints("Task1 is Running \nTask1 Wait For Task2 exit");
	//OSTimeDly(3);
	//prints(" Task1 is Running ");
	//prints(" Task1 wait for task2 to exit!");
	OSSemPend(g_event,0,&check);
	prints("Task1 Run !");

	//prints(" Task1 exit!");
	//OSTimeDly(2);

	while(1)
	{
		
	}
}

void Task2(void* p3)
{
	prints("Task2 is Running ");
	//OSTimeDly(3);
	prints("Task2 exit !");

	OSSemPost(g_event);

	while(1)
	{
				
	}
}




