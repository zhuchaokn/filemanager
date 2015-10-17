#include "utils.h"
#include "datagram.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void recivefile(char* filename,int fd,int length);
void sendfileto(char* filename,int fd,int length);
void registerMe(char* filename,int fd,int length);
void updateList(char* list, int fd, int length);
void closefd(char* list, int fd, int length);
typedef void (*FileOptP)(char*,int,int);
FileOptP chooseOpt(char *cmd);
