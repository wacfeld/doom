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

