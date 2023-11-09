#define __STDC_WANT_LIB_EXT2__ 1
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <ncurses.h>

#define USAGESTR "USAGE: ./doom FILE"

char latex_header[] =
  "\\documentclass{article}\n"
  "\\begin{document}\n";

char latex_footer[] = "\n\\end{document}\n";

char tmpdir[] = "/tmp/doom.XXXXXX";
char *texfname;
// pass this to mupdf
char *pdffname;

// need these also for calling remove()
char *auxfname;
char *logfname;

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

void writef(char *fname, const char *fmt, ...)
{
  FILE *fp = fopen(fname, "w");
  if(!fp)
  {
    perror("fopen failed: ");
    exit(1);
  }

  va_list args;
  va_start(args, fmt);
  vfprintf(fp, fmt, args);
  va_end(args);

  fclose(fp);
}

// call pdflatex on file using system() and return the exit code
int build()
{
  char *cmd;
  asprintf(&cmd, "pdflatex %s 1>/dev/null 2>/dev/null", texfname);
  mvprintw(2,0,cmd);
  return system(cmd);
}

// start pdf viewer using fork()/exec() and return its PID
pid_t start_viewer()
{
  pid_t child_pid;

  // parent
  if((child_pid = fork()))
  {}

  // child
  else
  {
    execlp("mupdf", "mupdf", pdffname, (char*)NULL);
  }
  return child_pid;
}

int viewer_alive(pid_t pid)
{
  int val = kill(pid, 0);
  if(val == 0)
    return 1;

  else
    return 0;
}

// tell the pdf viewer process to redisplay the file
// in the case of mupdf this means sending SIGHUP to it
void update_viewer(pid_t pid)
{
  kill(pid, SIGHUP);
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

void cleanup()
{
  terminate_ncurses();
  refresh();
  endwin();

  remove(texfname);
  remove(pdffname);
  remove(auxfname);
  remove(logfname);
  terminate_dir();
}

void handle_sigint(int sig)
{
  cleanup();
  exit(0);
}

int main(int argc, char **argv)
{
  signal(SIGINT, handle_sigint);

  // if(argc <= 1)
  // {
  //   puts(USAGESTR);
  //   return 1;
  // }

  // create temp directory
  init_dir();
  chdir(tmpdir);
  puts(tmpdir);

  // create filenames
  asprintf(&texfname, "%s/file.tex", tmpdir);
  asprintf(&pdffname, "%s/file.pdf", tmpdir);
  asprintf(&auxfname, "%s/file.aux", tmpdir);
  asprintf(&logfname, "%s/file.log", tmpdir);

  init_ncurses();

  int bufmax = 10;
  char *buf = malloc(bufmax);
  *buf = '\0';

  pid_t viewer_pid = -1;

  int x = 0;

  while(1)
  {
    //mvprintw(10,0,"%d idiot", x++);
    // print buffer & info
    mvprintw(0,0, buf);
    mvprintw(1,0,texfname);
    
    // get input from user
    unsigned char c = getch();
    erase();
    mvprintw(10,0,"the CODE RECEIVED is %d",c);
    if(c >= 128)
      continue;

    // append to buffer & write to file
    buf = append(buf, c, &bufmax);
    writef(texfname, "%s%s%s", latex_header, buf, latex_footer);

    // build
    int code = build();
    mvprintw(3,0,"%d", code);

    // update viewer if open
    if(viewer_pid != -1 && viewer_alive(viewer_pid))
    {
      update_viewer(viewer_pid);
    }

    // open viewer if not already open
    else
    {
      viewer_pid = start_viewer();
      mvprintw(6,0,"%d",viewer_pid);
    }
  }

  cleanup();
}
