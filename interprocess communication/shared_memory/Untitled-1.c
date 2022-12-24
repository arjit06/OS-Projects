#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* data[3];
    for(int i=0;i<3;i++)
    {
        data[i]=(char*)malloc(6);
    }

    // strcpy(data[0],"hello");
    data[0] = "hello";
    data[1] = "byeye";
    data[2] = "gones";

    for(int i=0;i<3;i++)
    {
        printf("%s\n",data[i]);
    }
}