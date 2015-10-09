#include "includes/select.h"
#define CLIENT_NUM 3
int server_socket(int port){
	int sock_fd,yes;
	struct sockaddr_in server_addr;
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		ERROR("open server socket:");
	}
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		ERROR("set sockopt");
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
	if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		ERROR("bind");
	}
	if (listen(sock_fd, CLIENT_NUM) == -1) {
		ERROR("listen");
	}
	return sock_fd;
}
fd_set preparefd(int serverfd)
{
	fd_set fdsets;
	FD_ZERO(&fdsets);
	FD_SET(STDIN_FILENO,&fdsets);
	FD_SET(serverfd,&fdsets);
	return fdsets;
}
