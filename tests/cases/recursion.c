/* basic empty test */

/* check wherer the parser can infer the existence of an nullable token given a rule and sequence using only tokens */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "AAAA BBB;";

symbol_t _a(symbol_t*) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _e(symbol_t*) {
  printf("e\n");
  return (symbol_t){ 0 };
}

symbol_t _b(symbol_t*) {
  printf("b\n");
  return (symbol_t){ 0 };
}

symbol_t _c(symbol_t*) {
  printf("c\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'c', (unsigned int[]){ 'a', 'b', 0 }, _c },
  { 'a', (unsigned int[]){ 'A',      0 }, _a },
  { 'a', (unsigned int[]){ 'a', 'A', 0 }, _a },
  { 'b', (unsigned int[]){ ';',      0 }, _b },
  { 'b', (unsigned int[]){ 'B', 'b', 0 }, _b },
  { 0 }
};
