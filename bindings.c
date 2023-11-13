//vim:fdm=marker
#include <stdlib.h>
#include <string.h>

#include "bindings.h"

char *bindings[][2] = {
  // lowercase letters{{{1
  {"a", "a"},
  {"b", "b"},
  {"c", "c"},
  {"d", "d"},
  {"e", "e"},
  {"f", "f"},
  {"g", "g"},
  {"h", "h"},
  {"i", "i"},
  {"j", "j"},
  {"k", "k"},
  {"l", "l"},
  {"m", "m"},
  {"n", "n"},
  {"o", "o"},
  {"p", "p"},
  {"q", "q"},
  {"r", "r"},
  {"s", "s"},
  {"t", "t"},
  {"u", "u"},
  {"v", "v"},
  {"w", "w"},
  {"x", "x"},
  {"y", "y"},
  {"z", "z"},

  // uppercase letters{{{1
  {"A", "A"},
  {"B", "B"},
  {"C", "C"},
  {"D", "D"},
  {"E", "E"},
  {"F", "F"},
  {"G", "G"},
  {"H", "H"},
  {"I", "I"},
  {"J", "J"},
  {"K", "K"},
  {"L", "L"},
  {"M", "M"},
  {"N", "N"},
  {"O", "O"},
  {"P", "P"},
  {"Q", "Q"},
  {"R", "R"},
  {"S", "S"},
  {"T", "T"},
  {"U", "U"},
  {"V", "V"},
  {"W", "W"},
  {"X", "X"},
  {"Y", "Y"},
  {"Z", "Z"},

  // lowercase greek letters{{{1
  {"'a", "\\alpha "},
  {"'b", "\\beta "},
  {"'g", "\\gamma "},
  {"'d", "\\delta "},
  {"'e", "\\epsilon "},
  {"'z", "\\zeta "},
  {"'8", "\\eta "}, // "ate"
  {"'h", "\\theta "}, // t already taken
  {"'i", "\\iota "},
  {"'k", "\\kappa "},
  {"'l", "\\lambda "},
  {"'m", "\\mu "},
  {"'n", "\\nu "},
  {"'x", "\\xi "},
  {"'o", "o"}, // teehee
  {"'p", "\\pi "},
  {"'r", "\\rho "},
  {"'s", "\\sigma "},
  {"'t", "\\tau "},
  {"'u", "\\upsilon "},
  {"'f", "\\phi "}, // phonetic
  {"'c", "\\chi "},
  {"'y", "\\psi "}, // looks like a y
  {"'w", "\\omega "}, // looks like a w

  // uppercase greek letters{{{1
  {"'A", "A"},
  {"'B", "B"},
  {"'G", "\\Gamma "},
  {"'D", "\\Delta "},
  {"'E", "E"},
  {"'Z", "Z"},
  {"'8", "H"},
  {"'H", "\\Theta "},
  {"'I", "I"},
  {"'K", "K"},
  {"'L", "\\Lambda "},
  {"'M", "M"},
  {"'N", "N"},
  {"'X", "\\Xi "},
  {"'O", "O"},
  {"'P", "\\Pi "},
  {"'R", "P"},
  {"'S", "\\Sigma "},
  {"'T", "T"},
  {"'U", "\\Upsilon "},
  {"'F", "\\Phi "},
  {"'C", "X"},
  {"'Y", "\\Psi "},
  {"'W", "\\Omega "},

  // relations &c. {{{1
  {"<=", "\\leq "},
  {">=", "\\geq "},
  {"!=", "\\neq "},
  {"|", "\\mid "},
  {"in", "\\in "},
  {"psub", "\\subset "},
  {"sub", "\\subseteq "},
  {"~=", "\\aprox "},
  {"->", "\\to "},
  {"<-", "\\gets "},
};

const int nbindings = sizeof(bindings) / sizeof(bindings[0]);

static int cmp(const void *a, const void *b)
{
  return strcmp(((char *const *) a)[0], ((char *const *) b)[0]);
}

// sort the bindings array by first entry in lexicographic order,
// so that they can looked-up efficiently
void sortBindings()
{
  qsort(bindings, nbindings, sizeof(bindings[0]), cmp);
}
