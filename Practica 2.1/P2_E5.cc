#include <time.h>
#include <stdio.h>
#include <iostream>

int main (void)
{
   	time_t tiempo;
   	struct tm *ti_legible;
 
   	//Getting current time of system
   	tiempo = time (NULL); 
	int cosa = 0;
	for(int i = 0; i < 10000; i++)	
		cosa++;	

  return 0;
}
