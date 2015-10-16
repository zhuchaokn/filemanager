#include "includes/global.h"
int ROLE_LIVING = 1;
int GPeerCounts = 1;
Peer gpeerList[PEER_LIMIT] = { { "localhost", "127.0.0.1", 8081 } };
int GClientCounts=0;
Client gclients[PEER_LIMIT];
Peer myself={"localhost","127.0.0.1",8081};
fd_set g_fdsets;
void addPeer(Peer peer){
	gpeerList[GPeerCounts++]=peer;
}
void removePeer(char* ip){
	int i=0;
	for(;i<GPeerCounts;i++){
		if(Equal(ip,gpeerList[i].ip)){
		  break;
		}
	}
	if(i<GPeerCounts){
		for(;i<GPeerCounts;i++){
			gpeerList[i]=gpeerList[i+1];
		}
		GPeerCounts--;
	}
}
void showClientList() {
	printf("id \t%-30s\t%-20s\t%-5s\n", "Hostname", "IP address", "Port No.");
	for (int i = 0; i < GClientCounts; i++) {
		Peer* ptr = &(gclients[i].peer);
		printf("%-3d\t%-30s\t%-20s\t%-5d\n", i + 1, ptr->host, ptr->ip,
				ptr->port);
	}
}
Client* getClient(int id){
	if(id<0||id>GClientCounts){
		return NULL;
	}
	return gclients+id;
}
void addClient(Client ct){
	gclients[GClientCounts++]=ct;
}
void removeClient(char* ip){
	int i=0;
	for(;i<GClientCounts;i++){
		if(Equal(ip,gpeerList[i].ip)){
		  break;
		}
	}
	if(i<GClientCounts){
		for(;i<GClientCounts;i++){
			gpeerList[i]=gpeerList[i+1];
		}
		GClientCounts--;
	}
}
