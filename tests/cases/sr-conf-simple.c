/* simple S/R conflict test */
#include <stdio.h>

#include "parsley_grammar.h"

char* input = "AB A";

symbol_t _a(symbol_t* symbols) {
  printf("a\n");
  return (symbol_t){ 0 };
}

symbol_t _b(symbol_t* symbols) {
  printf("b\n");
  return (symbol_t){ 0 };
}

rule_def_t gr_rules[] = {
  { 'a', (unsigned int[]){ 'A', 'B', 0 }, _a },
  { 'b', (unsigned int[]){ 'A',      0 }, _b },
  { 0 }
};

/*
tree_node_t gr_tree[] = {
    { 'a',  (rule_t[]){ (rule_t){ (tree_node_t*[]){ gr_tree + 2, gr_tree + 2, NULL }, _a }, (rule_t){ 0 } } },
    { 'b',  (rule_t[]){ (rule_t){ (tree_node_t*[]){ gr_tree + 2,              NULL }, _b }, (rule_t){ 0 } } },
    { 'A',  NULL,                                                                                     },
    { 'B',  NULL,                                                                                     },
    { '\0', NULL,                                                                                     }
  };
*/
