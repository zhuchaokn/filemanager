#include "includes/role.h"
#include "includes/command.h"
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
	 g_fdsets=preparefd(serverfd);
	fd_set fdsets;
	while(ROLE_LIVING)
	{

		fdsets=g_fdsets;
		results=select(FD_SETSIZE,&fdsets,NULL,NULL,NULL);
		if(results<0)
		{ 
			ERROR(SELECT_ERROR); 
		}
		for(int i=0;i<GClientCounts;i++){
			Client* cptr=getClient(i);
			int ctfd=cptr->fd;
			if(ctfd&&FD_ISSET(ctfd,&fdsets))
			{
				deal_client(ctfd);
			}
		}
		if(FD_ISSET(STDIN_FILENO,&fdsets))
		{
			//有键盘输入了
			read_command(&com);
			puts(com.com);
			CommandFp comfp=dispatch(&com);
			if(comfp){
				comfp(&com);
			}else{
				WARN("no match command found %s",com.com);
			}
		}else if(FD_ISSET(serverfd,&fdsets))
		{
			Client ct=accept_client(serverfd);//有其它perr来连我了
			FD_SET(ct.fd,&g_fdsets);
			addClient(ct);
		}
	}
}
