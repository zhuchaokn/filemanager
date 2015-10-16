#include "global.h"
#ifndef FUNCMPPING
#define FUNCMPPING
typedef struct {
	char cmd[20];
	void* funcp;
}FuncMapping;
#endif
void split_command(char* str,Command* com);
void* choose(char* cmd,FuncMapping map[],int n);
