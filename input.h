#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include "element.h"

typedef enum {NORMAL, INSERT} Mode;

Mode mode;

void handle_key(unsigned char key);
void handle_insert(unsigned char key);
void handle_normal(unsigned char key);

#endif
