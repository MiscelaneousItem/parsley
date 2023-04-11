/* complex empty test */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "B";

symbol_t _a(symbol_t* nu) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _b(symbol_t* nu) {
  printf("b\n");
  return (symbol_t){ 0 };
}

symbol_t _e(symbol_t* nu) {
  printf("e\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'e', 'b', 0 }, _a  },
  { 'b', (unsigned int[]){ 'C',      0 }, _b  },
  { 'b', (unsigned int[]){ 'B',      0 }, _b  },
  { 'e', NULL,                            _e  },
  { 0 }
};
