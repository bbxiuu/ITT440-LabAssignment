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

#define BACKLOG 10

int main(int argc, char *argv[] )
{
int socQotd, new_socket,c,msg_size;
struct sockaddr_in server, client;
char cl_msg[20000];

//creating socket
socQotd = socket(AF_INET,SOCK_STREAM,0);
if(socket_desc==-1)
{

printf("Failed to create socket!");

}

//preparing for socket address
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(17);

//bind
if(bind(socQotd,(struct sockaddr *)&server, sizeof(server))<0)
{

puts("bind failed");
return 1;
}
puts("bind done");

//listen
listen (socQotd,3);

//accept for incoming connection
puts("Waiting for incoming connections....");
c=sizeof(struct sockaddr_in);

//server client connection
new_socket=accept(socQotd,(struct sockaddr *)&client,(socklen_t*)&c);
if(new_socket<0)
{
perror("FAILED TO ACCEPT");
return 1;
}
puts("Connection accepted");


while((msg_size=recv(new_socket,cl_msg,20000,0))>0)
{
write(new_socket,cl_msg,strlen(cl_msg));
}


if(msg_size==-1)
{
puts("FAILED TO RECEIVE MESSAGE");
}

else if(msg_size==0)
{
puts("DISCONNECTED");
fflush(stdout);
}

close(socQotd);

return 0;
}
