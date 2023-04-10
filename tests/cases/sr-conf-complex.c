/* S/R conflict test */

/* check whether a symbol in (ie not at the start) a rule will not be incorrectly reduced to a smaller rule */   
/* conversly check whether smaller rules will be reduced when one can be sure that a larger rule is not in play */

#include <stdio.h>

#include "parsley_grammar.h"

char* input = "AAB DCC AA CC";

symbol_t _a(symbol_t*) {
  printf("a\n");
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

symbol_t _d(symbol_t*) {
  printf("d\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'A', 'A', 'B', 0 }, _a },
  { 'b', (unsigned int[]){ 'A',           0 }, _b },
  { 'c', (unsigned int[]){ 'D', 'C', 'C', 0 }, _c },
  { 'd', (unsigned int[]){ 'C',           0 }, _d },
  { 0 }
};
