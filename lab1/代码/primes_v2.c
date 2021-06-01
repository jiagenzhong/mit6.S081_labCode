#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int rec[], int count)
{
  int p[2];
  pipe(p);

  if(rec[0] == -1)
  {
    exit(0);
  }

  if(fork() != 0)
  {
    printf("prime %d\n",rec[0]);
    
    for(int i=1; i<count; i++)
    {
      if( (rec[i] % rec[0]) != 0)
      {
        // 通过pipe，把ori[i]传给 下一个进程
        write(p[1], &rec[i] , sizeof(rec[i]));
      }
    }
  
    int temp = -1;
    write(p[1], &temp , sizeof(temp));
    close(p[1]);
    close(p[0]);

    wait(0);
    exit(0);
  }
  else
  {
    int buf[35];
    for(int i=0 ; i<35; i++)
    {
      buf[i] = 0;
    }

    int index = 0;
    int temp = 0;
    while(read(p[0], &temp, sizeof(temp)) != 0)
    {
      buf[index] = temp;
      index++;
      if(temp == -1)
      {
        close(p[1]);
      }
    }

    close(p[0]);
	
		if(index >= 1)
		{
      int *adr = &buf[0];
			sieve(adr,index );
		}
		else
		{  
		  printf("prime %d\n",buf[index]);
    }
		
		exit(0);
  }
}

int main(int agrc, char *argv[])
{
  int buf[35];
  for(int i=0 ; i<35; i++)
  {
    buf[i] = -1;
  }
  int index = 0;
  int temp = 0;

  printf("prime 2\n");

  for(int i = 3; i <= 35; i++)
  {
    if(i % 2 != 0)
    {
      buf[index] = i;
      index++;        
    }
  }

  if(index >= 1)
  {
    int *adr = &buf[0];
    sieve(adr,index );
  }
  else
  {  
    printf("prime %d\n",buf[index]);
  }

  exit(0);
}
