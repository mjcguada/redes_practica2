#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#include <iostream>

#define SIZE 256




int main(int argc, char* argv[]){

	char buf[SIZE];

	struct addrinfo* rp, *result;
	struct addrinfo hints;
	int sfd;
	ssize_t s;
	bool conexion = true;
		
	memset(&hints, 0, sizeof(struct addrinfo)); 
	memset(buf, 0, SIZE); 

	hints.ai_family = AF_INET;
	//hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0; 
	
	int err = getaddrinfo(argv[1], argv[2], &hints, &rp);

	if(err != 0){
		printf("Error en getaddrinfo \n");
	}


	//char host[NI_MAXHOST], serv[NI_MAXSERV];

	//getnameinfo (rp->ai_addr, rp->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
	
	for (rp = result; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (sfd == -1)
                   continue;

               if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
                   break;                  /* Success */

               close(sfd);
           }


	/*
	if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == -1){
		printf("Error en bind \n");
	}	
	
	listen(sfd,15);
	*/
	
	while(true){
		
		struct sockaddr cresult;
		socklen_t cliente_len = sizeof(cresult);
		
		//j = accept(sfd, &cresult, &cliente_len);
		std::cin>>buf;

		if(buf[0] == 'q'){
			close(sfd);
			return 0;
		}
		
		send(sfd,&buf, SIZE, 0);
		
		s = recv(sfd, &buf, 255, 0);
			
		printf("Instruccion: %s \n", buf);

		
	}

	freeaddrinfo(rp);


	return 0;
}
