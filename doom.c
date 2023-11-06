#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define USAGESTR "USAGE: ./doom FILE\n"

char template[] = "/tmp/doom.XXXXXX";

void init()
{
  char *dir_name = mkdtemp(template);

  if(dir_name == NULL)
  {
    perror("mkdtemp failed: ");
    exit(1);
  }
}

void terminate()
{
  if(rmdir(template) == -1)
  {
    perror("rmdir failed: ");
    exit(1);
  }
}

int main(int argc, char **argv)
{
  if(argc <= 1)
  {
    printf(USAGESTR);
    return 1;
  }

  char *fname = argv[1];
  puts(fname);
  init();
  puts(template);
  terminate();
}
