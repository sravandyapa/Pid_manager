
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

void clear()
{
	system("clear");
	printf("\n\n\t\t\tWelcome to pid manager\n\n\n");
}

int a[1000],a1[1000]={},b[1000]={};
sem_t s[1000];

void allocate();
void release();
void *f();

void menu()
{
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
		clear();
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
			system("clear");
			printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\tThank you see you again\n\n\n\n");
			sleep(2);
			system("clear");
			break;
		}
		else
		{
			printf("Enter valid choice\n");
			printf("\n\n\nPress any Number ");
			scanf("%d",&j);
		}
	}

}

void allocate()
{
	int i,j,n,*m,y;
	for(j=0;j>=0;j++)
	{
		clear();
		printf("\n\n\nEnter\n 1. Allocate many process\n 2. Allocate single process\n 3. Available and Busy Pid's\n 4. Exit\n Enter your choice : ");
		scanf("%d",&y);
		if(y==1)
		{
			clear();
			printf("\n\n\nNo of process you want to allocate to pid's : ");
			scanf("%d",&n);
			pthread_t t[n];
			if(n>=0&&n<1000)
			{
					for(i=0;i<n;i++)
					{
						if(a1[i]==0)
						{
							m=&i;
							sem_init(&s[i],0,1);
							pthread_create(&t[i],NULL,f,m);
							pthread_join(t[i],NULL);
						}
						else
						{
							printf("\nPid %d  is currently busy try another pid`s",i);
							sleep(1);
						}
					}
			}
			else
			printf("\n\n\nPid does not Exist");
			printf("\n\n\n\nPress any Number "); 
			scanf("%d",&i); 

		}
		else if(y==2)
		{
			clear();
			printf("\n\n\nEnter the pid number(less than 1000) you want to allocate : ");
			scanf("%d",&n);
			if(n>=0&&n<1000)
			{
				if(a1[n]==1)
				{
					printf("\n\n\nPid is currently busy try another pid`s\n");
				}
				else
				{
					pthread_t t;
					m=&n;
					sem_init(&s[n],0,1);
					pthread_create(&t,NULL,f,m);
					pthread_join(t,NULL);
				}
			}
			else
			printf("\n\n\nPid does not Exist");
			printf("\n\n\n\nPress any Number "); 
			scanf("%d",&i); 

		}
		else if(y==3)
		{
			int i;
			printf("\n\nAvailable Pids's are : ");
			for(i=0;i<1000;i++)
			{
				if(a1[i]==0)
				{
					printf("%d ",i);
				}
			}
			printf("\n\nBusy Pids's are : ");
			for(i=0;i<1000;i++)
			{
				if(a1[i]==1)
				{
					printf("%d ",i);
				}
			}
			printf("\n\n\nPress any Number ");
			scanf("%d",&i);
		}
		else if(y==4)
		{
			break;
		}
		else
		{
			int i;
			printf("Enter valid choice\n");
			printf("\n\n\nPress any Number ");
			scanf("%d",&i);
		}
	}
}
void *f(int *i)
{
	int n=*i;
	sem_wait(&s[n]);
	b[n]=a[n];
	a1[n]=1;
	printf("Process %d  allocated and pid no %d\n",a[n],a[n]);
	sleep(1);
}
void release()
{
	int i,j,n;
	for(j=0;j>=0;j++)
	{
		clear();
		printf("\n\n\nEnter\n 1. Release all process\n 2. Release single process\n 3. Exit\n Enter your choice : ");
		scanf("%d",&n);
		if(n==1)
		{
			clear();
			for(i=0;i<1000;i++)
			{
				if(a1[i]==1)
				{
					sem_post(&s[i]);
					printf("Process %d released and pid also\n",i);
					a1[i]=0;
					sleep(1);
				}
			}
			printf("\n\n\nPress any Number");
			scanf("%d",&i);
		}
		else if(n==2)
		{
			clear();
			printf("\n\n\nEnter pid no to get released : ");
			scanf("%d",&i);
			if(a1[i]==1)
			{
				sem_post(&s[i]);
				printf("Process %d released and pid also\n",i);
				a1[i]=0;
				sleep(1);
			}
			else
			{
				printf("Pid is not allocated so you cannot release it");
			}
			printf("\n\n\nPress any Number ");
			scanf("%d",&i);
		}
		else if(n==3)
		{
			break;
		}
		else
		{
			printf("Enter valid choice\n");
			printf("\n\n\nPress any Number ");
			scanf("%d",&i);
		}
	}
}
