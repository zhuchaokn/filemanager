#include"mcro.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define PEER_LIMIT 100
extern int ROLE_LIVING;
#ifndef PEER_STU
#define PEER_STU
typedef struct{
	char host[30];
	char ip[20];
	int port;
}Peer;
typedef struct{
	int fd;
	Peer peer;
}Client;
extern int GPeerCounts;
extern Peer gpeerList[PEER_LIMIT];
extern Peer myself;
extern int GClientCounts;
extern fd_set g_fdsets;
#endif
void addPeer(Peer peer);
void showClientList();
Client* getClient(int id);
void addClient(Client ct);
#ifndef COM_STR
#define COM_STR
#define ARG_NUM 3
typedef struct{
	char com[20];
	char args[ARG_NUM][100];
} Command;
typedef void (*CommandFp)(Command*);
typedef struct{
	char* com;
	CommandFp funp;
}ComMapping;
#endif

