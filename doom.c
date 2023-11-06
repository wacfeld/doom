#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define USAGESTR "USAGE: ./doom FILE"

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

char* concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

int main(int argc, char **argv)
{
  if(argc <= 1)
  {
    puts(USAGESTR);
    return 1;
  }

  char *fname = argv[1];
  puts(fname);
  init();
  puts(template);

  char *dest = concat(template, "/file.tex");

  symlink(fname, dest);
  getchar();

  terminate();
}
