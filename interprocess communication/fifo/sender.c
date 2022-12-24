#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BILLION  1000000000.0;


int main()
{
    printf("Sender process with pid %d\n", getpid());

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
    // for(int i=0;i<50;i++)
    // {
    //     printf("%s ",arr[i]);
    // }
    // printf("\n");
    // printf("\n");



    /*Create a fifo*/
    char* myfifo="/tmp/myfifo";
    int status = mkfifo(myfifo, 0666);
    if (status == -1)
    {
        perror("Error in mkfifo\n");
        return EXIT_FAILURE;
    }



    char* str=(char*)malloc(6);
    char space=' ';
    int idx;
    int fd,write_status,highest_id,read_status; 
    struct timespec start, stop;
    double time_taken;

    clock_gettime( CLOCK_REALTIME, &start); //start timer   
    //traverse over the array 
    for(int i=0;i<50;i=i+5)  
    {
        /* fd- Descriptor for FIFO*/
        fd = open(myfifo, O_WRONLY); //open writing end
        if (fd == -1)
        {
            perror("Error in open\n");
            return EXIT_FAILURE;
        }


        //send strings first
        for(int j=i;j<i+5;j++) //send five strings at a time
        {
            strcpy(str,arr[j]);
            strncat(str,&space,1);
            idx=j;
            write_status = write(fd, str, sizeof(str));
            if (write_status == -1)
            {
                perror("Error in write\n");
                return EXIT_FAILURE;
            }

            write_status = write(fd, &idx, sizeof(int));
            if (write_status == -1)
            {
                perror("Error in write\n");
                return EXIT_FAILURE;
            }

        }
        close(fd);

        //now wait for the response  and open reading end 
        fd = open(myfifo, O_RDONLY); //open for reading mode 
        highest_id;
        read_status = read(fd, &highest_id, sizeof(int));
        if (read_status == -1)
        {
            perror("Error in write\n");
            return EXIT_FAILURE;
        }
        printf("String with highest id is %d. Now sending next 5 strings\n",highest_id);
        close(fd); //close read end 

    }
    clock_gettime( CLOCK_REALTIME, &stop); //end timer

    float temp1=stop.tv_nsec;
    float temp2=start.tv_nsec;
    time_taken =( stop.tv_sec - start.tv_sec )    + (temp1-temp2)/BILLION;
    printf("Time taken by FIFO: %lf\n",time_taken);


    
    return EXIT_SUCCESS;
}
