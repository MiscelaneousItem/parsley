#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parsley.h"

extern char* input; // defined in test case grammar

symbol_t tlex(void* input) {

  if(!input) return (symbol_t){ '\0', 0, NULL };

  static long unsigned int i = 0;
  while(((char*)input)[i] == ' ') i++;
  return (symbol_t){ ((char*)input)[i++], 0, NULL };

}

int main() {

  p_parse(gr_rules, input, tlex);

  return 0;
}
