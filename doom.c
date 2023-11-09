#define __STDC_WANT_LIB_EXT2__ 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <ncurses.h>

#define USAGESTR "USAGE: ./doom FILE"

char tmpdir[] = "/tmp/doom.XXXXXX";

void init_dir()
{
  char *dir_name = mkdtemp(tmpdir);

  if(dir_name == NULL)
  {
    perror("mkdtemp failed: ");
    exit(1);
  }
}

void terminate_dir()
{
  if(rmdir(tmpdir) == -1)
  {
    perror("rmdir failed: ");
    exit(1);
  }
}

void init_ncurses()
{
	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
}

void terminate_ncurses()
{
	refresh();
	endwin();
}

void write_to_file(char *fname, char *txt)
{
  FILE *fp = fopen(fname, "w");
  if(!fp)
  {
    perror("fopen failed: ");
    exit(1);
  }

  fputs(txt, fp);

  fclose(fp);
}

// s1 is dynamically allocated pointer
char *concat(char *s1, const char *s2, int *max)
{
  int l1=strlen(s1), l2=strlen(s2);

  int must_realloc = 0;
  while(l1 + l2 + 2 > *max)
  {
    *max *= 2;
    must_realloc = 1;
  }

  if(must_realloc)
  {
    s1 = realloc(s1, *max);
  }

  strcat(s1, s2);
  
  return s1;
}

char *append(char *s, char c, int *max)
{
  int l = strlen(s);
  if(l + 2 > *max)
  {
    *max *= 2;
    s = realloc(s, *max);
  }

  s[l] = c;
  s[l+1] = '\0';

  return s;
}

int main(int argc, char **argv)
{
  // if(argc <= 1)
  // {
  //   puts(USAGESTR);
  //   return 1;
  // }

  // create temp directory
  init_dir();
  puts(tmpdir);

  // create tex file
  char *dest;
  asprintf(&dest, "%s/file.tex", tmpdir);

  init_ncurses();

  int bufmax = 10;
  char *buf = malloc(bufmax);
  *buf = '\0';

  while(1)
  {
    mvprintw(0,0, buf);
    char c = getch();
    move(0,0);
    buf = append(buf, c, &bufmax);
    clrtoeol();
  }

  terminate_ncurses();

  // destroy files

  // destroy temp directory
  terminate_dir();
	refresh();
	endwin();

}
