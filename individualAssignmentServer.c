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

#define PORT 17
#define FILENAME "qotd.txt"
#define LSIZ 1024
#define RSIZ 50

// Return line count, but stop once the count exceeds a maximum
  int Line_Count(FILE *istream, int line_index) {
  int lc = 0;
  int previous = '\n';
  int ch;
  rewind(istream);
  while (line_index > 0 && (ch = fgetc(istream)) != EOF) {
    if (ch == '\n') {
      line_index--;
    }
    if (previous == '\n') {
      lc++;
    }
    previous = ch;
  }

  return lc;
}


int main(int argc, char *argv[] )
{
  int socQotd,new_socket,c,msgSize,valread;
  struct sockaddr_in server, client;

   char buffer[1024] = { 0 };
   char svReply[sizeof(buffer)];
   char svReply2[sizeof(buffer)];

  //creating socket
    socQotd = socket(AF_INET,SOCK_STREAM,0);
    if(socQotd==-1)
      {

        printf("\nFailed to create socket!");

      }

  //preparing for socket address
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(17); //use port 17

  //bind
    if(bind(socQotd,(struct sockaddr *)&server, sizeof(server))<0)
      {

       puts("\nbind failed");
       return 1;
      }
     puts("\nSocket is successfully binded! ");

  //listen
    listen (socQotd,3);

  //accept for incoming connection
    puts("\nWaiting for incoming connections....");
    c=sizeof(struct sockaddr_in);


 //server client connection
    new_socket=accept(socQotd,(struct sockaddr *)&client,(socklen_t*)&c);
    if(new_socket<0)
      {
       perror("\nFAILED TO ACCEPT");
       return 1;
      }
    puts("Connection accepted!");

  //qotd protocol

    srand((unsigned) time(NULL));
    FILE *istream = fopen(FILENAME, "r");
    assert(istream);
    int lc = Line_Count(istream, RAND_MAX);
    assert(lc && lc < RAND_MAX);

    int line_index = Line_Count(istream, line_index);

 
  int ch,tot=0;
  char line[RSIZ][LSIZ];
  char quote[sizeof(buffer)];
  int i = 0;


  printf("\n");

        while(fgets(line[i], LSIZ, istream))
        {
                 line[i][strlen(line[i]) - 1] = '\0';
                 i++;
        }

         tot =i+1;

         printf("\nRandom quote chosen : \n");
        for(i = 0; i < 1; ++i)
           {
            sprintf(quote,"%s", line[rand()%tot]);
            puts(quote);
           }
       strcpy(svReply, "Hi from server!\n\nToday's quote is : ");
       strcpy(svReply2, quote);

       printf("\n****************************************************************************************************************************\n");


 //sending random quote to the client

    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, svReply, strlen(svReply), 0);
    send(new_socket, svReply2, strlen(svReply2), 0);
    printf("Quote has been sent!\n\n");

  // closing the connected socket
    close(new_socket);
  // closing the listening socket
    shutdown(socQotd, SHUT_RDWR);

    fclose(istream);

return 0;
}
