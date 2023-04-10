PARSLEY_PATH   = $(HOME)/c/parsley

CORE_FILES    = $(PARSLEY_PATH)/src/parsley.c
CORE_DEPS     = $(PARSLEY_PATH)/pgr/makefile $(PARSLEY_PATH)/src/parsley_grammar.h $(PARSLEY_PATH)/src/parsley_lex.h
CORE_FLAGS    = -g -Wall -I $(PARSLEY_PATH)/src/

CC          = gcc

PGR_FILES    = $(PARSLEY_PATH)/pgr/pgr.c $(PARSLEY_PATH)/pgr/pgrlex.c

YACC_FILES   = $(PARSLEY_PATH)/pgr/yacc.c 
YACC_DEPS    = $(PARSLEY_PATH)/pgr/yacc.yacc $(PARSLEY_PATH)/pgr/yacc.h



REF_FILES    = $(PARSLEY_PATH)/pgr/yacc.ref.c
REF_DEPS     = $(PARSLEY_PATH)/pgr/yacc.ref.h

YACC_FLAGS   = -D INIT_HOOK_ON -D CLOSE_HOOK_ON
DEBUG_FLAGS  = -D PARSE_VERBOSE -D LEX_VERBOSE


debug: $(CORE_FILES) $(PGR_FILES) $(CORE_DEPS) $(YACC_DEPS)
	$(CC) $(CORE_FILES) $(PGR_FILES) $(YACC_FILES) $(CORE_FLAGS) $(DEBUG_FLAGS) $(YACC_FLAGS) -o pgr

release: $(CORE_FILES) $(PGR_FILES) $(YACC_FILES) $(CORE_DEPS) $(YACC_DEPS)
	./pgr yacc.yacc yacc
	$(CC) $(CORE_FILES) $(PGR_FILES) $(YACC_FILES) $(CORE_FLAGS) $(YACC_FLAGS) -o pgr

restore: $(CORE_FILES) $(PGR_FILES) $(REF_FILES) $(CORE_DEPS) $(REF_DEPS)
	$(CC) $(CORE_FILES) $(PGR_FILES) $(REF_FILES) $(CORE_FLAGS) $(YACC_FLAGS) $(DEBUG_FLAGS) -o restored
