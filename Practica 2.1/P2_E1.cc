#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string.h>

int main()
{
/* Comprobar la ocurrencia de error y notificarlo con la llamada perror(3) */      
    	int rc = setuid(0);	
  	
    	if(rc == -1){
		perror("setuid()");		
		printf("Error: %s\n", strerror(errno));		
	}
    	return 0;
}
