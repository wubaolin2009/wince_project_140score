#include "string.h"

int strlen(char* char_to_get_length)
{
	char* char_tmp = char_to_get_length;
	int   string_length = 0;
	while( *char_tmp != '\0' )
	{
		string_length ++;
		char_tmp ++;
	}
	return string_length;
}

void strcpy(char* char_to,char* char_src)
{
	char* char_tmp_src = char_src;
	char* char_tmp_to  = char_to;
	while( *char_tmp_src != '\0')
	{
		*char_tmp_to = *char_tmp_src;
		char_tmp_to ++;
		char_tmp_src ++;
	}
	*char_tmp_to = '\0';

}

int strcmp(char *s1,char *s2) 
{ 
	while(*s1||*s2) //如果S1和S2比较完毕 （‘\\0’）跳出循环； 
	{ 
		if(*s1-*s2) //判断S1和S2对应的字符是不是不同； 
			return *s1-*s2; //如果不同，返回S1和S2的ASCII之差； 
		else // 如果相同，让指针指向S1和S2的下一个字符比较 
		{ 
			s2++; 
			s1++; 
		} 
	} 
	return 0; // S1和S2相等的时候返回0； 
} 

