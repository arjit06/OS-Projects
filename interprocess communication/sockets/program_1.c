#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */
#include <stdbool.h>    /* 'bool' type plus 'true' and 'false' constants */

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SV_SOCK_PATH "/tmp/us_xfr"

#define BUF_SIZE 100
#define BACKLOG 5

#define BILLION  1000000000.0;
int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;

    char* buf=(char*)malloc(7);
    char* newline="\n";
    strcpy(buf,"hello");

    //generate 50 random strings
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
    

    sfd = socket(AF_UNIX, SOCK_STREAM, 0); /* Create client socket */
    if (sfd == -1) printf("socket");

    /* Construct server address, and make the connection */

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sfd, (struct sockaddr *) &addr,sizeof(struct sockaddr_un)) == -1) printf("connect");
    /* Copy stdin to socket */
    
    int highest_id=6;
    int idx;
    char space=' ';

    struct timespec start, stop;
    double time_taken;

    clock_gettime( CLOCK_REALTIME, &start); //start timer  

    for(int i=0;i<50;i=i+5)
    {
        for(int j=i;j<i+5;j++) //send five strings at a time
        {
            idx=j;
            strcpy(buf,arr[j]);
            send(sfd, buf, 5, 0);
            send(sfd, &idx, 4, 0);
        }
        numRead = read(sfd, &highest_id, 4);
        printf("String with highest id is %d. Now sending next 5 strings\n",highest_id);
    }

    clock_gettime( CLOCK_REALTIME, &stop); //end timer

    float temp1=stop.tv_nsec;
    float temp2=start.tv_nsec;
    time_taken =( stop.tv_sec - start.tv_sec )    + (temp1-temp2)/BILLION;
    printf("Time taken by FIFO: %lf\n",time_taken);
}