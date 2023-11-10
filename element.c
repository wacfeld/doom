#include "element.h"
#include "misc.h"

typedef struct element
{
  Type type;

  Element *parent;

  int nch;
  int maxch;
  struct element **children;

  char *s;
} Element;

Element *makeElement(Element *parent, Type type, char *s)
{
  Element *e = malloc(sizeof(Element));
  e->type = type;
  e->parent = parent;
  
  // a LIST starts with 0 children
  if(type == LIST)
  {
    e->nch = 0;
    e->maxch = 1;
    e->children = malloc(sizeof(Element*));
  }

  // a EQN contains one LIST
  // so does a SQRT
  else if(type == EQN || type == SQRT)
  {
    e->nch = 1;
    e->children = malloc(sizeof(Element*));
    e->children[0] = makeElement(e, LIST, NULL);
  }

  // a FRAC contains two LISTS
  else if(type == FRAC)
  {
    e->nch = 2;
    e->children = malloc(2*sizeof(Element*));
    e->children[0] = makeElement(e, LIST, NULL);
    e->children[1] = makeElement(e, LIST, NULL);
  }

  // a SYMB is atomic, it contains only a string
  else if(type == SYMB)
  {
    e->s = s;
  }

  return e;
}

char *highlight(Element *e)
{
  char *inner = element2str(e);
  char *s;
  asprintf(&s, "\\xcolor{green}{%s}", inner);
  return s;
}

char *element2str(Element *e)
{
  Type t = e->type;

  if(t == LIST)
  {
    int max = 1;
    char *s = calloc(max, 1);

    for(int i = 0; i < e->nch; i++)
    {
      s = concat(s, element2str(e->children[i]), &max);
    }
    return s;
  }

  else if(t == EQN)
  {
    char *s;
    char *inner = element2str(e->children[0]);
    asprintf(&s, "\\begin{equation} %s \\end{equation}", inner);
    return s;
  }

  else if(t == FRAC)
  {
    char *s;
    char *c1 = element2str(e->children[0]);
    char *c2 = element2str(e->children[1]);
    asprintf(&s, "\\frac{%s}{%s}", c1, c2);
    return s;
  }

  else if(t == SQRT)
  {
    char *s;
    char *inner = element2str(e->children[0]);
    asprintf(&s, "\\sqrt{%s}", inner);
    return s;
  }

  else if(t == SYMB)
  {
    return e->s;
  }

  else
  {
    return "unknown";
  }
}
