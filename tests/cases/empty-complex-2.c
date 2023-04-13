/* complex empty test */
/* check if the parser will not infer a nullable token when it could shift and generate a equivalent token */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "A; A ";

symbol_t _a(symbol_t* nu) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _e(symbol_t* nu) {
  printf("e\n");
  return (symbol_t){ 0 };
}

symbol_t _e2(symbol_t* nu) {
  printf("e2\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'A', 'e', 0 }, _a  },
  { 'e', NULL,                            _e  },
  
  { 'e', (unsigned int[]){ ';',      0 }, _e2 },
  { 0 }
};
