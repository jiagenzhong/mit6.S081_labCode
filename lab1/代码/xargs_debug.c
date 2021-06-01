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

//  char *temp[] = {"grep", "hello","./c/b", 0};
//  char *temp[] = { "echo", "THIS", "IS", "ECHO", 0 };

//    printf("%s %s %s %s %s %s %s\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5]);
//    printf("%s %s %s %s %s %s %s\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]);
    exec("grep", cmd);
    printf("exec failed!\n");
    exit(1);
  }
  else
  {
    wait(&status);
//    printf("the child exited with status %d\n", status);
  }
}

int main(int agrc, char *argv[])
{
  char buf[512];
  read(0,buf, sizeof(buf));
//  write(1, buf , n);

  int i = 0;
  while(buf[i] != '\0'){
    char lefcmd[33];
    char *dest = lefcmd;
    
    while(buf[i] != '\n'){
      *dest++ = buf[i];
      i++;
    }
    *dest++ = '\0';
//    printf("\n--lefcmd:%s\n",lefcmd);
    forkexec(lefcmd, agrc ,argv);
    i++;
  }

  exit(0);
}