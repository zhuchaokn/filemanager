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
void register_client(Client clients[],int n,Client ct)
{
   for(int i=0;i<n;i++)
   {
	   if(clients[i].fd==0)
	   {
		   clients[i]=ct;
	   }
   }
}
void client(int port)
{
	Command com;
	Client clients[CLIENT_NUM];
	int results=0;
	init_command(&com);
	int serverfd=server_socket(port);
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
		for(int i=0;i<CLIENT_NUM;i++){
			int ctfd=clients[i].fd;
			if(ctfd&&FD_ISSET(ctfd,&fdsets))
			{
				deal_client(ctfd);
			}
		}
		if(FD_ISSET(STDIN_FILENO,&fdsets))
		{
			//有键盘输入了
			read_command(&com);
			CommandFp comfp=dispatch(&com);
			if(comfp){
				comfp(&com);
			}else{
				WARN("no match command found %s",com.com);
			}
		}else if(FD_ISSET(serverfd,&fdsets))
		{
			Client ct=accept_client(serverfd);//有其它perr来连我了
			FD_SET(ct.fd,&fdsets_template);
			register_client(clients,CLIENT_NUM,ct);
		}
	}
}
