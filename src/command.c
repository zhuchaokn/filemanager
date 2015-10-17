#include"includes/command.h"
#include "includes/fileopt.h"
#include "includes/select.h"
#include "includes/utils.h"
#define COM_NUM 11
char buffer[400] = { 0 };
FuncMapping mapping[COM_NUM] = { { "QUIT", quit }, { "HELP", help }, {
		"REGISTER", register2server }, { "CREATOR", creator }, { "GET", getfile }, { "PUT",
		putfile }, { "LIST", list }, { "CONNECT", connectTo }, { "TERMINATE",
		terminate }, { "SYNC", syncfile }, { "DISPLAY", display } };
void read_command(Command* com) {
	fgets(buffer, 400, stdin);
	split_command(buffer, com);
}
CommandFp dispatch(Command* com) {
	return choose(com->com, mapping, COM_NUM);
}
void register2server(Command* com) {
	char * ip = com->args[0];
	int port = atoi(com->args[1]);
	Client client = connectToIp(ip, port);
	addClient(client);
	FD_SET(client.fd, &g_fdsets);
}
void help(Command* com)
{
	puts("CREATOR: Display your (the students) full name, your UBIT name and UB email address.");
	puts("DISPLAY: Display the IP address of this process, and the port on which this process is listening for incoming connections.");
	puts("REGISTER <server IP> <port no>: This command is used by the client to register itself with the server and to get the IP and listening port numbers of all other peers currently registered with the server. ");
	puts("CONNECT <destination> <port no>: This command is used to establish a connection between two registered clients. ");
	puts("LIST: Display a numbered list of all the connections this process is part of.");
	puts("TERMINATE <connection id> This command will terminate the connection listed under the specified number when LIST is used to display all connections.");
	puts("QUIT Close all connections and terminate this process.");
	puts("GET <connection id> <file> This command will download a file from one host specified in the command.");
	puts("PUT <connection id> <file name> For example, ‘PUT 3 /local/Fall_2015/qiao/a.txt’ will put the file a.txt which is located in /local/Fall_2015/qiao/, to the host on the connection that has connection id 3.");
	puts("SYNC This command will make sure that all peers are up-to-date with their CONNECTED peers.");



}
void creator(Command* com)
{
	puts("Full name: Lingbing Song");
	puts("UBIT name: lingbing");
	puts("UB address: lingbing@buffalo.edu");
}
void closeClient(int id){
	   DGHead head={"CLOD",0};
	   Client* cptr = getClient(id);
	   int fd=cptr->fd;
	   write(fd,&head,sizeof(DGHead));
	   FD_CLR(fd,&g_fdsets);
	   close(fd);
	   removeClientOfId(id);
}
void quit(Command* com) {
	for(int i=0;i<GClientCounts;i++)
	{
		closeClient(i);
	}
	ROLE_LIVING = 0;
}
void putfile(Command* com) {
	int id = atoi(com->args[0]);
	char* fileName = com->args[1];
	Client* cptr = getClient(id-1);
	if (!cptr) {
		WARN("invalid connctiond id %d", 0);
	}
	int fd = cptr->fd;
	int fileNameLen = strlen(com->args[1]);
	DGHead head = { "PUT", fileNameLen };
	write(fd, &head, sizeof(head));
	write(fd, fileName, fileNameLen);
	sendfileto(fileName, fd, 0);
}
void getfile(Command* com) {
	int id = atoi(com->args[0]);
	char* fileName = com->args[1];
	Client* cptr = getClient(id-1);
	if (!cptr) {
		WARN("invalid connctiond id %d\n", 0);
	}
	int fd = cptr->fd;
	int fileNameLen = strlen(com->args[1]);
	DGHead head = { "GET", fileNameLen };
	write(fd, &head, sizeof(head));
	write(fd, fileName, fileNameLen);
	recivefile(fileName, fd, 0);
}
void connectTo(Command* com) {
	char * ip = com->args[0];
	int port = atoi(com->args[1]);
	Client client = connectToIp(ip, port);
	addClient(client);
	FD_SET(client.fd, &g_fdsets);
}
void list(Command* com) {
	showClientList();
}
void terminate(Command* com) {
   int id = atoi(com->args[0]);
   id=id-1;
   closeClient(id);
}
void syncfile(Command* com) {

	DGHead syncHead={"sync",0};
    for(int i=0;i<GClientCounts;i++){
    	Client* cptr = getClient(i);
    }
}
void display(Command* com) {
	printf("ip:%s\t port:%d\n", myself.ip, myself.port);
}

