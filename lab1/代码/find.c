#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(char *path, char *fileName)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    fprintf(2, "find: the filePath is a fileName! please enter the filePath!\n");
    exit(1);
  
  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }

      if(st.type == 2)
      {
        //printf FileName
        char fname[DIRSIZ+1];

        long flength = strlen(fileName);
        memcpy(fname, fmtname(buf), flength);
        fname[flength] = '\0';

        if(strcmp(fname,fileName) == 0){
          printf("%s/%s\n",path,fileName);
        }
        else
        {
          continue;
        }
      }
      else if(st.type == 1)
      {
        char dir1[DIRSIZ+1] = ".";
        memset(dir1+1, ' ', DIRSIZ-1);
        char dir2[DIRSIZ+1] = "..";
        memset(dir2+2, ' ', DIRSIZ-2);

        if(strcmp(dir1,fmtname(buf)) == 0 || strcmp(dir2,fmtname(buf))==0)
          continue;

        char newpath[512];
        long int pathlenth = strlen(path);
        memcpy(newpath, path, pathlenth);
        newpath[pathlenth] = '\0';

        char *dest = newpath+strlen(newpath);
        char *src = fmtname(buf);
        long int end = strlen(fmtname(buf));
        long int begin = 0;
        *dest++ = '/';
        while(begin != end && *src!=' ')
        {
          *dest++ = *src++;
          begin++;
        }
        *dest++ = '\0';

        find(newpath,fileName);
      }
    }

  }
}

int main(int argc, char *argv[])
{

  if(argc < 3){
    fprintf(2, "usage: find pattern [file path] [file name]\n");
    exit(1);
  }
  
  find(argv[1], argv[2]);
  exit(0);
}