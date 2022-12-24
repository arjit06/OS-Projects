#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sched.h>
#include <time.h>

#define BILLION  1000000000.0;
//no.of columns*curr_row + curr_column
void* countA(void* arg)
{
    FILE* filepointer;
    filepointer = fopen("data.txt", "a") ;

    nice(-2);
    // struct sched_param param;
    // param.sched_priority=0;
    // int retval=pthread_setschedparam(pthread_self(),SCHED_OTHER,&param);

    struct timespec start, stop;
    double time_taken;
    clock_gettime( CLOCK_REALTIME, &start);
    for(long long int i=1;i<=pow(2,32);i++){}
    clock_gettime( CLOCK_REALTIME, &stop);
    float temp1=stop.tv_nsec;
    float temp2=start.tv_nsec;
    time_taken =( stop.tv_sec - start.tv_sec )    + (temp1-temp2)/BILLION;

    fprintf(filepointer,"Thread1: %f\n",time_taken);
    fclose(filepointer);
    printf("Thread1: %lf\n",time_taken);
}

void* countB(void* arg)
{
    FILE* filepointer;
    filepointer = fopen("data.txt", "a") ;

    int * priority=(int*)arg;
    struct sched_param param;
    param.sched_priority=*priority;
    int retval=pthread_setschedparam(pthread_self(),SCHED_RR,&param);

    struct timespec start, stop;
    double time_taken;
    clock_gettime( CLOCK_REALTIME, &start);
    for(long long int i=1;i<=pow(2,32);i++){}
    clock_gettime( CLOCK_REALTIME, &stop);
    float temp1=stop.tv_nsec;
    float temp2=start.tv_nsec;
    time_taken =( stop.tv_sec - start.tv_sec )    + (temp1-temp2)/BILLION;
    fprintf(filepointer,"Thread2: %f\n",time_taken);
    fclose(filepointer);
    printf("Thread2: %f\n",time_taken);

}

void* countC(void* arg)
{
    FILE* filepointer;
    filepointer = fopen("data.txt", "a") ;

    int* priority=(int*)arg;
    struct sched_param param;
    param.sched_priority=*priority;
    int retval=pthread_setschedparam(pthread_self(),SCHED_FIFO,&param);

    struct timespec start, stop;
    double time_taken;
    clock_gettime( CLOCK_REALTIME, &start);
    for(long long int i=1;i<=pow(2,32);i++){}
    clock_gettime( CLOCK_REALTIME, &stop);
    float temp1=stop.tv_nsec;
    float temp2=start.tv_nsec;
    time_taken =( stop.tv_sec - start.tv_sec )    + (temp1-temp2)/BILLION;
    fprintf(filepointer,"Thread3: %f\n",time_taken);
    fclose(filepointer);
    printf("Thread3: %f\n",time_taken);

}

int main()
{
    struct sched_param param;
    param.sched_priority=0;
    nice(18); //now nice value is 18
    
    int retval;

    clock_t t;
    pthread_t Thr_A,Thr_B,Thr_C; 

    // param.sched_priority=0;
    // retval=pthread_setschedparam(pthread_self(),SCHED_OTHER,&param);

    int j=1;

    FILE* filepointer;
    filepointer = fopen("data.txt", "w");
    fclose(filepointer);
    
    for(int i=5;i<100;i=i+10)
    {
        // param.sched_priority=0;
        // retval=pthread_setschedparam(pthread_self(),SCHED_OTHER,&param);
        filepointer = fopen("data.txt", "a");
        fprintf(filepointer,"Reading %d\n",j);
        fclose(filepointer);
        printf("Reading %d\n",j);
        pthread_create(&Thr_A,NULL,&countA,NULL);

        // param.sched_priority=i;
        // retval=pthread_setschedparam(pthread_self(),SCHED_RR,&param);

        pthread_create(&Thr_B,NULL,&countB,&i);

        // param.sched_priority=i;
        // retval=pthread_setschedparam(pthread_self(),SCHED_FIFO,&param);
        pthread_create(&Thr_C,NULL,&countC,&i);
        pthread_join(Thr_A,NULL);
        pthread_join(Thr_B,NULL);
        pthread_join(Thr_C,NULL);
        printf("\n");
        filepointer = fopen("data.txt", "a");
        fprintf(filepointer,"\n");
        fclose(filepointer);
        j++;
    }
   

}
