#include "includes/select.h"
#include "includes/datagram.h"
#include "includes/fileopt.h"
int server_socket(int port) {
	int sock_fd, yes;
	struct sockaddr_in server_addr;
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		ERROR("open server socket:");
	}
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
			== -1) {
		ERROR("set sockopt");
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
	if (bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr))
			== -1) {
		ERROR("bind");
	}
	if (listen(sock_fd, CLIENT_NUM) == -1) {
		ERROR("listen");
	}
	return sock_fd;
}
fd_set preparefd(int serverfd) {
	fd_set fdsets;
	FD_ZERO(&fdsets);
	FD_SET(STDIN_FILENO, &fdsets);
	FD_SET(serverfd, &fdsets);
	return fdsets;
}
Client accept_client(int serverfd) {
	struct sockaddr_in client_address;
	Client ct;
	int len = sizeof(client_address);
	int socketfd = accept(serverfd, (struct sockaddr *) &client_address, &len);
	ct.fd = socketfd;
	ct.peer.port = ntohs(client_address.sin_port);
	char* ip = inet_ntoa(client_address.sin_addr);
	strncpy(ct.peer.ip, ip, 20);
	//host
	printf("receive connection from %s\n",ip);
	return ct;
}
int deal_client(int fd) {
	int nreads = 0;
	char buffer[500];
	DGHead head;
	//读取命令
	nreads = read(fd, &head, sizeof(DGHead));
	//读取文件名称
	if (head.length > 0) {
		nreads = read(fd, buffer, head.length);
		buffer[nreads] = 0;
	}
	FileOptP func = chooseOpt(head.cmd);
	if (!func) {
		fprintf(stderr, "Unrecognized option %s\n", head.cmd);
	} else {
		func(buffer, fd, head.length);
	}
	return 0;
}
Client connectToIp(char* ip, int port) {
	printf("connect to %s %d\n",ip,port);
	int client_sockfd;
	int len;
	Client client={0};
	struct sockaddr_in address; //服务器端网络地址结构体
	int result;
	client_sockfd = socket(AF_INET, SOCK_STREAM, 0); //建立客户端socket
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip);
	address.sin_port = port;
	len = sizeof(address);
	result = connect(client_sockfd, (struct sockaddr *) &address, len);
	printf("connect to %d\n",result);
	if (result == -1) {
		return client;
	}
	client.fd=client_sockfd;
	strncpy(client.peer.ip,ip,20);
	client.peer.port=port;
	return client;
}
