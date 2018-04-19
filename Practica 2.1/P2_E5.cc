#include <time.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>

int main (void)
{
	timespec tiempo1;
	timespec tiempo2;
	long t1, t2;

	t1 = clock_gettime(2, &tiempo1);
	if (t1 != 0) {
		perror("Error variable 1");
	}
	for (int i = 0; i < 10000; i++) {

	}
	t2 = clock_gettime(2, &tiempo2);

	std::cout << "Tiempo: " << (long)pow(tiempo2.tv_sec,3) + tiempo2.tv_nsec << "(ns)" << std::endl;

	return 1;
}
