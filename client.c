#include "msgq.h"
#include "bank.h"
#include "tools.h"

int msgid = 0;
MSG_CTOS ctos = {};
MSG_STOC stoc = {};
static int lock = 0;

void open_acc(void)
{
	msgid = get_msg(ACCOUNT_PATH,SUBP_CNT);
	ctos.return_type = getpid();
	ctos.type = MSGTY_OPEN;
	Account acc = {};
	printf("请输入姓名：");
	scanf("%s",acc.id);
	printf("请输入身份证：");
	scanf("%s",acc.card);
	printf("请输入密码：");
	scanf("%s",acc.pass);
	ctos.acc = acc;
	ctos.acc.islock = 0;
	ctos.acc.balance = 0;
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	if(stoc.info != NULL)
	{
		printf("帐号:%s,开户成功\n",stoc.info);
	}
	else
	{		
		printf("开户失败\n");
	}
	any_key();
}

void login_menu(char* id);
void login(void)
{
	msgid = get_msg(ACCOUNT_PATH,SUBP_CNT);
	ctos.return_type = getpid();
	ctos.type = MSGTY_LOGIN;
	if(lock >= 3)
	{
		printf("您已被锁定，请解锁\n");
		getchar();
		return;
	}
	Account acc = {};
	printf("请输入帐号：");
	scanf("%s",acc.id);
	printf("请输入密码：");
	scanf("%s",acc.pass);
	ctos.acc = acc;
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	
	if(0 == strcmp(stoc.info,"Success pwdcorrect"))
	{
		printf("%s,登陆成功\n",acc.id);
		getch();
		login_menu(acc.id);
	}
	else
	{	
		lock++;	
		printf("帐号或密码错误\n");
		getch();
	}
	any_key();
}

void destory(void)
{
	printf("%s",__func__);
}

void unlock(void)
{
	printf("%s",__func__);
}

void query(void)
{
	printf("%s",__func__);
}

void save(void)
{
	printf("%s",__func__);
}

void take(void)
{
	printf("%s",__func__);
}

void transfer(void)
{
	printf("%s",__func__);
}

void repass(void)
{
	printf("%s",__func__);
}

int main_menu(void)
{
	system("clear");
	puts("***欢迎使用银行***");
	puts("1、开户	2、销户");
	puts("3、解锁	4、登录");
	puts("5、退卡");
	return get_cmd(1,5);
}

int sub_menu(char* id)
{
	system("clear");
	char str[50] = {};
	sprintf(str,"***%s客户,您好!***",id);
	puts(str);
	puts("1、查询	2、存款");
	puts("3、取款	4、转账");
	puts("5、改密	6、退卡");
	return get_cmd(1,6);
}

void login_menu(char* id)
{
	for(;;)
	{
		switch(sub_menu(id))
		{
			case (1): query(); break;
			case (2): save(); break;
			case (3): take(); break;
			case (4): transfer(); break;
			case (5): repass(); break;
			case (6): exit(-1);
		}
	}
}

int main()
{
	for(;;)
	{
		switch(main_menu())
		{
			case (1): open_acc(); break;
			case (2): destory(); break;
			case (3): unlock(); break;
			case (4): login(); break;
			case (5): return 0;
		}

	}
	
	
	/*msgid = get_msg(ACCOUNT_PATH,SUBP_CNT);

	ctos.acc.balance = 10;
	ctos.return_type = getpid();
	
	ctos.type = MSGTY_OPEN;
	sprintf(ctos.acc.card,"open");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);
	
	ctos.type = MSGTY_DESTORY;
	sprintf(ctos.acc.card,"destory");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);

	ctos.type = MSGTY_UNLOCK;
	sprintf(ctos.acc.card,"unlock");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);
	
	ctos.type = MSGTY_LOGIN;
	sprintf(ctos.acc.card,"LOGIN");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);
	
	
	ctos.type = MSGTY_QUERY;
	sprintf(ctos.acc.card,"QUERY");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);

	ctos.type = MSGTY_SAVE;
	sprintf(ctos.acc.card,"SAVE");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);
	
	ctos.type = MSGTY_TAKE;
	sprintf(ctos.acc.card,"TAKE");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);
	
	ctos.type = MSGTY_TRANSFER;
	sprintf(ctos.acc.card,"TRANSFER");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);
	
	ctos.type = MSGTY_REPASS;
	sprintf(ctos.acc.card,"REPASS");
	send_msg(msgid,&ctos,sizeof(MSG_CTOS));
	recv_msg(msgid,&stoc,sizeof(MSG_STOC),ctos.return_type);
	printf("%s\n",stoc.info);*/
	
}
