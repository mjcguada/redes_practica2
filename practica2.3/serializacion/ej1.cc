#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include<stdlib.h>

static const size_t MAX_NAME = 80;

class Jugador: public Serializable
{
public:
    Jugador(const char * _n, int16_t _x, int16_t _y):x(_x),y(_y)
    {
        strncpy(name, _n, MAX_NAME); //Copia en name		   
    };

    virtual ~Jugador(){};

    void to_bin()
    {
		int32_t total = MAX_NAME + 2*sizeof(int16_t);
		alloc_data(total);
		char* tmp = _data+ sizeof(int32_t);
		
		memcpy(tmp, name, sizeof(name));
		tmp+= MAX_NAME;

		memcpy(tmp, &x, sizeof(int16_t));		
		tmp += sizeof(int16_t);

		memcpy(tmp, &y, sizeof(int16_t));
		tmp += sizeof(int16_t);			
    }

    int from_bin(char * data)
    {	
		char* tmp = data + sizeof(int32_t);
		memcpy(name, tmp, MAX_NAME);
		tmp+= MAX_NAME;
		memcpy(&x, tmp, sizeof(int16_t));
		tmp += sizeof(int16_t);
		memcpy(&y, tmp, sizeof(int16_t));
		tmp += sizeof(int16_t);
		std::cout << name << ", " << x << ", "<< y << std::endl;
    }
	
private:
    char name[MAX_NAME];

    int16_t x;
    int16_t y;
    
};

int main(int argc, char **argv)
{
	srand(time(NULL));
	int uno = rand()%50;
	int dos = rand()%50;
	Jugador jugar("Juancho", uno, dos);
	Jugador jugar2("xxx", 0, 0);

	jugar.to_bin();

	int jugador;
	jugador = open("jugador.txt", O_RDWR);
	write(jugador, jugar.data(), jugar.size());
	close(jugador);

	jugar2.from_bin(jugar.data());
}
