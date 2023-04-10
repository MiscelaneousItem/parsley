/* complex empty test */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "A";

symbol_t _a(symbol_t*) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _e(symbol_t*) {
  printf("e\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'e', 'A', 0 }, _a  },
  { 'e', NULL,                            _e  },
  { 0 }
};
