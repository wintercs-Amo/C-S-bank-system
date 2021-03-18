#ifndef BANK_H
#define BANK_H
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/types.h>

#define MSGTY_OPEN	(1)
#define MSGTY_DESTORY	(2)
#define MSGTY_UNLOCK	(3)
#define MSGTY_LOGIN	(4)
#define MSGTY_QUERY	(5)
#define MSGTY_SAVE	(6)
#define MSGTY_TAKE	(7)
#define MSGTY_TRANSFER	(8)
#define MSGTY_REPASS	(9)

#define SUBP_CNT 	(9)
#define ACCOUNT_PATH 	"./account/"
#define ID_PATH 	"./account/.id.dat"


typedef struct Account
{
	double balance;
	char id[20];
	char pass[7];
	char card[19];
	char islock;
}Account;

typedef struct MSG_CTOS
{
	long type;
	Account acc;
	pid_t return_type;
}MSG_CTOS;

typedef struct MSG_STOC
{
	long type;
	char info[256];
}MSG_STOC;

#endif//BANK_H
