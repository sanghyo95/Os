#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#define BUF_SIZE 256
int money=0;
int flag[2] = { 0, 0 };
int turn = 0;
void income(void);
void outlay(void);
void enter_region(int process);
void leave_region(int process);


int main(void)
{


	int number;
	// 옵션 고르기 
	while (number != 4) {
		printf("-------------------------     나만의 가계부    ------------------------------ \n\n\n");		
		printf("[1]지출 입력              [2]소득 입력           [3]차액 계산          [4]종료\n\n\n");
		printf("옵션 선택 >>>> ");
		scanf("%d", &number);


		int fd, n, count;
		char buf[BUF_SIZE];
		//1번 지출 선택 
		if (number == 1) {
			int first_pid = fork();
			if (first_pid == 0) {
				// 지출 내역에 대한 파일 만들기 , 읽기쓰기, 파일이 이미 존재한다면-1  리턴
				fd = open("outlay.txt", O_RDWR | O_CREAT | O_EXCL, 0777);
				// 이미 파일이 있을 경우에 파일 열기
				if (fd == -1)
					fd = open("outlay.txt", O_RDWR);

				printf("입력 할 지출 내역 개수 : ");
				scanf("%d", &count);	
				printf("\n\n\n");
				// 지출 개수만큼만 입력할수 있음

				write(1,"-----입력방식 >>> 전자제품 200000\n\n\n",sizeof("-----입력방식 >>> 전자제품 200000\n\n\n"));
				while (count > 0) {
					write(1, "지출 내역 : ", sizeof("지출 내역 : "));
					//파일 읽어온후 , 입력한 내용 맨뒤에 삽입하고, 파일의 내용 출력
					n = read(0, buf, BUF_SIZE);
					lseek(fd, 0, SEEK_END);
					n = write(fd, buf, n);
					lseek(fd, 0, SEEK_SET);
					n = read(fd, buf, BUF_SIZE);
					n = write(1, buf, n);
					write(1,"\n\n",sizeof("\n\n"));
					count--;
				}
				close(fd);
				return 0;
			}
			else {
				wait(&first_pid);
				printf("[1] 지출 내역 입력 종료\n\n\n");
			}

		}
		//2번 수입 선택
		else if (number == 2) {
			int second_pid = fork();
			if (second_pid == 0) {
				// 소득 내역에 대한 파일 만들기, 읽기쓰기용, 파일 이미 존재한다면 -1 리턴 
				fd = open("income.txt", O_RDWR | O_CREAT | O_EXCL, 0777);
				// 이미 파일 있는 경우 파일 열기
				if (fd == -1)
					fd = open("income.txt", O_RDWR);

				printf("입력할 소득 내역  개수: ");
				scanf("%d", &count);
				printf("\n\n\n");
				//소득 내역 입력한 개수만 입력
				
				write(1,"-----입력방식 >>> 생활비 200000\n\n\n",sizeof("-----입력방식 >>> 생활비 200000\n\n\n"));
				while (count > 0) {
					write(1, "소득 내역 : ", sizeof("소득 내역 : "));
					//파일 읽어온후 , 입력한 내용 맨뒤에 삽입하고, 파일의 내용 출력	
					n = read(0, buf, BUF_SIZE);
					lseek(fd, 0, SEEK_END);
					n = write(fd, buf, n);
					lseek(fd, 0, SEEK_SET);
					n = read(fd, buf, BUF_SIZE);
					n = write(1, buf, n);
					write(1,"\n\n",sizeof("\n\n"));
					count--;
				}
				close(fd);
				return 0;
			}
			else {
				wait(&second_pid);
				printf("[2] 소득 내역 입력 종료 \n\n\n");
			}
		}
		else if (number == 3) {
			pthread_t id;
			pthread_t id2;
			int thr_id;
			int thr_id2;
			void* tret;


			thr_id = pthread_create(&id, NULL, outlay, NULL);
			thr_id2 = pthread_create(&id2, NULL, income, NULL);
			if (thr_id < 0)
			{
				perror("thread create error : ");
				exit(0);
			}
			if (thr_id2 < 0)
			{
				perror("thread2 create error : ");
				exit(0);
			}

			pthread_join(id, NULL);
			pthread_join(id2, NULL);

			printf("소득,지출의 차액 : %d\n\n\n",money);
			

		}
		// 두번 이상 확인 할 때를 위해 값 초기화 
		money = 0;	
	}


}

void income(void)
{
	FILE* fp = fopen("income.txt", "r");
	char buf[10000];
	int i = 0;
	char buf2[20];
	if(fp == NULL)
	{
		perror("소득 내역이 없습니다");
		exit(0);
	}
	enter_region(0);
	while (!feof(fp)) {
		//버퍼에 한라인 입력 받기
		fgets(buf, sizeof(buf), fp);
		char* ptr = strtok(buf, " ");

		// 단어 하나하나 접근		
		while (ptr != NULL) {
		
			// 문자열을 숫자만 money 변수에 저장하기 
			strcpy(buf2, ptr);
			money += atoi(buf2);
			ptr = strtok(NULL, " ");
		}

	}
	
	// while 문이 한번더 실행 되어 반대로 한번 더해주기 
	money -= atoi(buf2);
	leave_region(0);
	fclose(fp);
	
}
void outlay(void)
{
	FILE* fp = fopen("outlay.txt", "r");
	char buf[10000];
	int i = 0;
	char buf2[20];
	if(fp == NULL)
	{
		perror("지출 내역이 없습니다");
		exit(0);
	}
	enter_region(1);
	while (!feof(fp)) {
		//버퍼에 한라인 입력 받기
		fgets(buf, sizeof(buf), fp);
		char* ptr = strtok(buf, " ");
		// 단어 하나하나 접근		
		while (ptr != NULL) {
			
			// 문자열을 숫자만 money 변수에 저장하기 
			strcpy(buf2, ptr);
			money += -(atoi(buf2));
			ptr = strtok(NULL, " ");
		}

	}
	// while 문이 한번더 실행 되어 반대로 한번 더해주기 
	money += atoi(buf2);
	leave_region(1);

	fclose(fp);
	
}
void enter_region(int process)
{
	int other = 1 - process;

	flag[process] = 1;
	turn = 1 - process;
	while((turn == 1 - process) && (flag[other] == 1)) {} 
}
void leave_region(int process)
{
	flag[process] = 0;
}


