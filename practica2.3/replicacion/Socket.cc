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

	memset(&hints, 0, sizeof(struct addrinfo)); 

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int err = getaddrinfo(address, port, &hints, (const struct sockaddr *) &sa);

	if(err != 0){
		printf("Error en getaddrinfo \n");
	}

	sd = socket(sa->ai_family, sa->ai_socktype,0);

	if (sfd == -1){
		printf("Error en creacion del socket \n");
	}
}

// ----------------------------------------------------------------------------

int Socket::bind()
{
    return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
}

// ----------------------------------------------------------------------------

int Socket::send(Serializable * obj, Socket * sock)
{
	
}

// ----------------------------------------------------------------------------

int Socket::recv(char * buffer, Socket ** sock)
{
	//char buf [MAX_MESSAGE_SIZE];
	
	buffer->to_bin();

	if(sock != 0){
		int result =  socket(sa, sa_len,0);
	}

	if(result != 0)
		return -1;
	else return 0;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

