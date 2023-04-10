#include "parsley.h"
#include "parsley_grammar.h"
#include "khash.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) (a<b ? a : b)

// create hash map that associates symbol type with the corresponding key node

KHASH_MAP_INIT_INT(NODE_MAP, tree_node_t*)
int absent;  
  
static tree_node_t* get_node_by_outcome(khash_t(NODE_MAP) * nodemap, unsigned int outcome) {
  khint_t k = kh_get(NODE_MAP, nodemap, outcome);
  if(k != kh_end(nodemap)) return kh_value(nodemap, k);
  return NULL;
}

static tree gen_gr_tree(khash_t(NODE_MAP)* nodemap, rule_def_t* rules) {
  tree_node_t* output = NULL;
  unsigned int output_size = 0, output_capacity = 0;
  
  for(rule_def_t* rule = rules ; rule->outcome; rule++) {
    
    if(output_capacity == output_size) {
      output_capacity += 100;
      output = realloc(output, output_capacity * sizeof(tree_node_t));
      memset(output + output_size, 0, (output_capacity - output_size) * sizeof(tree_node_t));
    }
    tree_node_t* node = get_node_by_outcome(nodemap, rule->outcome);
    
    // add the node if it doesn't exist
    if(!node) {
      output[output_size].outcome = rule->outcome;
      output[output_size].rules = calloc(1, sizeof(rule_t));
      output[output_size].nrules = 0;
      output[output_size].children = calloc(1, sizeof(tree_node_t*));
      output[output_size].nchildren = 0;
      
      khint_t k = kh_put(NODE_MAP, nodemap, output[output_size].outcome, &absent);
      kh_value(nodemap, k) = output + output_size;
      
      node = output + output_size;
      output_size++;
    }
    
    // init rule params
    
    node->rules[node->nrules].outcome = rule->outcome;
    node->rules[node->nrules].function = rule->function;
    node->rules[node->nrules].parents = NULL;
    
    if(rule->parents) {
      for(unsigned int j = 0; rule->parents[j]; j++) {
	node->rules[node->nrules].parents = realloc(node->rules[node->nrules].parents, (j + 2) * sizeof(tree_node_t*));
	tree_node_t* target_node = get_node_by_outcome(nodemap, rule->parents[j]);
	
	// add node if it doesn't exist
	if(!target_node) {
	  output[output_size].outcome = rule->parents[j];
	  output[output_size].rules = calloc(1, sizeof(rule_t));
	  output[output_size].nrules = 0;
	  output[output_size].children = calloc(1, sizeof(tree_node_t*));
	  output[output_size].nchildren = 0;
	  
	  khint_t k = kh_put(NODE_MAP, nodemap, output[output_size].outcome, &absent);
	  kh_value(nodemap, k) = output + output_size;
  
	  target_node = output + output_size;
	  
	  output_size++;
	}
	// fill out node parents
	node->rules[node->nrules].parents[j] = target_node;
	node->rules[node->nrules].parents[j + 1] = 0;
	node->rules[node->nrules].size = j + 1;

	// fill out target_node children 
	target_node->children[target_node->nchildren] = node;
	target_node->nchildren++;
	target_node->children = realloc(target_node->children, (target_node->nchildren + 1) * sizeof(tree_node_t*));
	target_node->children[target_node->nchildren] = NULL;
      }
    }
    node->nrules++;
    node->rules = realloc(node->rules, (node->nrules+1) * sizeof(rule_t) );
    node->rules[node->nrules].outcome = 0;
    
  }
  
  return (tree){ output_size, output };
}


static void free_gr_tree(tree tree) {
  for(int i = 0; i < tree.size; i++) {
    tree_node_t* node = tree.val + i;
    for(int i = 0; i < node->nrules; i++) {
      free(node->rules[i].parents);
      node->rules[i].parents = NULL;
    }
    node->nrules = 0;
    free(node->rules);
    node->rules = NULL;
    free(node->children);
    node->children = NULL;
  }
}


/* get_rule() returns the rule corresponding to the sequence symbols or (rule_t){ 0 } if none correspond */
static rule_t get_rule(khash_t(NODE_MAP)* nodemap, const symbol_t* symbols, unsigned int nsymbols) { 
  tree_node_t* node = get_node_by_outcome(nodemap, symbols[0].type);
  for(unsigned int i = 0; node->children[i]; i++) { // search through the children of the first symbol
    tree_node_t* child = node->children[i];
    for(rule_t* rule = child->rules; rule->outcome; rule++) {
      if(rule->parents && rule->size == nsymbols) {
	unsigned int i = 0;
	for(i = 0; i < nsymbols && rule->parents[i]; i++) if(symbols[i].type != rule->parents[i]->outcome) break;
	if(!rule->parents[i])  return *rule;
      }
    }
  }
  return (rule_t){ 0 };
}


