#include "msgq.h"
#include "bank.h"

int msgid = 0;
MSG_CTOS ctos = {};
MSG_STOC stoc = {};

int login(Account acc)
{
	char path[50] = "./data/";
	char ex[8] = ".data";
	sprintf(path,"%s%s%s",path,acc.id,ex);
	if(0 == access(path,F_OK))
	{
		Account buf = {};
		int fd = open(path,O_RDWR);
		if(0 != read(fd,&buf,sizeof(Account)))
		{
			printf("acc id %s\n",acc.id);
			printf("acc pw %s\n",acc.pass);
			printf("buf id %s\n",buf.id);
			printf("buf pw %s\n",buf.pass);
			if((0 == strcmp(acc.id,buf.id)) && (0 == strcmp(acc.pass,buf.pass)))
			{
				close(fd);
				printf("登陆成功\n");
				
				return 0;
			}
			else
			{
				printf("帐号或密码错误\n");
				close(fd);
				return -1;
			}
		}
		else
		{
			printf("读取信息失败\n");
			return -1;
		}
	}
	else
	{
		printf("此帐号不存在\n");
		return -1;
	}
}

int main(int argc,const char* argv[])
{
	printf("argv %s\n",argv[0]);
	msgid = get_msg(ACCOUNT_PATH,SUBP_CNT);
	
	for(;;)
	{
		recv_msg(msgid,&ctos,sizeof(MSG_CTOS),MSGTY_LOGIN);
		if(login(ctos.acc) == 0) sprintf(stoc.info,"Success pwdcorrect");
		stoc.type = ctos.return_type;
		send_msg(msgid,&stoc,sizeof(MSG_STOC));
	}	
}
