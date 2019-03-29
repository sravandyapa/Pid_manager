#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

int a[1000],a1[1000]={},b[1000]={};
sem_t s[1000];

void allocate();
void release();
void *f();

void menu()
{
	printf("\n\n\t\t\tWelcome to pid manager\n\n\n");
	printf("Enter\n 1. Allocate\n 2. Release\n 3. Exit\n Enter your choice : ");
}

int main()
{
	int i;
	for(i=0;i<1000;i++)
	{
		a[i]=i;
	}
	for(i=0;i>=0;i++)
	{
		int j,n,m;
		system("clear");
		menu();
		scanf("%d",&n);
		if(n==1)
		{
			allocate();
		}
		else if(n==2)
		{
			release();
		}
		else if(n==3)
		{
			printf("\n\n\t\t\tThank you see you again\n\n\n\n");
			break;
		}
	}

}

void allocate()
{
	int i,n,*m;
	printf("No of process you want to allocate\n");
	scanf("%d",&n);
	pthread_t t[n];
	for(i=0;i<n;i++)
	{
		m=&i;
		sem_init(&s[i],0,1);
		pthread_create(&t[i],NULL,f,m);
		pthread_join(t[i],NULL);
	}
}
void *f(int *i)
{
	int n=*i;
	sem_wait(&s[n]);
	b[n]=a[n];
	a1[n]=1;
	printf("thread %d  allocated\n",a[n]);
	sleep(1);
}
void release()
{
}
