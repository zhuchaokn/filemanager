#include "includes/role.h"
#include "includes/command.h"
#include "includes/select.h"
void init_command(Command* comp){
	memset(comp->com,0,20);
	for(int i=0;i<ARG_NUM;i++)
	{
		memset(comp->args[i],0,100);
	}
}
void client(int port)
{
	Command com;
	int results=0;
	init_command(&com);
	int serverfd=server_socket(port);
	printf("%d\n",serverfd);
	fd_set fdsets_template=preparefd(serverfd);
	fd_set fdsets;
	while(ROLE_LIVING)
	{
		fdsets=fdsets_template;
		results=select(FD_SETSIZE,&fdsets,NULL,NULL,NULL);
		if(results<0)
		{ 
			ERROR(SELECT_ERROR); 
		}
		if(FD_ISSET(STDIN_FILENO,&fdsets))
		{
			//read from stdin
			read_command(&com);
			CommandFp comfp=dispatch(&com);
			comfp(&com);
		}else if(FD_ISSET(serverfd,&fdsets))
		{
			printf("some one connect\n");
		}
	}
}
