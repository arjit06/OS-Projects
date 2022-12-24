#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
int max(int a ,int b){ return (a<b)?b:a;}

int main()
{
    printf("Reciever process with pid %d\n", getpid());

    /*Create a fifo*/
    char* myfifo="/tmp/myfifo";
    mkfifo(myfifo, 0666);
        
    /*Get Input from user*/
    char* str=(char*)malloc(6);
    int read_status,highest_id=0,write_status,fd,idx;

    for(int i=0;i<50;i=i+5)  
    {
        /* fd- Descriptor for FIFO*/
        fd = open(myfifo, O_RDONLY); //open for reading mode
        if (fd == -1)
        {
            perror("Error in open\n");
            return EXIT_FAILURE;
        }


        //receive strings first
        for(int j=i;j<i+5;j++) //receive five strings at a time
        {
            read_status = read(fd, str, sizeof(str));
            if (read_status == -1)
            {
                perror("Error in write\n");
                return EXIT_FAILURE;
            }
            printf("%s", str);
            read_status = read(fd, &idx, sizeof(int));
            if (read_status == -1)
            {
                perror("Error in write\n");
                return EXIT_FAILURE;
            }
            printf("%d\n",idx);

            highest_id=max(highest_id,idx);

        }
        printf("\n");
        close(fd);

        //now send the highest id by opening the writing end 
        fd = open(myfifo, O_WRONLY); //open writing end
        if (fd == -1)
        {
            perror("Error in open\n");
            return EXIT_FAILURE;
        }
        write_status = write(fd, &highest_id, sizeof(int));
        if (write_status == -1)
        {
            perror("Error in write\n");
            return EXIT_FAILURE;
        }
        close(fd); //close read end 

    }

    system("rm /tmp/myfifo");
    return EXIT_SUCCESS;
}
