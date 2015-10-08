#include<stdio.h>
typedef struct{
	char com[20];
	char arg1[100];
	char arg2[100];
	char arg3[100];
} Command;
typedef void (*CommandFp)(Command* );
void read_command(Command* com);
CommandFp dispatch(Command* com);
void help(Command* com);
void creator(Command* com);
void quit(Command* com);
