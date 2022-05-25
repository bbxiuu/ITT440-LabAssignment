#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int socQotd,new_socket,c;
struct sockaddr_in server;
char clmsg[20000],sv_reply[20000];

//create socket
socQotd=socket(AF_INET, SOCK_STREAM, 0);
if(socQotd==-1)
{
printf("Could not create socket");
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


//message to server
while(1)
{
printf("Enter a message: ");
fgets(clmsg,20000,stdin);
send(socQotd,clmsg,20000,0);

if(send(socQotd,clmsg,strlen(clmsg),0)<0)
{
puts("FAILED TO SEND");
return 1;
}

if(recv(socQotd,sv_reply,20000,0)<0)
{
puts("recv failed");
break;
}

puts("_________________________________________\n");
puts("SERVER REPLY: ");
puts(sv_reply);

}

close(socQotd);
return 0;
}

