#include<stdio.h>
#include"datagram.h"
#include<string.h>
#include "global.h"
#include "select.h"
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
