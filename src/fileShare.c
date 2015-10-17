/*
   ============================================================================
Name        : fileShare.c
Author      : song
Version     :
Copyright   : Your copyright notice
Description : Hello World in C, Ansi-style
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "includes/mcro.h"
#include "includes/role.h"
int main(int argc,char* args[])
{
	if(argc<3) ERROR(USEAGE_FORMAT);
	FuncMapping mapping[2]=
	{
		{"c",client},
		{"s",server}
	};
	char* role = args[1];
	int port = atoi(args[2]);
	myself.port=port;
	Rolefp roleptr=(Rolefp)choose(role,mapping,2);
	if(roleptr){
		roleptr(port);
	}else{
		ERROR(USEAGE_FORMAT);
	}
	return EXIT_SUCCESS;
}