/* could_form() descends the grammar tree to see if the symbol start could be formed from the symbol end */
/* to do this it explores all the first paths [docs/could_form.svg] */
static unsigned char could_form(tree_node_t* start, unsigned int end) {
  tree_node_t* head = start;
  tree_node_t** return_stack = NULL;
  unsigned int ret_stack_s = 0, ret_stack_c = 0;
  while(head->outcome != end) {
    if(head->nrules > 1) { // add all the paths that remain to be explored for this node to the stack
      while(ret_stack_c <= ret_stack_s + head->nrules) return_stack = realloc(return_stack, (ret_stack_c + 10) * sizeof(tree_node_t*)), ret_stack_c += 10;
      for(unsigned int i = 0; i < head->nrules - 1; i++) {
	if(head->rules[i + 1].parents && head->rules[i + 1].parents[0]->outcome != head->outcome) {
	  return_stack[ret_stack_s++] = head->rules[i + 1].parents[0];
	}
      }
    }
    
    if(head->nrules == 0 || !head->rules[0].parents || head->rules->parents[0]->outcome == head->outcome) {
      if(!ret_stack_s) return 0; // if we have arrived to a terminal and we have no other paths to explore we can safely say
      //that it is not possible to form the symbol start from symbol end
      head = return_stack[ret_stack_s - 1], ret_stack_s--; // if the stack is not empty we should explore the remaining path
    }
    
    else head = head->rules[0].parents[0]; // move down the tree
  }
  return 1;
}

/* start_of_rule() returns whether if the sequence symbols and the the look ahead (nxtoken_type) form the start of a rule */
static unsigned char start_of_rule(khash_t(NODE_MAP)* nodemap, const symbol_t* symbols, unsigned int nsymbols, unsigned int nxtoken_type) { 
  tree_node_t* node = get_node_by_outcome(nodemap, symbols[0].type);
  for(unsigned int i = 0; node->children[i]; i++) {
    tree_node_t* child = node->children[i];
    for(rule_t* rule = child->rules; rule->outcome; rule++) {
      if(rule->parents && rule->size > nsymbols) {
    	unsigned int i = 0;
	for(i = 0; i < nsymbols && rule->parents[i] &&
	      rule->parents[i]->outcome == symbols[i].type; i++);
	if( could_form(rule->parents[i], nxtoken_type) && i == nsymbols )  return 1;
      }
    }
  }
  return 0;
}

/* nullable() returns the path to the first empty rule that forms the symbol node */
/* or NULL if there are none */
static rule_t* nullable(tree_node_t* node) {
  for(rule_t* rule = node->rules; rule->outcome; rule++ ) {
    if(!rule->parents) return rule;
  }
  return NULL;
}

/* infer_nullable() appends a nullable symbol to view if appropriate */
static symbol_t infer_nullable(khash_t(NODE_MAP)* nodemap, symbol_t* view, unsigned int view_size, symbol_t nxtoken) {
  tree_node_t* pnode = get_node_by_outcome(nodemap, view[0].type);
  if(!pnode || !pnode->children[0]) return (symbol_t){ 0 };
  for(unsigned int i = 0; pnode->children[i]; i++) {
    tree_node_t* child = pnode->children[i];
    for(rule_t* rule = child->rules; rule->outcome; rule++) {
      
      if(rule->size - 1 >= view_size && rule->parents && rule->parents[0]->outcome == view[0].type) {
	rule_t* nnode = nullable(rule->parents[view_size]);
	if( (rule->size - 1 == view_size && nnode && !start_of_rule(nodemap, view, view_size, nxtoken.type))
	    || (rule->size - 1 > view_size && nnode && could_form(rule->parents[view_size + 1], nxtoken.type) && !start_of_rule(nodemap, view, view_size, nxtoken.type)) ) {
	    symbol_t inf_token = { 0 };
	    if(nnode->function) inf_token = nnode->function(view + view_size); 
	    return (symbol_t){ nnode->outcome, inf_token.dsize, inf_token.data };
	}
      }
    }
  }
  return (symbol_t){ 0 };
}

/*
  tree_node_t* pnode = get_node_by_outcome(nodemap, nxtoken.type);
  if(!pnode || !pnode->children[0]) return (symbol_t){ 0 };
  for(unsigned int i = 0; pnode->children[i]; i++) {
  tree_node_t* child = pnode->children[i];
  for(rule_t* rule = child->rules; rule->outcome; rule++) {     
  if(rule->size > 1 && rule->parents[1]->outcome == nxtoken.type) {
  rule_t* nnode = nullable(rule->parents[0]);
  if(nnode) {
  symbol_t inf_token = { 0 };
  if(nnode->function) inf_token = nnode->function(NULL); 
  return (symbol_t){ nnode->outcome, inf_token.dsize, inf_token.data };
  }
  }
  }
  }
  return (symbol_t){ 0 };
*/

