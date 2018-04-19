#include <time.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

int main (void)
{
   time_t tiempo;
   struct tm *ti_legible;
 
   //Getting current time of system
   tiempo = time (NULL);
 
   // Converting current time to local time
   ti_legible = localtime (&tiempo);
 
   // Displaying date and time in standard format
   printf("%s", asctime (ti_legible));

   char* buf= (char*) malloc(sizeof(char)*200);

   strftime (buf, 200, "Hoy es %A, %I:%M %p.\n", ti_legible);
   fputs (buf, stdout);   

  return 0;
}
