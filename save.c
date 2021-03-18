#include "msgq.h"
#include "bank.h"

int msgid = 0;
MSG_CTOS ctos = {};
MSG_STOC stoc = {};

void save(void)
{
	printf("%s %lf\n",ctos.acc.card,ctos.acc.balance);
	sprintf(stoc.info,"Y open success!");
}

int main(int argc,const char* argv[])
{
	printf("argv %s\n",argv[0]);
	msgid = get_msg(ACCOUNT_PATH,SUBP_CNT);
	
	for(;;)
	{
		recv_msg(msgid,&ctos,sizeof(MSG_CTOS),MSGTY_SAVE);
		save();
		stoc.type = ctos.return_type;
		send_msg(msgid,&stoc,sizeof(MSG_STOC));
	}	
}
