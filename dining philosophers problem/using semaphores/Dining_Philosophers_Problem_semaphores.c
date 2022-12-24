#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
//philosophers and forks numbered from 1 to 5

int forks[5]={0,0,0,0,0}; //fork i-1 is not used 
sem_t Sem[6]; //five semaphores for each fork used as a shared variable 
sem_t lock;
int value;

int fork_one(int n)
{
    int f;
    if (n<=4) f=n ;
    else f=4;
    return f;
}

int fork_two(int n)
{
    int f;
    
    if (n==1) f=5;
    else if (n!=5) f=n-1;
    else f=5;
    return f;
}



void pick_up_fork_one(int n)
{
    int f=fork_one(n);
    sem_wait(&Sem[f]); //prevents two processes from accessing the same fork simul. forces it too wait.
    sem_wait(&lock); //to make it an atomic operation
   

    sleep(1);
    printf("Philosopher %d picks up fork %d\n",n,f);
    if (forks[f]==1) printf("\nILLEGAL ACCESS !!!\n\n");
    forks[f]=1;
    sem_post(&lock);
}

void put_down_fork_one(int n) 
{
    sem_wait(&lock);
    int f=fork_one(n);

    sleep(1);
    printf("Philosopher %d puts down fork %d\n",n,f);
    forks[f]=0;
    sem_post(&lock);

    sem_post(&Sem[f]);  //notifies the other process that fork can now be picked up.
}

void pick_up_fork_two(int n)
{
    int f=fork_two(n);
    sem_wait(&Sem[f]);
    sem_wait(&lock);

     
    sleep(1);
    printf("Philosopher %d picks up fork %d\n",n,f);
    if (forks[f]==1) printf("\nILLEGAL ACCESS !!!\n\n");
    forks[f]=1;
    sem_post(&lock);
}

void put_down_fork_two(int n) 
{
    sem_wait(&lock);
    int f=fork_two(n);
   
    sleep(1);
    printf("Philosopher %d puts down fork %d\n",n,f);
    forks[f]=0;
    sem_post(&lock);

    sem_post(&Sem[f]);  //notifies the other process that fork can now be picked up.
}
 
void* philosopher_thread(void *arg)
{
    int* n =(int*)arg;
    int num=*n;
    while(1)
    {
        printf("Philosopher %d is thinking\n",num);
        sleep(2);
        printf("Philosopher %d is HUNGRY\n",num);
       

        
        pick_up_fork_one(num);

        pick_up_fork_two(num);

        sleep(1);
        printf("Philosopher %d is EATING\n",num);
        

        put_down_fork_one(num);
        put_down_fork_two(num);
    }
}



int main()
{
    pthread_t threads[5]; // a thread representing a philosopher
    int philosophers[5]={1,2,3,4,5};

    sem_init(&lock, 0, 1);
    

    for (int i = 1; i <= 5; i++)
    {
		sem_init(&Sem[i], 0, 1);
    }


    for(int i=0;i<=4;i++)
    {    
        pthread_create(&(threads[i]),NULL,&philosopher_thread,&philosophers[i]); 
    }

    for(int i=0;i<=4;i++)
    {
        pthread_join((threads[i]),NULL);
    }
}