#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 256
	int main()
	{
	
		int fd,n;
		char buf[BUF_SIZE];
	
			fd = open("name.txt",O_RDWR|O_CREAT|O_EXCL,0777);
		if( fd == -1) 
			fd =open("name.txt",O_RDWR);
	
			
			
		
		write(1,"이름 입력 : ",sizeof("이름 입력 : "));

		n= read(0,buf,BUF_SIZE);

		lseek(fd,0,SEEK_END);

		n = write(fd,buf,n);

		lseek(fd,0,SEEK_SET);
		
		n=read(fd,buf,BUF_SIZE);

		n=write(1,buf,n);

		close(fd);
	}
