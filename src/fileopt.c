#include "includes/fileopt.h"
FuncMapping optmapping[2] = { { "PUT", recivefile }, { "GET", sendfileto } };
FileOptP chooseOpt(char *cmd) {
	return choose(cmd, optmapping, 2);
}
int file_size(char* filename) {
	struct stat statbuf;
	stat(filename, &statbuf);
	int size = statbuf.st_size;

	return size;
}
void recivefile(char* filename, int fd, int length) {
	DGHead head;
	char buffer[1024];
	//读取文件报文
	int nreads = read(fd,&head,sizeof(head));
	length=head.length;
	nreads=read(fd,buffer,1024);
	int total = nreads;
	int outfd = open(filename, O_WRONLY);
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
	int nreads = read(infd, buffer, 1024);
	int total = nreads;
	while (nreads > 0) {
		write(fd, buffer, nreads);
		nreads = read(fd, buffer, 1024);
		total += nreads;
	}
	close(infd);
}
