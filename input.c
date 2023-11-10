#define __STDC_WANT_LIB_EXT2__ 1

#include <ctype.h>

#include "input.h"

Mode mode = NORMAL;

void handle_key(unsigned char key)
{
  if(key >= 128)
    return;

  if(mode == NORMAL)
    handle_normal(key);
  else if(mode == INSERT)
    handle_insert(key);

}

int is_special(unsigned char c)
{
  // TODO make this more complete
  return !(isalnum(c) || isspace(c));
}

void handle_insert(unsigned char key)
{
  // normal
  if(key == 27) // escape
  {
    mode = NORMAL;
  }

  else if(is_special(key))
  {
     // TODO
  }

  else
  {
    char *s;
    asprintf(&s, "%c", key);
    Element *e = makeElement(NULL, SYMB, s);
    insertLeft(e, cur_element);
  }
}

void handle_normal(unsigned char key)
{
  // insert
  if(key == 'i')
  {
    mode = INSERT;
  }

  // left
  else if(key == 'h')
  {
    cur_element = leftOf(cur_element);
  }

  // right
  else if(key == 'l')
  {
    cur_element = rightOf(cur_element);
  }

  // descend
  else if(key == 'j')
  {
    if(cur_element->nch > 0)
      cur_element = cur_element->children[0];
  }

  // ascend
  else if(key == 'k')
  {
    if(cur_element->parent != NULL)
      cur_element = cur_element->parent;
  }
}

