#ifndef MISC_H
#define MISC_H

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


#define USAGESTR "USAGE: ./doom FILE"

extern char latex_header[];
extern char latex_footer[];

//char tmpdir[] = "/tmp/doom.XXXXXX";
char *tmpdir;
char *texfname;
// pass this to mupdf
char *pdffname;

// need these also for calling remove()
char *auxfname;
char *logfname;


char *concat(char *s1, const char *s2, int *max)   ;
char *append(char *s, char c, int *max)            ;
void init_dir()                                    ;
void terminate_dir()                               ;
void init_ncurses()                                ;
void terminate_ncurses()                           ;
void writef(char *fname, const char *fmt, ...)     ;
int build(char **output)                           ;
pid_t start_viewer()                               ;
int viewer_alive(pid_t pid)                        ;
void update_viewer(pid_t pid)                      ;
void cleanup()                                     ;
void handle_sigint(int sig)                        ;

#endif
