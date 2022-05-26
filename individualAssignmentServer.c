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
#define LSIZ 128
#define RSIZ 10

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

//function to return random quote
char  print_random_line(FILE *istream, int line_index) {
  Line_Count(istream, line_index);
  int ch,tot = 0;
  char line[RSIZ][LSIZ];
  int i = 0;

  printf("\n");

          while(fgets(line[i], LSIZ, istream)) 
	{
                 line[i][strlen(line[i]) - 1] = '\0';
                 i++;
        }

         tot = i+1;
         printf("\n The quote from line %d  is : \n",line_index + 1);

        for(i = 0; i < 1; ++i)
           {
            printf(" %s\n", line[i]);
           }

return line_index;
                                                        }


int main(int argc, char *argv[] )
{
  int socQotd,new_socket,c;
  struct sockaddr_in server, client;
  char svMsg[20000],clReply[20000];

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

//starts here

    srand((unsigned) time(NULL));
    FILE *istream = fopen(FILENAME, "r");
    assert(istream);
    int lc = Line_Count(istream, RAND_MAX);
    assert(lc && lc < RAND_MAX);

while(1)
{

  print_random_line(istream, rand() % lc);


  strcpy(svMsg, "Quote of the day: \n");
  printf("\n%s",svMsg);
  send(new_socket,svMsg,20000,0);

  if(send(new_socket,svMsg,strlen(svMsg),0)<0)
    {
     puts("Failed to send quote to the client :(");
     return 1;
}

if(recv(new_socket,clReply,20000,0)<0)
{
puts("recv failed");
break;
}

 fclose(istream);
 close(socQotd);


}

   // fclose(istream);

//closes here


 // close(socQotd);

return 0;
}
