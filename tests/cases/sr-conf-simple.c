/* simple S/R conflict test */
#include <stdio.h>

#include "parsley_grammar.h"

char* input = "AB A";

symbol_t _a(symbol_t* nu) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _b(symbol_t* nu) {
  printf("b\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'A', 'B', 0 }, _a },
  { 'b', (unsigned int[]){ 'A',      0 }, _b },
  { 0 }
};
