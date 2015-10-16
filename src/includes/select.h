#include "global.h"
#include "role.h"
fd_set preparefd(int);
Client accept_client(int serverfd);
int deal_client(int fd);
Client connectToIp(char* ip,int port);
