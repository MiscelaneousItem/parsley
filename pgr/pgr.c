#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parsley.h"

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

FILE* outf[2];

int main(int argc, char** argv) {
      
  if(argc < 1) fprintf(stderr, "insufficient input\n"), exit(1);
    
  char* code = open_file(argv[1]);
    
  char* buffer;
  asprintf(&buffer, "%s.c", argv[2]);
  outf[0] = fopen(buffer, "w");
  free(buffer);
  
  asprintf(&buffer, "%s.h", argv[2]);
  outf[1] = fopen(buffer, "w");
  free(buffer);
  
  p_parse(code);
  
  fclose(outf[0]);
  fclose(outf[1]);
  free(code);

  return 0;
}
