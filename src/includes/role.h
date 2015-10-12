#include "mcro.h"
#include "global.h"
#include<string.h>
#include "utils.h"
#define CLIENT_NUM 3
#ifndef CLIENT_STR
#define CLIENT_STR
typedef struct{
   int fd;
   char address [50];
   int port;
}Client;
#endif
void server(int port);
void client(int port);
typedef void (*Rolefp)(int);
