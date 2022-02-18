#include <time.h>
#include <stdio.h>
#include <string.h>

void code()
{
	for(int i = 0; i < 10000; i++)
	{
		printf(".");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	clock_t t;
	double totalTime;
	int iterations;
	sscanf (argv[1],"%d",&iterations);
	
	for(int i = 0; i < iterations; i++)
	{
		printf("start: %d \n", (int) (t=clock()));
	
		code();
	
		printf("stop: %d \n", (int) (t=clock()-t));
		printf("Elapsed: %f seconds\n", (double) t/ CLOCKS_PER_SEC);
		
		totalTime = totalTime + ((double) t/ CLOCKS_PER_SEC);
	}
	
	double average = totalTime / iterations;
	printf("The average run time: %f\n", average);
	
	return 0;
}