/* basic empty test */

/* check wherer the parser can infer the existence of an nullable token given a rule and sequence using only tokens */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "AB AC A";

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
  { 'a', (unsigned int[]){ 'A', 'e', 'B', 0 }, _a },
  { 'e', NULL,                                 _e },
  { 'b', (unsigned int[]){ 'A', 'C',      0 }, _b },
  { 'c', (unsigned int[]){ 'A',           0 }, _c },
  { 0 }
};
