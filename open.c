#include "msgq.h"
#include "tools.h"
#include "bank.h"

int msgid = 0;
MSG_CTOS ctos = {};
MSG_STOC stoc = {};

int open_acc(Account acc)
{
	printf("%s %lf\n",ctos.acc.card,ctos.acc.balance);
	char filename[40] = {"./data/"};
	sprintf(filename,"./data/%s.data",acc.id);
	acc.balance = 0;
	int fd = open(filename,O_CREAT|O_RDWR|O_EXCL,0644);
	if(fd == -1)
	{
		perror("文件创建失败\n");
		return -1;
	}
	if(write(fd,&acc,sizeof(Account)) < 0)
	{
		perror("write\n");
		return -1;
	}
	close(fd);
	printf("用户创建成功!\n");
	sprintf(stoc.info,"Y open success! %s.dat has been create",acc.id);
	return 0;
}

int main(int argc,const char* argv[])
{
	printf("argv %s\n",argv[0]);
	msgid = get_msg(ACCOUNT_PATH,SUBP_CNT);
	
	for(;;)
	{
		recv_msg(msgid,&ctos,sizeof(MSG_CTOS),MSGTY_OPEN);
		open_acc(ctos.acc);
		stoc.type = ctos.return_type;
		printf("%s\n",stoc.info);
		send_msg(msgid,&stoc,sizeof(MSG_STOC));
	}	
}
