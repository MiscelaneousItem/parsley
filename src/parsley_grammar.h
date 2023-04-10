#ifndef _STRUCTS
#define _STRUCTS

typedef struct { // symbols outputed by the lexer formed by reduction
  unsigned int type, dsize;
  void* data;
} symbol_t;

typedef struct tree_node tree_node_t;

typedef struct { // minimal amount of information to qualify a rule
  unsigned int outcome, *parents;
  symbol_t (*function)(symbol_t*);
} rule_def_t;

typedef struct { // rule as used in the grammar tree
  unsigned int outcome, size;  
  tree_node_t** parents;
  symbol_t (*function)(symbol_t*);
} rule_t;

struct tree_node {
  unsigned int outcome, nrules, nchildren;
  tree_node_t** children;
  rule_t *rules;
};

typedef struct {
  int size;
  tree_node_t* val;
} tree;

#endif

extern rule_def_t gr_rules[];

// gr_init() and gr_close() allow the user to malloc/free variables and set up context(s) required for their grammar, reduce_hook() allows the user to recover the child nterm created upon a reduce action and its parents 
extern void init_hook();                                          // enable with INIT_HOOK_ON
extern void reduce_hook(symbol_t, const symbol_t*, unsigned int); //       "     REDUCE_HOOK_ON
extern void close_hook();                                         //       "     CLOSE_HOOK_ON

