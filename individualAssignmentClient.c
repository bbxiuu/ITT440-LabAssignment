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

#define PORT 17
#define FILENAME "qotd.txt"

int main(int argc, char *argv[])
{
int socQotd,new_socket,c;
struct sockaddr_in server;
char clMsg[20000], svReply[20000];

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

//qotd protocol

//starts here 

while(1)
{
printf("Enter a message: ");
fgets(clMsg,20000,stdin);
send(socQotd,clMsg,20000,0);

if(send(socQotd,clMsg,strlen(clMsg),0)<0)
{
puts("Failed to send message to the server :(");
return 1;
}

if(recv(socQotd,svReply,20000,0)<0)
{
puts("recv failed");
break;
}

puts("_________________________________________\n");
puts("SERVER REPLY: ");
puts(svReply);

}

/*bzero(buffer, 1024);
strcpy(buffer, "Quote received! Thank you & have a nice day <3 \n");
printf("Message from client : %s\n", buffer);
send(socQotd, buffer, strlen(buffer), 0);
*/
//closes here
close(socQotd);
return 0;
}

