#include "tools.h"
#include <getch.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void clear_stdin(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清理输入缓冲区
}

void any_key(void)
{
	printf("按任意键继续...\n");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getchar();
}

char* get_str(char* str,size_t len)
{
	if(NULL == str)
	{
		puts("空指针异常！");
		return NULL;
	}

	//char *in=fgets(str,len,stdin);
	
	size_t cnt = strlen(str);
	if('\n' == str[cnt-1])
	{
		str[cnt-1] = '\0';
	}
	else
	{
		printf("请输入正确id\n");
		return NULL;
	}
	
	//clear_stdin();

	return str;
}

char get_sex(void)
{
	printf("（m男，w女）：");
	while(true)
	{
		char sex = getch();
		if('w' == sex || 'm' == sex)
		{
			printf("%s\n",'w'==sex?"女":"男");
			return sex;
		}
	}
}

int get_cmd(int start,int end)
{
	clear_stdin();
	printf("请输入指令:");
	while(true)
	{
		int val;
		scanf("%d",&val);
		if(val >= start && val <= end)
		{
			return val;
		}
		else printf("输入有误!请检查\n");
	}
}

char* get_pw(char* passwd,bool is_show,size_t size)
{
	if(NULL == passwd) return NULL;

	int count = 0;
	do{
		char val = getch();
		if(127 == val)
		{
			if(count > 0)
			{
				if(is_show)printf("\b \b");
				count--;
			}
			continue;
		}
		else if(10 == val)
		{
			break;
		}
		passwd[count++] = val;
		if(is_show) printf("*");
	}while(count < size -1);

	passwd[count] = '\0';
	return passwd;
}

