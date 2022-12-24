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

#define SV_SOCK_PATH "/tmp/us_xfr"

#define BUF_SIZE 100
#define BACKLOG 5

int max(int a ,int b){ return (a<b)?b:a;}

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int listener_socket, working_socket;
    ssize_t numRead;
    char* buf=(char*)malloc(42);

    listener_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (listener_socket == -1)
    printf("socket");
    
    /* Construct server socket address, bind socket to it,
    and make this a listening socket */
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) printf("remove-%s", SV_SOCK_PATH);

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (bind(listener_socket, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) printf("bind");

    if (listen(listener_socket, BACKLOG) == -1) printf("listen");
    
    
    working_socket = accept(listener_socket, NULL, NULL);
    if (working_socket == -1)printf("accept");

    /* Transfer data from connected socket to stdout until EOF */

    int highest_id=0,idx;
    
    for(int i=0;i<50;i=i+5)
    {
        for(int j=i;j<i+5;j++) //receive five strings at a time
        {
            numRead = read(working_socket, buf, 5);
            printf("%s ",buf);

            numRead = read(working_socket, &idx, 4);
            printf("%d\n",idx);
            highest_id=max(highest_id,idx);
        }
        printf("\n");
        send(working_socket,&highest_id,4,0);
    }
}