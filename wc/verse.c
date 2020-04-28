#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define BUF_SIZE 256
struct timespec begin, end;

int main(void)
{
	
	char buf[256] = "hello world\n";

	clock_gettime(CLOCK_MONOTONIC,&begin);
	
	for(int i=0;i<1000;i++)
		printf("%s",buf);

	clock_gettime(CLOCK_MONOTONIC,&end);

		printf("\n\n\n\n\n");
		printf("printf : %lf\n",(end.tv_sec - begin.tv_sec) + 
			     (end.tv_nsec - begin.tv_nsec) / 1000000000.0 );
		
	clock_gettime(CLOCK_MONOTONIC, &begin);
	
	write(1,"\n\n\n\n",sizeof("\n\n\n\n"));
	
	for(int i=0;i<1000;i++)
		write(1,buf,sizeof(buf));
	clock_gettime(CLOCK_MONOTONIC, &end);

		
		printf("write : %lf\n",(end.tv_sec - begin.tv_sec) + 
			     (end.tv_nsec - begin.tv_nsec) / 1000000000.0 );
}
