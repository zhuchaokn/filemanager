#define USEAGE_FORMAT "useage: fshare s/c port"
#define SELECT_ERROR "select meet error"
#define Equal(x,y) !strcmp(x,y)
#define ERROR(msg){\
	perror(msg);\
	exit(-1);\
}
#define WARN(msg,args...) fprintf(stderr,msg,##args)
