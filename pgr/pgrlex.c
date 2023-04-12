#include "parsley_grammar.h"
#include "yacc.ref.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static char isin(char a, char* b) {
  unsigned int i = 0;
  while(b[i] != '\0') {
    if(a == b[i]) return 1;
    i++;
  }
  return 0;
}

static char seq2(char* in, char* cmp) {
  if(in[0] == cmp[0] && in[1] == cmp[1]) return 1;
  return 0;
}

symbol_t pgrlex(void* input) {
  char* code_input = input;
  if(!code_input) return (symbol_t){ 0 };

  static unsigned int i = 0;
  unsigned int j = 0;
  char* buffer = calloc(65, 1);
   
  while( ( isin(code_input[i], " \n\t") || seq2(code_input + i, "//") || seq2(code_input + i, "/*") ) && code_input[i] != '\0') { // get to the first non space/newline/tab character
    
    if(seq2(code_input + i, "/*")) {
      while(!seq2(code_input + i, "*/") && code_input[i] != '\0') {
	i++;
      }
      i++;
    }
  
    if(seq2(code_input + i, "//")) {
      while(code_input[i] != '\n' && code_input[i] != '\0') {
	i++;
      }
    }
    
    i++;
  }

  while(code_input[i] != '\0') {
    if((isin(code_input[i], " \n\t:;|{%'") || seq2(code_input + i, "//") || seq2(code_input + i, "/*") || code_input[i] == '\0')) {
      if(isin(code_input[i], ":;|{%'") && j == 0) {
	char c = code_input[i];
#ifdef LEX_VERBOSE
	printf("char : %c\n", (char)c);
#endif
	i++;
	free(buffer);
	if( (c != '%'  && c != '{' && c != '\'') || (c == '%' && code_input[i] != '{')) return (symbol_t){ c,   0, NULL };

	// char handling ('x')
	if(c == '\'') {
	  buffer = calloc(64, 1);
	  buffer[0] = '\'';
	  j++;
	  while(code_input[i] != '\'' && code_input[i] != '\0') {
	    buffer[j] = code_input[i];
	    i++;
	    j++;
	    buffer[j] = code_input[i];
	   }
	  i++;
	  return (symbol_t){ TOKEN_ALPHA, strlen(buffer) + 1, buffer };
	}
	// code zone handling
	unsigned int zone_size = 100, paren_open = 1, in_string = 0, in_char = 0;
	char* code_zone = calloc(zone_size, 1);
	
	if(code_input[i] == '{') i++; // handling for %{ code zone openings
	
	while(code_input[i] != '\0' && paren_open) {

	  if(strlen(code_zone) == zone_size - 1) {
	    code_zone = realloc(code_zone, zone_size + 100);
	    memset(code_zone + zone_size, '\0', 100);
	    zone_size += 100;
	  }
	  code_zone[strlen(code_zone)] = code_input[i];
	  i++;
	  if(code_input[i] == '\\' && (in_char || in_string)) {
	    if(strlen(code_zone) == zone_size - 1) {
	      code_zone = realloc(code_zone, zone_size + 100);
	      memset(code_zone + zone_size, '\0', 100);
	      zone_size += 100;
	    }
	    code_zone[strlen(code_zone)] = code_input[i];
	    i++;
	  }
	  else if(code_input[i] == '\'') in_char = !in_char;
	  else if(code_input[i] == '"') in_string = !in_string;
	  else if(!in_char && !in_string && c == '%' && code_input[i] == '%' && code_input[i+1] == '}') { // %{ opening
	    i++;
	    break;
	  }
	  else if(!in_char && !in_string) {                                                          // { opening
	    if(code_input[i] == '{') paren_open++;
	    else if(code_input[i] == '}') paren_open--;
	  }
	    
	}
	i++;
#ifdef LEX_VERBOSE
	printf("code_zone : %s\n", code_zone);
#endif
	if(c == '%') return (symbol_t){ TOKEN_C_ZONE, strlen(code_zone) + 1, code_zone };
	else return (symbol_t){ TOKEN_C_FUNCTION, strlen(code_zone) + 1, code_zone };
      }
#ifdef LEX_VERBOSE
      printf("buffer : %s\n", buffer);
#endif
      
      if(strcmp(buffer, "token") == 0) {
	free(buffer);
	return (symbol_t){ TOKEN_TOK, 0, NULL };
      }
      return (symbol_t){ TOKEN_ALPHA, strlen(buffer) + 1, buffer };
      
    }
    buffer[j] = code_input[i];
    j++;
    i++;
  }
  free(buffer);
  
  return (symbol_t){ 0 };
}
