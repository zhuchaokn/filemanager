#include"includes/command.h"
#include "includes/utils.h"
#define COM_NUM 2
char buffer[400]={0};
FuncMapping mapping[COM_NUM]={
		{"QUIT",quit},
		{"HELP",help}
};
void read_command(Command* com)
{
	fgets(buffer,400,stdin);
	split_command(buffer,com);
}
CommandFp dispatch(Command* com)
{
	CommandFp funcp=choose(com->com,mapping,COM_NUM);
	return notfound;
}
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
void notfound(Command* com)
{
	printf("no command match %s\n",com->com);
}

