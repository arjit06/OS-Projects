#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
int max(int a ,int b){ return (a<b)?b:a;}
#define SHM_SIZE 1024
int main()
{

    printf("Receiver process with pid %d\n", getpid());
	key_t key;


    int length=6;

    int numid;
    key= ftok("shmfile",69); //generate a new key
    numid=shmget(key,SHM_SIZE,0666|IPC_CREAT); // shmget returns an identifier in numid
    char* shared_mem=(char*) shmat(numid,(void*)0,0); //creates shared string variable


    char copied[30];
    char temp[5];
    int id;
    int highest_id=0;

    for(int i=0;i<50;i=i+5)
    {  
        while (shared_mem[30]!='A'){sleep(1);}
        //strcpy(copied,shared_mem);

        for(int j=i;j<i+5;j++) //receive five strings at a time
        {
            sscanf(shared_mem+j*length, "%d %s", &id, temp);
            highest_id=max(highest_id, id);
           // printf("%d",copied[j*length]-'0');
            //strcpy(temp,copied+j*length+1);
            printf("Data read from memory: %s\n",temp);

        }
        sprintf(shared_mem+30,"%d",highest_id);
        //shared_mem[30]=highest_id;
        printf("\n");
    }


 
	//detach from shared memory

    shmdt(shared_mem);
    

	// destroy the shared memory
	return 0;
}
