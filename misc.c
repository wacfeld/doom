#include "misc.h"

char latex_header[] =
  "\\documentclass{article}\n"
  "\\usepackage{xcolor}"
  "\\begin{document}\n";

char latex_footer[] = "\n\\end{document}\n";

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

void init_dir()
{
  char *runtimedir = getenv("XDG_RUNTIME_DIR");
  if(!runtimedir)
  {
    runtimedir = "/tmp";
  }
  asprintf(&tmpdir, "%s/doom.XXXXXX", runtimedir);

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
int build(char **output)
{
  char *cmd;
  asprintf(&cmd, "pdflatex -halt-on-error %s 2>&1", texfname);
  mvprintw(2,0,cmd);
  
  FILE *fp = popen(cmd, "r");

  int max = 10;
  char *out = malloc(max);
  *out = 0;

  char buf[100];
  while(fgets(buf, sizeof(buf), fp) != NULL)
  {
    out = concat(out, buf, &max);
  }
  *output = out;

  int exitcode = pclose(fp);
  return exitcode;
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
    int fd = open("/dev/null", O_WRONLY);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
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
