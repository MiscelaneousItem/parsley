/* empty first token */
/* check if the parser can infer a empty token at the start of a rule  */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "A";

symbol_t _a(symbol_t* nu) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _e(symbol_t* nu) {
  printf("e\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'e', 'A', 0 }, _a  },
  { 'e', NULL,                            _e  },
  { 0 }
};
