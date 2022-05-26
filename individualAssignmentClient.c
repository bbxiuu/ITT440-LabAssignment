#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
int socQotd,new_socket,c;
struct sockaddr_in server;
string quotes[20000],sv_reply[20000];

//creating socket
socQotd=socket(AF_INET, SOCK_STREAM, 0);
if(socQotd==-1)
{
printf("Failed to create socket!");
}


server.sin_addr.s_addr=inet_addr("192.168.6.4");//Server IP address
server.sin_family=AF_INET;
server.sin_port=htons(17);//use port 17

//connect to remote server
if(connect(socQotd,(struct sockaddr *)&server, sizeof(server))<0)
{
puts("connect error");
return 1;
}
puts("Connected \n");


close(socQotd);
return 0;
}

