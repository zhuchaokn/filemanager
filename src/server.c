#include "includes/role.h"
#include "includes/command.h"
#include "includes/select.h"
void notifyClients(){
	DGHead head={"LIST",GClientCounts*sizeof(Peer)};
   for(int i=0;i<GClientCounts;i++)
   {
	   Client* cptr=getClient(i);
	   write(cptr->fd,&head,GPeerCounts*sizeof(Peer));
	   write(cptr->fd,gpeerList,GPeerCounts*sizeof(Peer));
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
              read(ctfd,&port,sizeof(int));
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
		}
	}
}
