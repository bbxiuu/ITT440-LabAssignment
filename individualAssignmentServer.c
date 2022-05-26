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

int main(int argc, char *argv[] )
{
int socQotd,new_socket,c;
struct sockaddr_in server, client;

//creating socket
socQotd = socket(AF_INET,SOCK_STREAM,0);
if(socQotd==-1)
{

printf("Failed to create socket!");

}

//preparing for socket address
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(17); //use port 17

//bind
/*if(bind(socQotd,(struct sockaddr *)&server, sizeof(server))<0)
{

puts("bind failed");
return 1;
}
puts("bind done");
*/

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

close(socQotd);

return 0;
}
