#include "includes/role.h"
#include "includes/command.h"
#include "includes/select.h"
void notifyClients(){
	int length=GPeerCounts*sizeof(Peer);
	char buffer[1000];
	memcpy(buffer,gpeerList,length);
	DGHead head={"LIST",length};
   for(int i=0;i<GClientCounts;i++)
   {
	   Client* cptr=getClient(i);
	   int nwrites=write(cptr->fd,&head,sizeof(DGHead));
	   write(cptr->fd,buffer,length);
   }
}
void server(int port) {
	int results = 0,clientCount=0;
	int serverfd = server_socket(port);
	fd_set fdsets_template = preparefd(serverfd);
	fd_set fdsets;
	while (ROLE_LIVING) {

		fdsets = fdsets_template;
		results = select(FD_SETSIZE, &fdsets, NULL, NULL, NULL);
		if (results < 0) {
			ERROR(SELECT_ERROR);
		}
		for (int i = 0; i < GClientCounts; i++) {
			Client* cptr=getClient(i);
			if(cptr==NULL) continue;
			int ctfd=cptr->fd;
			int port=0;
			if (ctfd && FD_ISSET(ctfd, &fdsets)) {
				//读取客户端发送过来的监听端口
			 DGHead head;
              read(ctfd,&head,sizeof(head));
              if(Equal(head.cmd,"PORT")){
            	  port=head.length;
              }else if(Equal(head.cmd,"CLOD")){
            	  FD_CLR(ctfd,&fdsets_template);
            	  close(ctfd);
            	  removeClientOfFd(ctfd);
            	  removePeer(cptr->peer.ip);
              }
              write(ctfd,cptr->peer.ip,20);
              Peer peer=cptr->peer;
              peer.port=port;
              addPeer(peer);
              notifyClients();
			}
		}
		if (FD_ISSET(serverfd, &fdsets)) {
			Client ct = accept_client(serverfd); //有其它perr来连我了
			clientCount++;
			FD_SET(ct.fd, &fdsets_template);
			addClient(ct);
			DGHead head={"REG",0};
			write(ct.fd,&head,sizeof(DGHead));
		}
	}
}
