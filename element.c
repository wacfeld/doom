#include "element.h"
#include "misc.h"

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
    e->nch = 0;
  }

  return e;
}

int getIndex(Element *parent, Element *child)
{
  for(int i = 0; i < parent->nch; i++)
  {
    if(child == parent->children[i])
      return i;
  }

  return -1;
}

Element *leftOf(Element *e)
{
  Element *parent = e->parent;
  // if no parent, return original element
  if(parent == NULL)
    return e;

  int i = getIndex(parent, e);

  // if first child, TODO
  if(i == 0)
  {
    return e;
  }

  else
  {
    return parent->children[i-1];
  }
}

Element *rightOf(Element *e)
{
  Element *parent = e->parent;
  // if no parent, return original element
  if(parent == NULL)
    return e;

  int i = getIndex(parent, e);
  
  // if last child, TODO
  if(i == parent->nch-1)
  {
    return e;
  }

  else
  {
    return parent->children[i+1];
  }
}

char *highlight(char *s)
{
  char *t;
  asprintf(&t, "\\textcolor{green}{%s}", s);
  free(s);
  return t;
}

char *element2str(Element *e)
{
  Type t = e->type;

  char *s;
  if(t == LIST)
  {
    int max = 1;
    s = calloc(max, 1);

    for(int i = 0; i < e->nch; i++)
    {
      s = concat(s, element2str(e->children[i]), &max);
    }
  }

  else if(t == EQN)
  {
    char *inner = element2str(e->children[0]);
    asprintf(&s, "\\begin{equation} %s \\end{equation}", inner);
  }

  else if(t == FRAC)
  {
    char *c1 = element2str(e->children[0]);
    char *c2 = element2str(e->children[1]);
    asprintf(&s, "\\frac{%s}{%s}", c1, c2);
  }

  else if(t == SQRT)
  {
    char *inner = element2str(e->children[0]);
    asprintf(&s, "\\sqrt{%s}", inner);
  }

  else if(t == SYMB)
  {
    s = e->s;
  }

  else
  {
    s = "unknown";
  }

  if(e == cur)
    return highlight(s);
  else
    return s;
}
