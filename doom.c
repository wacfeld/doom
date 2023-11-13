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
#include "input.h"
#include "bindings.h"

int main(int argc, char **argv)
{
  signal(SIGINT, handle_sigint);

  sortBindings();

  // char s[100];
  // while(fgets(s, 100, stdin) != NULL)
  // {
  //   if(strlen(s))
  //   {
  //     s[strlen(s)-1] = 0;
  //   }
  //   char *res = getBinding(s);
  //   if(res)
  //     puts(res);
  //   else
  //     puts("Not found");
  // }

  // for(int i = 0; i < nbindings; i++)
  // {
  //   printf("%s %s\n", bindings[i][0], bindings[i][1]);
  // }

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

  //int bufmax = 10;
  //char *buf = malloc(bufmax);
  //*buf = '\0';

  // root element is a list
  root = makeElement(NULL, LIST, NULL);
  cur_element = root;

  pid_t viewer_pid = -1;

  while(1)
  {
    // get input from user
    unsigned char c = getch();
    erase();
    //mvprintw(10,0,"the CODE RECEIVED is %d",c);

    handle_key(c);
    char *text = element2str(root);
    
    mvprintw(0,0, text);
    mvprintw(1,0, mode == NORMAL ? "NORMAL" : "INSERT");
    mvprintw(2,0, "%p", cur_element);
    refresh();

    // write to file
    writef(texfname, "%s%s%s", latex_header, text, latex_footer);
    free(text);

    // build
    char *out;
    int code = build(&out);
    mvprintw(3,0,"pdflatex exits with %d", code);

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
    }
  }

  cleanup();
}
