#define _GNU_SOURCE // for asprintf
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parsley_grammar.h"
#include "case.h"

rule_def_t gr_rules[] = {
  { root,           (unsigned int[]){ c_zone,token_def_list,'%','%',ntdef_list,'%','%', 0 }, NULL                                 }, // 0
  { c_zone,         (unsigned int[]){ TOKEN_C_ZONE,                                     0 }, NULL                 }, // 1
  { ntdec,          (unsigned int[]){ TOKEN_ALPHA,':',                                  0 }, NULL               }, // 2
  { ntdef_list,     (unsigned int[]){ ntdef,                                            0 }, NULL                                 }, // 3
  { ntdef_list,     (unsigned int[]){ ntdef_list, ntdef,                                0 }, NULL                                 }, // 4
  { ntdef,          (unsigned int[]){ ntdec, rule_list,                                 0 }, NULL                                 }, // 5
  { rule_list,      (unsigned int[]){ end_rule,                                         0 }, NULL                                 }, // 6
  { rule_list,      (unsigned int[]){ rule, rule_list,                                  0 }, NULL                                 }, // 7
  { rule,           (unsigned int[]){ rule_body, '|',                                   0 }, NULL                                 },
  { end_rule,       (unsigned int[]){ rule_body, ';',                                   0 }, NULL                                 },
  { rule_body,      (unsigned int[]){ alpha_list,                                       0 }, NULL                     }, // 8
  { rule_body,      (unsigned int[]){ alpha_list, TOKEN_C_FUNCTION,                     0 }, NULL    }, // 9
  { rule_body,      NULL,                                                                    NULL                         }, // 8
  { rule_body,      (unsigned int[]){ TOKEN_C_FUNCTION,                                 0 }, NULL               }, // 9
  { alpha_list,     (unsigned int[]){ TOKEN_ALPHA,                                      0 }, NULL              }, // 10
  { alpha_list,     (unsigned int[]){ alpha_list,TOKEN_ALPHA,                           0 }, NULL   }, // 11
  { token_def_list, (unsigned int[]){ token_def,                                        0 }, NULL                                 }, // 12
  { token_def_list, (unsigned int[]){ token_def_list,token_def,                         0 }, NULL                                 }, // 13
  { token_def,      (unsigned int[]){ '%',TOKEN_TOK,TOKEN_ALPHA,                        0 }, NULL }, // 14
  { token_def,      (unsigned int[]){ token_def, TOKEN_ALPHA,                           0 }, NULL     }, // 15
  { 0 }
};
