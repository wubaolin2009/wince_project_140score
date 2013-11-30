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
	while(*s1||*s2) //���S1��S2�Ƚ���� ����\\0��������ѭ���� 
	{ 
		if(*s1-*s2) //�ж�S1��S2��Ӧ���ַ��ǲ��ǲ�ͬ�� 
			return *s1-*s2; //�����ͬ������S1��S2��ASCII֮� 
		else // �����ͬ����ָ��ָ��S1��S2����һ���ַ��Ƚ� 
		{ 
			s2++; 
			s1++; 
		} 
	} 
	return 0; // S1��S2��ȵ�ʱ�򷵻�0�� 
} 

