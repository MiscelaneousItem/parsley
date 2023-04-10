
#define _GNU_SOURCE // for asprintf
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parsley_grammar.h"
#include "yacc.h"

#define NUM_LEN 5

  extern FILE* outf[2];
  char* nterms_s, *current_dec;
  unsigned int nterms_s_size = 100;
  unsigned int nsymbols = 0;

  void init_hook(void) {
    nterms_s = calloc(nterms_s_size, 1);
    strcpy(nterms_s, "rule_def_t gr_rules[] = {\n");
  }
  void close_hook(void) {
    fprintf(outf[0], nterms_s);
    fprintf(outf[0], "{ 0 }\n};\n");
    free(nterms_s);
    free(current_dec);
  }

symbol_t c_zone__TOKEN_C_ZONE(symbol_t* symbols){
 fprintf(outf[0], (char*)symbols[0].data); return (symbol_t){ 0 }; 
}

symbol_t ntdec__TOKEN_ALPHA_058(symbol_t* symbols){

  free(current_dec);
  current_dec = calloc(symbols->dsize + 1, 1);
  strncpy(current_dec, symbols->data, symbols->dsize);
  fprintf(outf[1], "#define %s %i\n", current_dec, 256 + nsymbols);
  nsymbols++;
  return (symbol_t){ ntdec, 0, NULL }; 
 
}

symbol_t rule_body__alpha_list(symbol_t* symbols){

    for(u_int16_t i = 0; i < symbols[0].dsize; i++) {
    if( ((char*)symbols[0].data)[i] == ' ') ((char*)symbols[0].data)[i] = ','; 
  }
  
  char* rule_definition;
  asprintf(&rule_definition, "{ %s, (unsigned int[]){ %s, 0 }, NULL },\n", current_dec, (char*)symbols[0].data);

  while(strlen(nterms_s) +
	strlen(rule_definition) >= nterms_s_size) nterms_s = realloc(nterms_s, nterms_s_size *= 2); 
  strcat(nterms_s, rule_definition);
  
  free(rule_definition);
  
  return (symbol_t){ rule, 0, NULL };
 
}

symbol_t rule_body__alpha_list_TOKEN_C_FUNCTION(symbol_t* symbols){

    char* buffer = calloc(symbols[0].dsize + 1, 1);
  memcpy(buffer, symbols[0].data, symbols[0].dsize);
  for(u_int16_t i = 0; i < symbols[0].dsize; i++) {
    if(buffer[i] == ' ') buffer[i] = '_';
    if(buffer[i] == '\'') {
      if(buffer[i+1] == '\\') fprintf(stderr, "please do no use escape sequences as symbols\n"), exit(1);
      char* num_buff;
      asprintf(&num_buff, "%d", buffer[i+1]);
      if(((unsigned char)buffer[i+1]) < 100) {
	buffer[i] = '0';
	i++;
      }
      memcpy(buffer + i, num_buff, strlen(num_buff)); // strlen() allows to cut the EOF
      i++;
    }
  }
  char* rule_function_name;
  asprintf(&rule_function_name, "%s__%s", current_dec, buffer);
  free(buffer);

  char* rule_function;
  asprintf(&rule_function, "symbol_t %s(symbol_t* symbols){\n%s\n}\n", rule_function_name, (char*)symbols[1].data);
  
  buffer = calloc(symbols[0].dsize + 1, 1);
  memcpy(buffer, symbols[0].data, symbols[0].dsize);
  for(u_int16_t i = 0; i < symbols[0].dsize; i++) {
    if(buffer[i] == ' ') buffer[i] = ','; 
  }
  
  char* rule_definition;
  asprintf(&rule_definition, "{ %s, (unsigned int[]){ %s, 0 }, %s },\n", current_dec, buffer, rule_function_name);
  
  free(buffer);

  fprintf(outf[0], "%s\n", rule_function);

  while(strlen(nterms_s) + strlen(rule_definition) >= nterms_s_size) nterms_s = realloc(nterms_s, nterms_s_size *= 2); 
  strcat(nterms_s, rule_definition);
  
  free(rule_function_name);
  free(rule_definition);
  free(rule_function);
  
  return (symbol_t){ rule, 0, NULL };
 
}

symbol_t rule_body__empty(symbol_t* symbols){

  char* rule_definition;
  asprintf(&rule_definition, "{ %s, NULL, NULL },\n", current_dec);
  
  while(strlen(nterms_s) + strlen(rule_definition) >= nterms_s_size) nterms_s = realloc(nterms_s, nterms_s_size *= 2); 
  strcat(nterms_s, rule_definition);
  
  free(rule_definition);
  
  return (symbol_t){ rule, 0, NULL };

 
}

