#define __STDC_WANT_LIB_EXT2__ 1
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <ncurses.h>
#include <sys/wait.h>

#include "misc.h"
#include "element.h"


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

  while(1)
  {
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
    char *out;
    int code = build(&out);
    mvprintw(3,0,"pdflatex %d", code);

    // allow viewer to exit if something closes it
    int status;
    waitpid(viewer_pid, &status, WNOHANG);

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
