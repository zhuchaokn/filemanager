#include"includes/command.h"
#include "includes/utils.h"
#define COM_NUM 2
char buffer[400]={0};
ComMapping mapping[]={
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
	for(int i=0;i<COM_NUM;i++)
	{
		if(!strcmp(com->com,mapping[i].com))
		{
			return mapping[i].funp;
		}
	}
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

