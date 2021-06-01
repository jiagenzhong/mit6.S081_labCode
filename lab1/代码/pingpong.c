#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int agrc, char *argv[])
{
    int p[2];
    pipe(p);

    if(fork() == 0)
    {                
        char rbuf[10];
        read(p[0], rbuf, sizeof p[0]);
        printf("%d: received %s\n", getpid(), rbuf);
        write(p[1], "pong", 4);        
    }
    else
    {
        write(p[1], "ping", 4);
        close(p[1]);
        
        wait(0);
        char rbuf[10];
        
        read(p[0], rbuf, sizeof p[0]);
        printf("%d: received %s\n", getpid(), rbuf);
    }

    exit(0);
}