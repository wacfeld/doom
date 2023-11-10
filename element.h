#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdlib.h>

typedef enum {LIST, EQN, FRAC, SQRT, SYMB} Type;
typedef struct element Element;

Element *makeElement(Element *parent, Type type, char *s);
char *element2str(Element *e);

// state variables
Element *root;
Element *cur;

#endif
