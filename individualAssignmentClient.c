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
#include <assert.h>

#define PORT 17
#define FILENAME "qotdRcv.txt"

int main(int argc, char *argv[])
{
int socQotd,new_socket, msgSize,c,valread;
struct sockaddr_in server;

char buffer[1024] = { 0 };
char clMsg[sizeof(buffer)];

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
puts("Connected successfully! \n");

//receive qotd and write into qotdRcv.txt

 FILE *istream = fopen(FILENAME, "w");
 assert(istream);

    strcpy(clMsg,"\nHello from Client!\n");
    send(socQotd, clMsg, strlen(clMsg), 0);
    printf("\nGreeting server...\n\n");
    valread = read(socQotd, buffer, 1024);
    printf("%s\n\n", buffer);

    fprintf(istream,"%s",buffer);

    // closing the connected socket
    close(socQotd);
    fclose(istream);

    return 0;

}
