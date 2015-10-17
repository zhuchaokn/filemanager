#include "includes/fileopt.h"
#define OPT_NUM 5
FuncMapping optmapping[OPT_NUM] = {
		{ "PUT", recivefile },
		{ "GET", sendfileto },
		{ "REG", registerMe },
		{ "LIST", updateList },
		{ "CLOD", closefd }

};
FileOptP chooseOpt(char *cmd) {
	return choose(cmd, optmapping,OPT_NUM);
}
int file_size(char* filename) {
	struct stat statbuf;
	stat(filename, &statbuf);
	int size = statbuf.st_size;
	return size;
}
void updateList(char* list, int fd, int length){
	printf("server updates peer list:\n");
     memcpy(gpeerList,list,length);
     GPeerCounts=length/sizeof(Peer);
     showPeerList();
}
void closefd(char* list, int fd, int length){
     close(fd);
     FD_CLR(fd,&g_fdsets);
     removeClientOfFd(fd);
}
void registerMe(char* filename, int fd, int length)
{
	   DGHead head={"PORT",myself.port};
	    //将本地端口号发送给服务器
		write(fd, &head, sizeof(DGHead));
		char myIp[20];
		read(fd, myIp, 20 * sizeof(char));
		strncpy(myself.ip, myIp, 20);
}
void recivefile(char* filename, int fd, int length) {
	DGHead head;
	char buffer[1024];
	//读取文件报文
	int nreads = read(fd,&head,sizeof(head));
	length=head.length;
	if(length>1024){
		nreads=read(fd,buffer,1024);
	}else{
		nreads=read(fd,buffer,length);
	}
	int total = nreads;
	//int outfd = open(filename,O_WRONLY|O_CREAT);
	int outfd = open("/tmp/send.txt",O_WRONLY|O_CREAT);
	while (nreads > 0 && total < length) {
		write(outfd, buffer, nreads);
		nreads = read(fd, buffer, 1024);
		total += nreads;
	}
	write(outfd, buffer, nreads);
	close(outfd);
}
void sendfileto(char* filename, int fd, int length) {
	char buffer[1024];
	length=file_size(filename);
	DGHead head={
			"FILE",
			length
	};
	//先发一个头部过去,
	write(fd,&head,sizeof(DGHead));
	int infd = open(filename, O_RDONLY);
	int nreads =0;
	if(length>1024){
		nreads=read(infd, buffer, 1024);
	}else{
		nreads=read(infd, buffer, length);
	}
	int total = nreads;
	while (nreads > 0&&total<length) {
		write(fd, buffer, nreads);
		nreads = read(fd, buffer, 1024);
		total += nreads;
	}
	write(fd, buffer, nreads);
	close(infd);
}
