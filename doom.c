#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *init()
{
  char template[] = "/tmp/doom.XXXXXX";
  char *dir_name = mkdtemp(template);

  if(dir_name == NULL)
  {
    perror("mkdtemp failed: ");
    return 0;
  }

  return dir_name;
}

void terminate(char *dir_name)
{
  if(rmdir(dir_name) == -1)
  {
    perror("rmdir failed: ");
  }
}

int main()
{
  char *s = init();
  print("%s\n", s);
  terminate(s);
}
