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

void handle_insert(unsigned char key)
{
  
}

void handle_normal(unsigned char key)
{
  // left
  if(key == 'h')
  {
    cur = leftOf(cur);
  }

  // right
  else if(key == 'l')
  {
    cur = rightOf(cur);
  }

  // descend
  else if(key == 'j')
  {
    if(cur->nch > 0)
      cur = cur->children[0];
  }

  // ascend
  else if(key == 'k')
  {
    if(cur->parent != NULL)
      cur = cur->parent;
  }
}

