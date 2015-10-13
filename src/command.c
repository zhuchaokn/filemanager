#include"includes/command.h"
#include "includes/utils.h"
#define COM_NUM 10
char buffer[400]={0};
FuncMapping mapping[COM_NUM]={
		{"QUIT",quit},
		{"HELP",help},
		{"REGISTER",quit},
		{"CREATOR",creator},
		{"GET",getfile},
		{"PUT",putfile},
		{"LIST",list},
		{"CONNECT",connectTo},
		{"TERMINATE",terminate},
		{"SYNC",syncfile},
		{"DISPLAY",display},
};
void read_command(Command* com)
{
	fgets(buffer,400,stdin);
	split_command(buffer,com);
}
CommandFp dispatch(Command* com)
{
	return choose(com->com,mapping,COM_NUM);
}
void register2server(Command* com);
void help(Command* com)
{
	printf("help\n");
}
void creator(Command* com)
{
	puts("creator");
}
void quit(Command* com)
{
	ROLE_LIVING=0;
}
void putfile(Command* com){

}
void getfile(Command* com){

}
void connectTo(Command* com){

}
void list(Command* com){

}
void terminate(Command* com){

}
void syncfile(Command* com){

}
void display(Command* com){

}


