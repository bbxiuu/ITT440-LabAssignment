#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define BACKLOG 10

int main(int argc,char **argv){

if(argc != 2){
printf("Usage: %s <port>\n", argv[0]);
exit(0);
}

int port = atoi(argv[1]);
printf("Port: %d\n", port);

}
