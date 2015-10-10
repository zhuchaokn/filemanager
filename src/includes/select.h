#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "mcro.h"
#include "role.h"
fd_set preparefd(int);
Client accept_client(int serverfd);
int deal_client(int fd);
