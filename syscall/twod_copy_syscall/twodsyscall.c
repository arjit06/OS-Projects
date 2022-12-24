#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE4(twod_copy, float*, src, float*, dest, int*, rows, int*, columns)
{
	float buffer[2][5];

	if (__copy_from_user(buffer,src,sizeof(float)*10))
			return -EFAULT;
        if (__copy_to_user(dest,buffer,sizeof(float)*10))
                         return -EFAULT;
        return 0; 
}	
