#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parsley.h"
#include "parsley_grammar.h"
symbol_t p_lex(void* input);


char* open_file(char* filepath) { // returns a char* containing the contents of a file
  char* buffer;
  
  FILE* fp = fopen ( filepath , "r" );
  if( !fp ) perror(filepath), exit(1);

  fseek( fp , 0L , SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  buffer = calloc(size + 1, sizeof(char));
  fread(buffer, size, 1, fp);
  fclose(fp);

  return buffer;
} 

int main() {
  char* input = open_file("../pgr/yacc.yacc");
  for(int i = 0; i < NRUNS; i++) {
    p_parse(gr_rules, input, p_lex);
  }
  free(input);
  return 0;
}
