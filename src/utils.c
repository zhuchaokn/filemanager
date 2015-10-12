#include "includes/utils.h"
void* choose(char* cmd,FuncMapping map[],int n){
	for(int i=0;i<n;i++)
	{
		if(Equal(cmd,map[i].cmd))
		{
			return map[i].funcp;
		}
	}
	return NULL;
}
int read2sp(char* from,char* to)
{
	int i=0;
	for(;from[i]&&from[i]!=' '&&from[i]!='\n';i++)
	{
		to[i]=from[i];
	}
	while(from[i]&&from[i]==' ')i++;
	return i;
}
void split_command(char* str,Command* com){
	int len=strlen(str);
    int index=read2sp(str,com->com);
    int i=0;
    while(index<len&i<ARG_NUM)
    {
    	str+=index;
    	index=read2sp(str,com->args[i++]);
    }
}
