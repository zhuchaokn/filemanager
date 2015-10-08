#include "includes/role.h"
void init_command(Command* comp){
	memset(comp->com,0,20);
	memset(comp->arg1,0,100);
	memset(comp->arg2,0,100);
	memset(comp->arg3,0,100);
}
void client(int port)
{
	Command com;
	init_command(&com);
	while(ROLE_LIVING)
	{
         read_command(&com);
         CommandFp comfp=dispatch(&com);
         comfp(&com);
	}
}
