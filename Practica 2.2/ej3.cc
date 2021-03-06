#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <time.h>
#include <iostream>

#define SIZE 500

int main(int argc, char** argv)
{
	char buf[SIZE];

	struct addrinfo* result, *rp;
	struct addrinfo hints;
	int sfd, s, j; 
	char enviar[SIZE];
	size_t len;
	ssize_t nread;
	
	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
	hints.ai_family   = AF_UNSPEC; // IPv4
	hints.ai_socktype = SOCK_DGRAM;

	s = getaddrinfo(argv[1], argv[2], &hints, &result);

	if(s != 0){
		printf("Error en getaddrinfo \n");
	}

 	for (rp = result; rp != NULL; rp = rp->ai_next) {
     	sfd = socket(rp->ai_family, rp->ai_socktype,0);
          
	if (sfd == -1){
		printf("Error en creacion del socket. \n");
	}

          if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
              break;                  /* Success */

          close(sfd);
      }

	 if (rp == NULL) {              
      	fprintf(stderr, "Could not connect\n");
          exit(EXIT_FAILURE);
      }else
		fprintf(stderr, "Connection success\n");
	
	 freeaddrinfo(result); 
	while(1){
		 //El servidor espera el primer mensaje
		 printf("Escribir mensaje: ");
		 scanf("%*c%[^\n]",enviar);
		 send(sfd,enviar,SIZE,0);		 
 
		 //El cliente recibe el mensaje del servidor
		 recv(sfd,enviar,SIZE,0); //deberia ser recvfrom
		 
		 printf("Servidor: %s\n",buf);
	}
	 /*for (j = 3; j < argc; j++) 
	 {
      	len = strlen(argv[j]) + 1;
          // +1 for terminating null byte

          if (len + 1 > SIZE) 
		{
      	    fprintf(stderr,
              "Ignoring long message in argument %d\n", j);
              continue;
          }

          if (write(sfd, argv[j], len) != len) {
              fprintf(stderr, "partial/failed write\n");
              exit(EXIT_FAILURE);
          }

          nread = read(sfd, buf, SIZE);
          if (nread == -1) 
		{
              perror("read");
              exit(EXIT_FAILURE);
          }

            printf("Received %ld bytes: %s\n", (long) nread, buf);
       }*/

     exit(EXIT_SUCCESS);

}
