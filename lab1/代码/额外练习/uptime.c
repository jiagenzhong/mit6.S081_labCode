#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int agrc, char *argv[])
{


    //convert string to an integer
    int times = uptime();
    fprintf(1,"Uptime is calling: %d \n",times);
    
    exit(0);
}