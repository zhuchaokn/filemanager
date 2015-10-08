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
	if(argc<3)
	{
		ERROR(USEAGE_FORMAT);
	}
	char* role = args[1];
	int port = atoi(args[2]);
	Rolefp roleptr=choose_role(role);
	Roleptr(port);
	return EXIT_SUCCESS;
}
