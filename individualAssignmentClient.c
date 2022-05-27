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
int socQotd, msgSize;
struct sockaddr_in server;
char svMsg[20000], clReply[1024];

//cleaning buffer
memset(svMsg,'\0',sizeof(svMsg));
memset(clReply,'\0',sizeof(clReply));

//creating socket
socQotd=socket(AF_INET, SOCK_STREAM, 0);
if(socQotd==-1)
{
printf("Failed to create socket!");
}


server.sin_family=AF_INET;
server.sin_port=htons(17);//use port 17
server.sin_addr.s_addr=inet_addr("192.168.6.4");//Server IP address

//connect to remote server
if(connect(socQotd,(struct sockaddr *)&server, sizeof(server))<0)
{
puts("connect error");
return 1;
}
puts("Connected \n");

//qotd protocol 


       if(msgSize = (recv(socQotd,svMsg,strlen(svMsg),0))>0)
       {
          //recv quote from server
          recv(socQotd,svMsg,strlen(svMsg),0);
          printf("\nQuote of the day : \n");
          printf("\n%s\n",svMsg);


        if(msgSize < 0)
          {
           puts("Failed to receive quote from the server :(");
          }

        else if(msgSize==0)
        {

         strcpy(clReply,"\nQuote received! Thank you & have a nice day <3");
         send(socQotd,clReply, strlen(clReply) ,0);
         fflush(stdout);
        }

         close(socQotd);
       }

return 0;
}

