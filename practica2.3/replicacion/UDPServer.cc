#include "UDPServer.h"
#include "Serializable.h"

UDPServer::UDPServer(const char * serv, const char * port)
    :socket(serv, port)
{
    pthread_mutex_init(&mutex, 0);
};

UDPServer::~UDPServer()
{
    pthread_mutex_destroy(&mutex);
};

// ----------------------------------------------------------------------------

extern "C" void * _server_thread(void *arg)
{
    UDPServer * server = static_cast<UDPServer *>(arg);

    server->server_thread();

    return 0;
}

// ----------------------------------------------------------------------------

int UDPServer::start()
{
	//Creamos los threads que gestionarán los mensajes 
	pthread_t pThreads[THREAD_POOL_SIZE];
	
	for(int i = 0; i < THREAD_POOL_SIZE; i++){

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		int newThread = pthread_create(&pThreads[i], &attr, _server_thread, static_cast<void*>(this));

		if(newThread != 0){		
			printf("ERROR: Thread no creado \n");
			return -1;
		}

	}

	return 0;
}

// ----------------------------------------------------------------------------

void UDPServer::server_thread()
{
	while(true){

		char* buff;
		struct sockaddr sock;
		//socklen_t tam = sizeof(sock);

		Socket* newSocket;
		socket.recv(buff,&newSocket);
		add_connection(newSocket);
		do_message(buff);
	}
}

// ----------------------------------------------------------------------------

void UDPServer::add_connection (Socket * s)
{
	//BLOQUEO
	pthread_mutex_lock(&mutex);

	bool found = false;

	for(Socket* aux : connections){

		if(s == aux){
			//Si existe la borramos
			found = true;
			delete s; 
		}

	}

	if(!found && connections.size() < THREAD_POOL_SIZE)
		connections.push_back(s);
	
	//DESBLOQUEO
	pthread_mutex_unlock(&mutex);
}

// ----------------------------------------------------------------------------

void UDPServer::del_connection (Socket * s)
{
	pthread_mutex_lock(&mutex);

	bool found = false;
	
	//Necesitamos este iterador para avanzar por la lista de conexiones
	std::vector<Socket *>::iterator iterador = connections.begin();

	//Buscamos la conexión a quitar hasta llegar al final
	while (!found && iterador != connections.end()){
		
		if(iterador == s){
			found = true;
			connections.erase(iterador);
		}
	}
	
	//Si no existe la conexión, borramos el socket
	if(!found)
		delete s;

	pthread_mutex_unlock(&mutex);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

