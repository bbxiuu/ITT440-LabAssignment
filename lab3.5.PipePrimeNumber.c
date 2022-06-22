#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

int childTask(){

int numberEntered;

printf("\nPlease enter a number : ");
scanf("%d", &numberEntered);
return numberEntered;
}

int main(void) {

  int fd[2];
  pipe(fd);
  pid_t pid = fork();
  void sigint_handler(int sig);

  if(signal(SIGINT, sigint_handler) == SIG_ERR){
     perror("signal");
     exit(1);
    }


  if(pid > 0) {
    wait(NULL);
    close(0);
    close(fd[1]);
    dup(fd[0]);

    int i;
    int number = 0;
    read(fd[0], &number, sizeof(number));

    if (number == 0 || number == 1)
       { printf("\n%d is not a prime number\n",number); }

   for (i = 2; i <= number / 2; ++i) {

        // if n is divisible by i, then n is not prime
         if (number % i == 0) {
             printf("\n%d is not a prime number\n",number);
             break;
             }
         else
             { printf("\n%d is a prime number\n",number);
               break;
             }
                                }


                 }

   else if(pid == 0) {
    dup(fd[1]);

    int numberEntered = childTask();
    write(fd[1], &numberEntered, sizeof(numberEntered));
    close(fd[0]);
    close(1);

    exit(EXIT_SUCCESS);
  }



return EXIT_SUCCESS;
}


void sigint_handler(int sig){
  printf("Jangan Kacau Saya!\n");
                            }
