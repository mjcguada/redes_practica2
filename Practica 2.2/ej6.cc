#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <time.h>
#include <iostream>
#include <pthread.h>

#define SIZE 256

class Thread
{

protected:

	struct addrinfo* result, *cliente;
	struct addrinfo hints;
	int sfd, s, bytes, maxThreads;

public:
	Thread(int soc){
		sfd = soc;	
	};
	virtual~Thread(){};
	
	void create_thread(){
		
		while (true){

			char buf[256];

			char host[NI_MAXHOST], serv[NI_MAXSERV];
			struct sockaddr cresult;
			socklen_t cliente_len = sizeof(cresult);

			bytes = recvfrom(sfd, buf, 256, 0, &cresult, &cliente_len);
		  	buf[bytes]='\0'; 

			int e = getnameinfo(&cresult, cliente_len, host, NI_MAXHOST,
			serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
			
			//Necesario para la fecha
			char buffer[SIZE];
			time_t curtime;
			struct tm *loctime;

			// Get the current time. 
			curtime = time (NULL);

			// Convert it to local time representation. 
			loctime = localtime (&curtime);
			///////////////////////////////

			if(e != 0)
			printf("Error en getnameinfo \n");
			else if(buf[0] == 't') //La hora
			{			  
				 strftime (buffer, SIZE, "The time is %I:%M %p.\n", loctime);
				 fputs (buffer, stdout);				
			}
			else if(buf[0] == 'f')
			{
				strftime (buffer, SIZE, "Today is %A, %B %d.\n", loctime);
			  	fputs (buffer, stdout);
			}
			else if(buf[0] == 'q'){
				//close(sockaddr);		
				break;	
			}
			else
			{
		  		printf("Conexión desde Host:%s Puerto:%s\n",host, serv);
		  		printf("\tMensaje(%i): %s\n", bytes, buf);
			}
			
			//sendto(sfd, buf, bytes, 0, (struct sockaddr *) &result, cliente_len);
	  	}
	};


	
};

int main(int argc, char** argv)
{
	char buf[256];
	char host[NI_MAXHOST], serv[NI_MAXSERV];

	struct addrinfo* result, *cliente;
	struct addrinfo hints;
	int sfd, s, bytes, maxThreads;
	
	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
	hints.ai_family   = AF_UNSPEC; // IPv4
	hints.ai_socktype = SOCK_DGRAM;
	
	maxThreads = 20;

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

		for (int i = 0; i < maxThreads; i++){

			Thread * newThread = new Thread(sfd);

			pthread_attr_t attr_t;

			pthread_attr_init(&attr_t);

			//pthread_create(&tid, &attr_t, , static_cast<void*>(newThread));
		}
	
	  	//sendto(sfd, buf, bytes, 0, (struct sockaddr *) &result, cliente_len);
		
	}
};
