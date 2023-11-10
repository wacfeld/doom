#include "element.h"

typedef struct element
{
  Type type;
  int nch;
  int maxch;
  struct element **children;
} Element;

Element *makeElement(Type type)
{
  
}

char *element2str(Element *e)
{
  Type t = e->type;
  char *s;

  if(t == LIST)
  {
    for(int i = 0; i < e->nch; i++)
    {
      
    }
  }

  if(t == EQN)
  {
    
  }

  else if(t == FRAC)
  {
    char *c1 = element2str(e->children[0]);
    char *c2 = element2str(e->children[1]);
    asprintf(&s, "\\frac{%s}{%s}", c1, c2);
  }
}
