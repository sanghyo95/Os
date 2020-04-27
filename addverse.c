#include <stdio.h>
#include <time.h>
struct timespec begin,end;
int add(int a,int b)
{
return a + b; 
}


int main(void)
{

	int num1, num2, sum;
	
	num1 = 5;	
	num2 = 10;
	clock_gettime(CLOCK_MONOTONIC,&begin);


	for(int i=0;i<1000000;i++)	
	sum = num1 + num2;

	clock_gettime(CLOCK_MONOTONIC,&end);

	printf("unuse function : %lf\n",(end.tv_sec - begin.tv_sec) +
     				(end.tv_nsec - begin.tv_nsec) / 1000000000.0 );
	
	clock_gettime(CLOCK_MONOTONIC,&begin);
	for(int i=0;i<1000000;i++)
	sum = add(num1,num2);

	clock_gettime(CLOCK_MONOTONIC,&end);
	
	printf("use function : %lf\n",(end.tv_sec - begin.tv_sec) +
    			       (end.tv_nsec - begin.tv_nsec) / 1000000000.0 );


	printf("sum =%d\n",sum);
}
