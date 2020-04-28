#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


	int main(void){
	
	int pid_1 = fork();
	if( pid_1 == 0 ) 
	{
		for(int i=0;i<100000;i++)
			printf("A");
	
		return 0;
	}
	int pid_2 = fork();
	if(pid_2 == 0 )
	{
		for(int i=0;i<100000;i++)
			printf("B");
		
		return 0;
	}
	else 
	{	
		wait(&pid_1);
		wait(&pid_2);
		printf("My children have gone");
	
	}
}
