#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	char buf[256];

	struct addrinfo* result, *cliente;
	struct addrinfo hints;
	int sfd, s, bytes;

	
	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
	hints.ai_family   = AF_UNSPEC; // IPv4
	hints.ai_socktype = SOCK_DGRAM;



	s = getaddrinfo(argv[1], argv[2], &hints, &result);

	if(s != 0){
		printf("Error en getaddrinfo \n");
	}
	sfd = socket(result->ai_family, result->ai_socktype, 0);
	

	int e = bind(sfd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

	if(e != 0){
		printf("Error bind \n");
	}

	while(true){
		char host[NI_MAXHOST], serv[NI_MAXSERV];
		struct sockaddr cresult;
		socklen_t cliente_len = sizeof(cresult);

		bytes = recvfrom(sfd, buf, 256, 0, &cresult, &cliente_len);
	  	buf[bytes]='\0'; 
	    
	  	e = getnameinfo(&cresult, cliente_len, host, NI_MAXHOST,
		 serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
	
	if(e != 0){
		printf("Error en getnameinfo \n");
	}
	  printf("Conexión desde Host:%s Puerto:%s\n",host, serv);
	  printf("\tMensaje(%i): %s\n", bytes, buf);

	  sendto(sfd, buf, bytes, 0, (struct sockaddr *) &result, cliente_len);

	}

}
