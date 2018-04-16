#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
static int MIN_PID=300;
static int MAX_PID=5000,pno=1;
pthread_mutex_t mutex;
struct p_manager
{
int pid;
int b;
}t[4700];

void allocate_map()
{
int i,id=MIN_PID;
for(i=0;i<=4700;i++)
{
 t[i].pid=id++;
 t[i].b=0;
}
}
void release(int k,int p)
{int i;
for(i=0;i<=4700;i++)
{if(t[i].pid==k)
  {
  t[i].b=0;
  printf("\nReleased The Pid of process :%d ",p);
  break;
  }
}
}
int allocate()
{   int j;
    for(j=0;j<=4700;j++)
    {
        if(t[j].b==0)
        {
            t[j].b=1;
            return t[j].pid;
            break;
        }
    }

    return 0;
}
void *display_thread(void *n)
{
int i=*(int *)n;
int k,p;
k=allocate();
pthread_mutex_lock(&mutex);
p=pno;
sleep(5);
printf("\nProcess : %d || PID = %d \n",pno++,k);
pthread_mutex_unlock(&mutex);
sleep(5);
release(k,p);
}

int main()
{
int n,i;
allocate_map();
printf("Enter the number of process to start");
scanf("%d",&n);
pthread_t p[n];
for(i=0;i<n;i++)
{
 pthread_create(&p[i],NULL,display_thread,(void *)&n);
}
for(i=0;i<n;i++)
{pthread_join(p[i],NULL);
}
return 0; 
}