symbol_t rule_body__TOKEN_C_FUNCTION(symbol_t* symbols){

  char* rule_function_name;
  asprintf(&rule_function_name, "%s__empty", current_dec);

  char* rule_definition;
  asprintf(&rule_definition, "{ %s, NULL, %s },\n", current_dec, rule_function_name);

  while(strlen(nterms_s) + strlen(rule_definition) >= nterms_s_size) nterms_s = realloc(nterms_s, nterms_s_size *= 2); 
  strcat(nterms_s, rule_definition);
  
  free(rule_definition);

  char* rule_function;
  asprintf(&rule_function, "symbol_t %s(symbol_t* symbols){\n%s\n}\n", rule_function_name, (char*)symbols[0].data);
  
  fprintf(outf[0], "%s\n", rule_function);

  free(rule_function_name);
  free(rule_function);
  return (symbol_t){ rule, 0, NULL };
 
}

symbol_t alpha_list__TOKEN_ALPHA(symbol_t* symbols){
 char* buffer = malloc(symbols->dsize); strcpy(buffer, symbols->data); return (symbol_t){ alpha_list, symbols->dsize, buffer }; 
}

symbol_t alpha_list__alpha_list_TOKEN_ALPHA(symbol_t* symbols){

  char* buffer = calloc(symbols[0].dsize + symbols[1].dsize, 1);
  strncpy(buffer, symbols[0].data, symbols[0].dsize);
  buffer[strlen(buffer)] = ' ';
  strncat(buffer, symbols[1].data, symbols[1].dsize);
  return (symbol_t){ alpha_list, strlen(buffer) + 1, buffer };
 
}

symbol_t token_def__037_TOKEN_TOK_TOKEN_ALPHA(symbol_t* symbols){

  fprintf(outf[1], "#define %s %d\n", (char*)symbols[2].data, nsymbols + 256);
  nsymbols++;
  return (symbol_t){ token_def, 0, NULL };

 
}

symbol_t token_def__token_def_TOKEN_ALPHA(symbol_t* symbols){

  fprintf(outf[1], "#define %s %d\n", (char*)symbols[1].data, nsymbols + 256);  
  nsymbols++;
  return (symbol_t){ token_def, 0, NULL };

}

rule_def_t gr_rules[] = {
{ root, (unsigned int[]){ c_zone,token_def,'%','%',ntdef_list,'%','%', 0 }, NULL },
{ c_zone, (unsigned int[]){ TOKEN_C_ZONE, 0 }, c_zone__TOKEN_C_ZONE },
{ ntdec, (unsigned int[]){ TOKEN_ALPHA,':', 0 }, ntdec__TOKEN_ALPHA_058 },
{ ntdef_list, (unsigned int[]){ ntdef, 0 }, NULL },
{ ntdef_list, (unsigned int[]){ ntdef_list,ntdef, 0 }, NULL },
{ ntdef, (unsigned int[]){ ntdec,rule_list, 0 }, NULL },
{ rule_list, (unsigned int[]){ end_rule, 0 }, NULL },
{ rule_list, (unsigned int[]){ rule,rule_list, 0 }, NULL },
{ rule, (unsigned int[]){ rule_body,'|', 0 }, NULL },
{ end_rule, (unsigned int[]){ rule_body,';', 0 }, NULL },
{ rule_body, (unsigned int[]){ alpha_list, 0 }, rule_body__alpha_list },
{ rule_body, (unsigned int[]){ alpha_list,TOKEN_C_FUNCTION, 0 }, rule_body__alpha_list_TOKEN_C_FUNCTION },
{ rule_body, NULL, rule_body__empty },
{ rule_body, (unsigned int[]){ TOKEN_C_FUNCTION, 0 }, rule_body__TOKEN_C_FUNCTION },
{ alpha_list, (unsigned int[]){ TOKEN_ALPHA, 0 }, alpha_list__TOKEN_ALPHA },
{ alpha_list, (unsigned int[]){ alpha_list,TOKEN_ALPHA, 0 }, alpha_list__alpha_list_TOKEN_ALPHA },
{ token_def_list, (unsigned int[]){ token_def, 0 }, NULL },
{ token_def_list, (unsigned int[]){ token_def_list,token_def, 0 }, NULL },
{ token_def, (unsigned int[]){ '%',TOKEN_TOK,TOKEN_ALPHA, 0 }, token_def__037_TOKEN_TOK_TOKEN_ALPHA },
{ token_def, (unsigned int[]){ token_def,TOKEN_ALPHA, 0 }, token_def__token_def_TOKEN_ALPHA },
{ empty, NULL, NULL },
{ 0 }
};
