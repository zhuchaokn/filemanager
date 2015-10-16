#include "mcro.h"
#include "global.h"
#include<string.h>
#include "utils.h"
#define CLIENT_NUM 100
#define SERVER_NUM 100
#ifndef CLIENT_STR
#define CLIENT_STR

#endif
void server(int port);
void client(int port);
typedef void (*Rolefp)(int);
