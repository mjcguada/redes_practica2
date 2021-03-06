#include <string>
#include <unistd.h>
#include <string.h>
#include "Serializable.h"
#include "Socket.h"
#include "UDPServer.h"

const int MAX_NAME = 80;
const int MAX_MESSAGE = 80;
class ChatMessage: public Serializable
{
public:
    ChatMessage(){};

    ChatMessage(const char * n, const std::string m)
    {
	 strncpy(nick, n, MAX_NAME);	   
	 strncpy(message, m, MAX_MESSAGE); 
    };

    void to_bin()
    {
		int32_t total = MAX_NAME + 2*sizeof(int16_t);
		alloc_data(total);
		char* tmp = _data+ sizeof(int32_t);
		
		memcpy(tmp, nick, sizeof(nick));
		tmp+= MAX_NAME;

		memcpy(tmp, message, sizeof(message));
		tmp+= MAX_MESSAGE;
		
    }

    virtual int from_bin(char * bobj)
    {
		char* tmp = bobj + sizeof(int32_t);
		memcpy(nick, tmp, MAX_NAME);
		tmp+= MAX_NAME;
		memcpy(message, tmp, MAX_MESSAGE);
		tmp+= MAX_MESSAGE;
		//std::cout << name << ", " << x << ", "<< y << std::endl;
    }

    char message[80];

    char nick[8];
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

class ChatServer : public UDPServer
{
public:
    ChatServer(const char * s, const char * p): UDPServer(s, p){};

    void do_message(char * buffer)
    {
		ChatMessage* newMessage = new ChatMessage();
		newMessage->from_bin(buffer);
    }
};

class ChatClient
{
public:
    ChatClient(const char * s, const char * p, const char * n):socket(s, p),
        nick(n){};

    void input_thread()
    {
		while(true){
			std::cin >> buf;
			ChatServer::do_message(buf);
		}
    }

    void net_thread()
    {
		while(true){
			UDPServer::server_thread();
		}
    }

private:
    char nick[8];
    char buf [MAX_MESSAGE];
    Socket socket;
};

