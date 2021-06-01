#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

void forkexec(char lcmd[],int count, char * rcmd[]) 
{
  int status;
  if(fork() == 0){
    
    char *cmd[MAXARG] = {lcmd};
    if(count <=1 && count >= MAXARG-2){
      printf("count is error.");
      exit(-1);
    }
    else{
      for(int i=1; i < count; i++){
        cmd[i-1] = rcmd[i];
      }
      cmd[count-1] = lcmd;
      cmd[count] = '\0';
    }

    exec("grep", cmd);
    printf("exec failed!\n");
    exit(1);
  }
  else
  {
    wait(&status);
  }
}

int main(int agrc, char *argv[])
{
  char buf[512];
  read(0,buf, sizeof(buf));

  int i = 0;
  while(buf[i] != '\0'){
    char lefcmd[33];
    char *dest = lefcmd;
    
    while(buf[i] != '\n'){
      *dest++ = buf[i];
      i++;
    }
    *dest++ = '\0';
    forkexec(lefcmd, agrc ,argv);
    i++;
  }

  exit(0);
}