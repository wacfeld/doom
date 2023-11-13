#ifndef BINDINGS_H
#define BINDINGS_H

extern char *bindings[][2];
const int nbindings;

void sortBindings();
char *getBinding(char *input);

#endif
