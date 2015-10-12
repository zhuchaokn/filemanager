#ifndef DATAGRAM
#define DATAGRAM
typedef struct{
	char cmd[6];//命令 put get register terminate
	int length;//报文长度
}DGHead;
#endif

