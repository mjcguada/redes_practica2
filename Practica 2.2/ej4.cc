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

	struct addrinfo* rp;
	struct addrinfo hints;
	int sfd, j; 
	ssize_t s;
	bool conexion = true;
		
	memset(&hints, 0, sizeof(struct addrinfo)); 

	hints.ai_family = AF_INET;
	//hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int err = getaddrinfo(argv[1], argv[2], &hints, &rp);

	if(err != 0){
		printf("Error en getaddrinfo \n");
	}


	char host[NI_MAXHOST], serv[NI_MAXSERV];

	getnameinfo (rp->ai_addr, rp->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
	
	sfd = socket(rp->ai_family, rp->ai_socktype,0);
          
	if (sfd == -1){
		printf("Error en creacion del socket \n");
	}
	
	if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == -1){
		printf("Error en bind \n");
	}	
	
	listen(sfd,15);
	
	while(true){
		
		struct sockaddr cresult;
		socklen_t cliente_len = sizeof(cresult);
		
		j = accept(sfd, &cresult, &cliente_len);
		
		//Mientras exista conexion con server
		while(conexion){
			s = recv(j, &buf, 255, 0);
			
			if(s == 0){ 
				conexion = false;
			}
			else{
				getnameinfo(&cresult, cliente_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
				printf("Conexión desde Host:%s Puerto:%s\n",host, serv);
				//Mandamos el mensaje
				send(j,&buf, s, 0);
			}
		}
	}

	freeaddrinfo(rp);


	return 0;
}
