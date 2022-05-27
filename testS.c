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
#include <ctype.h>
#include <assert.h>

#define BACKLOG 10
#define PORT 13

int main(int argc, char *argv[] )
{
  int socTime,new_socket,c,msgSize, n_client = 0;
  struct sockaddr_in server, client;

   char buffer[1024] = { 0 };
   char svReply[sizeof(buffer)];

  //creating socket
    socTime = socket(AF_INET,SOCK_STREAM,0);
    if(socTime==-1)
      {

        printf("\nFailed to create socket!");

      }

  //preparing for socket address
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(13); //use port 13

  //bind
    if(bind(socTime,(struct sockaddr *)&server, sizeof(server))<0)
      {

       puts("\nbind failed");
       return 1;
      }
     puts("\nSocket is successfully binded! ");


  //listen
    listen (socTime,3);

  //accept for incoming connection
    puts("\nWaiting for incoming connections....");
    c=sizeof(struct sockaddr_in);


  //server client connection
    new_socket=accept(socTime,(struct sockaddr *)&client,(socklen_t*)&c);
    if(new_socket<0)
      {
       perror("\nFAILED TO ACCEPT");
       return 1;
      }
    puts("Connection accepted!");

  while(1){
    //Counting the request from client
    n_client++;

    //Getting current time
    time_t currentTime;
    time(&currentTime);

    //Sending time to client
    printf("Sending Client current time = %s ", ctime(&currentTime));
    send(new_socket, ctime(&currentTime), 30, 0);
  }

  //Closing socket
    close(new_socket);

return 0;
}

