#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	int first_pid = fork();
	if(first_pid ==0 ) {
		for(int i=0;i<100000;i++)
		printf("A");
		printf("\n");
		return 0;
	}

	int second_pid = fork();
	if(second_pid == 0 ){
		
		for(int i=0;i<100000;i++)
		printf("B");

		printf("\n");
		return 0;
		}
		
	else {
		for(int i=0;i<100000;i++)
		printf("p");

		printf("\n");
		return 0;
	}
		printf("\n");
		return 0;



}
