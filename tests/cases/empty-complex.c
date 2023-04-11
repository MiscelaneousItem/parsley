/* complex empty test */

/* check whether the parser can infer the existence of an nullable token given a rule and sequence with the look ahead being a nonterminal */
/* to achieve this the parser must deconstruct the look ahead nonterminal until it can know whether it can be formed given the look ahead terminal */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "AB";

symbol_t _a(symbol_t* nu) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _b(symbol_t* nu) {
  printf("b\n");
  return (symbol_t){ 0 };
}

symbol_t _b2(symbol_t* nu) {
  printf("b2\n");
  return (symbol_t){ 0 };
}

symbol_t _c(symbol_t* nu) {
  printf("c\n");
  return (symbol_t){ 0 };
}

symbol_t _e(symbol_t* nu) {
  printf("e\n");
  return (symbol_t){ 0 };
}


rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'A', 'e', 'b', 0 }, _a  },
  { 'b', (unsigned int[]){ 'A', 'A',      0 }, _b  },
  { 'b', (unsigned int[]){ 'c',           0 }, _b2 },
  { 'c', (unsigned int[]){ 'B',           0 }, _c  },
  { 'e', NULL,                              _e  },
  { 0 }
};
