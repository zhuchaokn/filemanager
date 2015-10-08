#include "mcro.h"
#include "global.h"
#include<string.h>
void server(int port);
void client(int port);
typedef void (*Rolefp)(int);
Rolefp choose_role(char* role);
