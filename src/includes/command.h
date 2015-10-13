#include<stdio.h>
#include<string.h>
#include "global.h"
#define ARG_NUM 3
#ifndef COM_STR
#define COM_STR
typedef struct{
	char com[20];
	char args[ARG_NUM][100];
} Command;
typedef void (*CommandFp)(Command* );
typedef struct{
	char* com;
	CommandFp funp;
}ComMapping;
#endif
void read_command(Command* com);
CommandFp dispatch(Command* com);
void register2server(Command* com);
void display(Command* com);
void help(Command* com);
void creator(Command* com);
void quit(Command* com);
void putfile(Command* com);
void getfile(Command* com);
void connectTo(Command* com);
void list(Command* com);
void terminate(Command* com);
void syncfile(Command* com);
