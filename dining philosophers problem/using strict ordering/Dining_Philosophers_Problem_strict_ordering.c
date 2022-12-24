#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//philosophers and forks numbered from 1 to 5

int forks[6]={0,0,0,0,0,0}; //fork i (1<=i<=5) is not used 

char* state[5];
    

int value;

int fork_one(int n)
{
    int f;
    f=n;
    return f;
}

int fork_two(int n)
{
    int f;
    if (n==1) f=5;
    else f=n-1;
    return f;
}

int get_adj_one(int num)
{
    return (num+1)%5;

}

int get_adj_two(int num)
{
    if (num==1) return 5;
    return num-1;

}


void pick_up_fork_one(int n) //left for philosophers 1 to 4 but right for philosopher 5
{
    
    int f=fork_one(n);
    int adj1=get_adj_one(n);
    int adj2=get_adj_two(n);
    sleep(1);
    printf("Philosopher %d picks up fork %d\n",n,f);
           
}

void put_down_fork_one(int n) 
{
    int f=fork_one(n);
    sleep(1);
    printf("Philosopher %d puts down fork %d\n",n,f);
}

void pick_up_fork_two(int n) //right for philosophers 1 to 4 but left for philosopher 5
{
    int f=fork_two(n);
    int adj1=get_adj_one(n);
    int adj2=get_adj_two(n);
    sleep(1);
    printf("Philosopher %d picks up fork %d\n",n,f);
}

void put_down_fork_two(int n) 
{
    int f=fork_two(n); 
    sleep(1);
    printf("Philosopher %d puts down fork %d\n",n,f);
}

 
void* philosopher_thread(void *arg)
{
    int* n =(int*)arg;
    int num=*n;
    sleep(1);
    printf("Philosopher %d is thinking\n",num);
    sleep(1);
    printf("Philosopher %d is HUNGRY\n",num);
    
    

    
    pick_up_fork_one(num);
    

    pick_up_fork_two(num);

    sleep(1);
    printf("Philosopher %d is EATING\n",num);
    

    put_down_fork_one(num);
    put_down_fork_two(num);
    

    
}



int main()
{
    int philosophers[5]={1,2,3,4,5};
    pthread_t threads[6]; // a thread representing a philosopher
    for(int i=0;i<6;i++)
    {
        state[i]=(char*)malloc(9);
        strcpy(state[i],"THINKING");
    }

    int phil1=0;
    int phil2=2;

    while(1)
    {
        pthread_create(&(threads[philosophers[phil1]]),NULL,&philosopher_thread,&(philosophers[phil1])); 
        pthread_create(&(threads[philosophers[phil2]]),NULL,&philosopher_thread,&(philosophers[phil2])); 
        pthread_join((threads[philosophers[phil1]]),NULL);
        pthread_join((threads[philosophers[phil2]]),NULL);
        phil1=(phil1+1)%5;
        phil2=(phil2+1)%5;

    }

    // for(int i=0;i<=4;i++)
    // {    
    //     pthread_create(&(threads[i]),NULL,&philosopher_thread,&philosophers[i]); 
    // }

    // for(int i=0;i<=4;i++)
    // {
    //     pthread_join((threads[i]),NULL);
    // }
}