#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int agrc, char *argv[])
{
    // deal with the user forget input the numbers
    if(agrc <= 1)
    {
        fprintf(2, "usage: sleep pattern [times count]\n");
        exit(1);
    }

    //convert string to an integer
    int times = atoi(argv[1]);

    if(sleep(times) == 0)
    {
        fprintf(1,"Call sleep(%d) success\n",times);
    }

    exit(0);
}