static symbol_t infer_nullable_end(khash_t(NODE_MAP)* nodemap, symbol_t nxtoken) {
  tree_node_t* head = get_node_by_outcome(nodemap, nxtoken.type);
  tree_node_t** return_stack = NULL;
  unsigned int ret_stack_s = 0, ret_stack_c = 0;
  while(head && head->children[0] && head->children[0]->outcome != head->outcome) {
    for(unsigned int i = 0; head->children[i]; i++) {
      tree_node_t* child = head->children[i];
      for(rule_t* rule = child->rules; rule->outcome; rule++) {     
	if(rule->size > 1 && rule->parents[1]->outcome == head->outcome) {
	  rule_t* nnode = nullable(rule->parents[0]);
	  if(nnode) {
	    symbol_t inf_token = { 0 };
	    if(nnode->function) inf_token = nnode->function(NULL); 
	    return (symbol_t){ nnode->outcome, inf_token.dsize, inf_token.data };
	  }
	}
      }
    }
    
    if(head->nrules > 1) { // add all the paths that remain to be explored for this node to the stack
      while(ret_stack_c <= ret_stack_s + head->nrules) return_stack = realloc(return_stack, (ret_stack_c + 10) * sizeof(tree_node_t*)), ret_stack_c += 10;
      for(unsigned int i = 0; i < head->nrules - 1; i++) {
	if(head->rules[i + 1].parents[0]->outcome != head->outcome) {
	  return_stack[ret_stack_s++] = head->rules[i + 1].parents[0];
	}
      }
    }

    head = head->children[0];
  }
  return (symbol_t){ 0 };
}

/* reduce() will attempt to reduce any rules it can in view */
/* it will not do anything in the case of a Shift/Reduce conflict */
static void reduce(khash_t(NODE_MAP)* nodemap, symbol_t* view, unsigned int* view_size, symbol_t nxtoken) {

  for(unsigned int k = 0; k < *view_size; k++) {

    symbol_t inf_token = infer_nullable(nodemap, view + k, *view_size - k, nxtoken);
    if(inf_token.type) {
      view[*view_size] = inf_token;
      (*view_size)++;
    }
       
    if(start_of_rule(nodemap, view + k, *view_size - k, nxtoken.type)) return; // detect S/R conflicts
    
    rule_t rule = get_rule(nodemap, view + k, *view_size - k);
    
    if(rule.outcome != '\0')  { // view + k is reduceable
        
      symbol_t nnterm = { 0 };
      
      if(rule.function) nnterm = rule.function(view + k);
	  
#ifdef REDUCE_HOOK_ON
      reduce_hook((symbol_t){ rule.outcome, nnterm.dsize, nnterm.data }, view + k, *view_size - k);
#endif
	  
      for(unsigned int i = 0; i < *view_size - k; i++) {
	free(view[k + i].data);
      }
      
      view[k] = (symbol_t){ rule.outcome, nnterm.dsize, nnterm.data };
      *view_size = k + 1;
      k = UINT_MAX; // so that it returns to 0 after iterating
	  
#if PARSE_VERBOSE
      printf("view_size = %d\ntokens : ", *view_size);
      for(unsigned int u = 0; u < *view_size; u++) {
	printf("%d ", view[u].type);
      }
      printf("\n");
#endif
    }
  }

  symbol_t inf_token = infer_nullable_end(nodemap, nxtoken);
  if(inf_token.type) {
    view[*view_size] = inf_token;
    (*view_size)++;
  }
  
  return;
}

void p_parse(rule_def_t* rules, void* input, symbol_t (*p_lex)(void*) ) {
#ifdef INIT_HOOK_ON
  init_hook();
#endif
    
  khash_t(NODE_MAP) * nodemap = kh_init(NODE_MAP); 
  tree gr_tree = gen_gr_tree(nodemap, rules);

  unsigned int  view_size = 0, view_capacity = 10;
  symbol_t*     view      = malloc(view_capacity * sizeof(symbol_t));
  
  symbol_t ctoken  = p_lex(input) , nxtoken = p_lex(input);

  symbol_t inf_token = infer_nullable_end(nodemap, ctoken);
  if(inf_token.type) {
    view[view_size] = inf_token;
    view_size++;
  }
  
  while(ctoken.type != '\0') {
    
    if(view_size == view_capacity) {
      view_capacity += view_capacity + 10;
      view = realloc(view, view_capacity * sizeof(symbol_t));
    }
    view[view_size] = ctoken;
    view_size++;
        
#ifdef PARSE_VERBOSE
    printf("tokens : ");
    for(unsigned int u = 0; u < view_size; u++) {
      printf("%d ", view[u].type);
    }
    printf("\n"); 
#endif
    
    reduce(nodemap, view, &view_size, nxtoken);
   
    ctoken = nxtoken;
    nxtoken = p_lex(input);
  }
  
  for(unsigned int i = 0; i < view_size; i++) {
    free(view[i].data);
  }
  free(view);

  free_gr_tree(gr_tree);
  free(gr_tree.val);
  kh_destroy(NODE_MAP, nodemap);
#ifdef CLOSE_HOOK_ON
  close_hook();
#endif
}
