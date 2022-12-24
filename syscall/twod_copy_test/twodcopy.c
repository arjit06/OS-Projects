#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
#define TWOD_COPY_SYSCALL 452

int main()
{
    float src_arr[2][5] = {{61,7, 9, 11, 12},{6, 7, 8, 9, 10}};
    float dest_arr[2][5]; //no. of rows, no. of columns respectively

    long sys_call_status;

    sys_call_status = syscall(TWOD_COPY_SYSCALL, src_arr, dest_arr);

    if (sys_call_status != EFAULT)
    {
        printf("Message : System Call 452 successfuly invoked \n");
        //print(*dest_arr, 2, 5);
        for (int i = 0; i < 2; i++)
        {
            for(int j=0;j<5;j++)
            {
                printf("%f ",dest_arr[i][j]);
            }
            printf("\n");
            
        }
    }

    return 0;
}
