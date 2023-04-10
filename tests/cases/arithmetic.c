/* arithmetic test */

/* parses arithmetic operations, with correct operator precedence */

#include <stdio.h>

#include "parsley_grammar.h"

char* input =
  "N * N ;"
  "N + N ;"
  "N * N + N ;"
  "N + N * N ; "
  "N + N + N;";

symbol_t _s(symbol_t*) {
  printf("s : s + s\n");
  return (symbol_t){ 0 };
}

symbol_t _s__m(symbol_t*) {
  printf("s : m\n");
  return (symbol_t){ 0 };
}

symbol_t _m(symbol_t*) {
  printf("m : m * m\n");
  return (symbol_t){ 0 };
}

symbol_t _m__N(symbol_t*) {
  printf("m : N\n");
  return (symbol_t){ 0 };
}

symbol_t _b(symbol_t*) {
  printf(";\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 's', (unsigned int[]){ 's', '+', 's', 0 }, _s },
  { 's', (unsigned int[]){ 'm',           0 }, _s__m },
  { 'm', (unsigned int[]){ 'm', '*', 'm', 0 }, _m },
  { 'm', (unsigned int[]){ 'N',           0 }, _m__N },
  { 'b', (unsigned int[]){ ';',           0 }, _b },
  { 0 }

};
