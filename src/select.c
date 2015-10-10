#include "includes/select.h"

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
Client accept_client(int serverfd){
	 struct sockaddr_in client_address;
	 Client ct;
	 int len=sizeof(client_address);
	 int socketfd=accept(serverfd,(struct sockaddr *)&client_address, &len);
	 ct.fd=socketfd;
	 return ct;
}
int deal_client(int fd){
	printf("%d is ready\n",fd);
	int nreads=0;
	char buffer[1025];
	nreads=read(fd,buffer,1024);
	while(nreads){
		buffer[nreads]=0;
		printf("%s",buffer);
		nreads=read(fd,buffer,1024);
	}
	printf("%d is done\n");
}
