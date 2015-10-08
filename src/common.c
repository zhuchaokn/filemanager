#include "includes/role.h"
Rolefp choose_role(char* role){
	if(!strcmp(role,"s")){
		return server;
	}else if(!strcmp(role,"c")){
		return client;
	}
	ERROR(USEAGE_FORMAT);
}
