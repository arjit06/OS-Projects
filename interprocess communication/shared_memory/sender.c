#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define SHM_SIZE 1024
#define BILLION  1000000000.0;

int main()
{
    key_t key;

    int length=6;

    printf("Sender process with pid %d\n", getpid());

	
	int shmid[51]; ///


     //generate 50 random strings of length 5 each
    int num, i;
    time_t t1;
    char c; //one character only
    char* arr[50];
    srand ( (unsigned) time (&t1)); //97 + 26
    char* word=(char*)malloc(6);
    for (int i=0;i<50;i++ )
    {
        arr[i]=(char*)malloc(6); 
        for(int i=0;i<5;i++)
        {
            c=rand()%26 +97;
            word[i]=c;
        }
        word[5]='\0';
        strcpy(arr[i],word);
    }


    int numid;
    key= ftok("shmfile",69); //generate a new key
    numid=shmget(key,SHM_SIZE,0666|IPC_CREAT); // shmget returns an identifier in numid
    char* shared_mem=(char*) shmat(numid,(void*)0,0); //creates shared string variable




    struct timespec start, stop;
    double time_taken;
    clock_gettime( CLOCK_REALTIME, &start); //start timer   

    int highest_id=0;

    //for(int i=0;i<51;i++)

    
    int id;
    for(int i=0;i<50;i=i+5)
    {  

        for(int j=i;j<i+5;j++) //send five strings at a time
        {
            
           // char c=j;
            //shared_mem[j*length]=c;
            
            sprintf(shared_mem+j*length, "%d %s", j, arr[j]);
            //strcpy(shared_mem+j*length+1,arr[j]);

        
        } 
        //strcpy(shared_mem+30,"w");
       // sprintf(shared_mem+30,'A');
        shared_mem[30]='A';
        while (shared_mem[30]=='A') //wait
        {
            sleep(1);
        }

        sscanf(shared_mem+30, "%d", &id);

        highest_id=id;
        printf("String with highest id is %d. Now sending next 5 strings\n",highest_id);

    }

    clock_gettime( CLOCK_REALTIME, &stop); //end timer

    float temp1=stop.tv_nsec;
    float temp2=start.tv_nsec;
    time_taken =( stop.tv_sec - start.tv_sec )    + (temp1-temp2)/BILLION;
    printf("Time taken by SHARED MEM: %lf\n",time_taken);
    

    shmdt(shared_mem);

    shmctl(numid,IPC_RMID,NULL);
	

	return 0;
}
