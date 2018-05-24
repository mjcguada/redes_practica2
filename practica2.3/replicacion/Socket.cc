#include "Socket.h"
#include "Serializable.h"

#include <string.h>


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Implementación Socket
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

bool operator== (const Socket &s1, const Socket &s2)
{
	if(s1->sd != s2->sd || s1->sa != s2->sa || s1->sa_len != s2->sa_len)
		return false;
	else return true;
}

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;
}

// ----------------------------------------------------------------------------

Socket::Socket(const char * address, const char * port):sd(-1)
{
	struct addrinfo hints;
	struct addrinfo aux;

	memset(&hints, 0, sizeof(struct addrinfo)); 

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	

	int err = getaddrinfo(address, port, &hints, (const struct sockaddr *) &aux);

	if(err != 0){
		printf("Error en getaddrinfo \n");
	}	
	
	sd = socket(aux->ai_family, aux->ai_socktype, 0);

	if (sfd == -1){
		printf("Error en creacion del socket \n");
	}

	//Pasamos los datos al socket en sí (nos faltaba esto)
	sa = aux->ai_addr;
	sa_len = aux->ai_addrlen;
}

// ----------------------------------------------------------------------------

int Socket::bind()
{
    return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
}

// ----------------------------------------------------------------------------

int Socket::send(Serializable * obj, Socket * sock)
{
	obj->to_bin();
	
	//No sé si hace falta el (void*)
	int result =  sendto(sock->sd, (void*)obj->_data, obj->_size, 0, &sock->sa,sock->sa_len);

	if(result != 0)
		return -1;
	else return 0;
}

// ----------------------------------------------------------------------------

int Socket::recv(char * buffer, Socket ** sock)
{
	//char buff [MAX_MESSAGE_SIZE];
	struct sockaddr sck_addr;
	socklen_t len = sizeof(sck_addr);
	//buffer->to_bin();

	if(sock != 0){
		//No sé si hace falta el (void*)
		int result =  recvfrom(sd, (void*)&buffer, MAX_MESSAGE_SIZE, 0, &sck_addr, &len);
		
		sock = new Socket(&src,port);		
	}

	if(result != 0)
		return -1;
	else return 0;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

