
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "parser.h"

static Ast * ast_reduce (Allocator * alloc, int sym, Ast ** children, int n);
#define DEFAULT_ACTION(yyn)					\
  yyval = ast_reduce ((Allocator *)parse->alloc, yyr1[yyn], yyvsp, yyr2[yyn])
static int yyparse (AstRoot * parse, Ast * root);
symbol_t translation_unit__translation_unit_error_059(symbol_t* symbols){
 $2->sym = YYSYMBOL_YYerror; 
}

symbol_t translation_unit__translation_unit_error_125(symbol_t* symbols){
 $2->sym = YYSYMBOL_YYerror; 
}

symbol_t translation_unit__translation_unit_error_041(symbol_t* symbols){
 $2->sym = YYSYMBOL_YYerror; 
}

symbol_t expression_error__error(symbol_t* symbols){
 $1->sym = YYSYMBOL_YYerror; 
}

symbol_t declaration__declaration_specifiers_059_type_not_specified(symbol_t* symbols){
 ast_push_declaration (parse->stack, $$); 
}

symbol_t declaration__declaration_specifiers_init_declarator_list_059_type_not_specified(symbol_t* symbols){
 ast_push_declaration (parse->stack, $$); 
}

symbol_t type_specifier__types(symbol_t* symbols){
 parse->type_already_specified = true; 
}

symbol_t struct_or_union_specifier__struct_or_union_123_error_125(symbol_t* symbols){
 $3->sym = YYSYMBOL_YYerror; 
}

symbol_t struct_or_union_specifier__struct_or_union_generic_identifier_123_error_125(symbol_t* symbols){
 $4->sym = YYSYMBOL_YYerror; 
}

symbol_t direct_declarator__direct_declarator_040_type_not_specified_error_041(symbol_t* symbols){
 $4->sym = YYSYMBOL_YYerror; 
}

symbol_t type_not_specified__empty(symbol_t* symbols){
 parse->type_already_specified = false; 
}

symbol_t statement__error_059(symbol_t* symbols){
 $1->sym = YYSYMBOL_YYerror; 
}

symbol_t for_scope__FOR(symbol_t* symbols){
 stack_push (parse->stack, &($$)); 
}

symbol_t iteration_statement__for_scope_040_expression_statement_expression_statement_041_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1); 
}

symbol_t iteration_statement__for_scope_040_expression_statement_expression_statement_expression_041_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1); 
}

symbol_t for_declaration_statement__for_scope_040_declaration_expression_statement_041_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1); 
}

symbol_t for_declaration_statement__for_scope_040_declaration_expression_statement_expression_041_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1); 
}

symbol_t external_declaration__error_compound_statement(symbol_t* symbols){
 $1->sym = YYSYMBOL_YYerror; 
}

symbol_t function_declaration__declaration_specifiers_declarator(symbol_t* symbols){
 ast_push_function_definition (parse->stack, $2);  
}

symbol_t function_definition__function_declaration_declaration_list_compound_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1->child[1]); 
}

symbol_t function_definition__function_declaration_compound_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1->child[1]); 
}

symbol_t forin_declaration_statement__for_scope_040_declaration_specifiers_declarator_IDENTIFIER_forin_arguments_041_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1); 
}

symbol_t forin_statement__for_scope_040_expression_IDENTIFIER_forin_arguments_041_statement(symbol_t* symbols){
 ast_pop_scope (parse->stack, $1); 
}

symbol_t root__translation_unit(symbol_t* symbols){

	  $$ = root;
	  $$->sym = yyr1[yyn];
	  $$->child = allocate ((Allocator *)parse->alloc, 2*sizeof(Ast *));
	  $$->child[0] = $1;
	  $1->parent = $$;
	  $$->child[1] = NULL;
        
}

rule_def_t gr_rules[] = {
{ translation_unit, (unsigned int[]){ external_declaration, 0 }, NULL },
{ translation_unit, (unsigned int[]){ translation_unit,external_declaration, 0 }, NULL },
{ translation_unit, (unsigned int[]){ translation_unit,error,';', 0 }, translation_unit__translation_unit_error_059 },
{ translation_unit, (unsigned int[]){ translation_unit,error,'}', 0 }, translation_unit__translation_unit_error_125 },
{ translation_unit, (unsigned int[]){ translation_unit,error,')', 0 }, translation_unit__translation_unit_error_041 },
{ primary_expression, (unsigned int[]){ IDENTIFIER, 0 }, NULL },
{ primary_expression, (unsigned int[]){ constant, 0 }, NULL },
{ primary_expression, (unsigned int[]){ string, 0 }, NULL },
{ primary_expression, (unsigned int[]){ '(',expression_error,')', 0 }, NULL },
{ primary_expression, (unsigned int[]){ generic_selection, 0 }, NULL },
{ expression_error, (unsigned int[]){ expression, 0 }, NULL },
{ expression_error, (unsigned int[]){ error, 0 }, expression_error__error },
{ constant, (unsigned int[]){ I_CONSTANT, 0 }, NULL },
{ constant, (unsigned int[]){ F_CONSTANT, 0 }, NULL },
{ constant, (unsigned int[]){ ENUMERATION_CONSTANT, 0 }, NULL },
{ enumeration_constant, (unsigned int[]){ IDENTIFIER, 0 }, NULL },
{ string, (unsigned int[]){ STRING_LITERAL, 0 }, NULL },
{ string, (unsigned int[]){ FUNC_NAME, 0 }, NULL },
{ generic_selection, (unsigned int[]){ GENERIC,'(',assignment_expression,',',generic_assoc_list,')', 0 }, NULL },
{ generic_assoc_list, (unsigned int[]){ generic_association, 0 }, NULL },
{ generic_assoc_list, (unsigned int[]){ generic_assoc_list,',',generic_association, 0 }, NULL },
{ generic_association, (unsigned int[]){ type_name,':',assignment_expression, 0 }, NULL },
{ generic_association, (unsigned int[]){ DEFAULT,':',assignment_expression, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ primary_expression, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ function_call, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ array_access, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ postfix_expression,'.',member_identifier, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ postfix_expression,PTR_OP,member_identifier, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ postfix_expression,INC_OP, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ postfix_expression,DEC_OP, 0 }, NULL },
{ postfix_expression, (unsigned int[]){ '(',type_name,')',postfix_initializer, 0 }, NULL },
{ postfix_initializer, (unsigned int[]){ '{',initializer_list,'}', 0 }, NULL },
{ postfix_initializer, (unsigned int[]){ '{',initializer_list,',','}', 0 }, NULL },
{ array_access, (unsigned int[]){ postfix_expression,'[',']', 0 }, NULL },
{ array_access, (unsigned int[]){ postfix_expression,'[',expression,']', 0 }, NULL },
{ function_call, (unsigned int[]){ postfix_expression,'(',')', 0 }, NULL },
{ function_call, (unsigned int[]){ postfix_expression,'(',argument_expression_list,')', 0 }, NULL },
{ member_identifier, (unsigned int[]){ generic_identifier, 0 }, NULL },
{ argument_expression_list, (unsigned int[]){ argument_expression_list_item, 0 }, NULL },
{ argument_expression_list, (unsigned int[]){ argument_expression_list,',',argument_expression_list_item, 0 }, NULL },
{ argument_expression_list, (unsigned int[]){ argument_expression_list,',', 0 }, NULL },
{ argument_expression_list_item, (unsigned int[]){ assignment_expression, 0 }, NULL },
{ argument_expression_list_item, (unsigned int[]){ postfix_initializer, 0 }, NULL },
{ unary_expression, (unsigned int[]){ postfix_expression, 0 }, NULL },
{ unary_expression, (unsigned int[]){ INC_OP,unary_expression, 0 }, NULL },
{ unary_expression, (unsigned int[]){ DEC_OP,unary_expression, 0 }, NULL },
{ unary_expression, (unsigned int[]){ unary_operator,cast_expression, 0 }, NULL },
{ unary_expression, (unsigned int[]){ SIZEOF,unary_expression, 0 }, NULL },
{ unary_expression, (unsigned int[]){ SIZEOF,'(',type_name,')', 0 }, NULL },
{ unary_expression, (unsigned int[]){ ALIGNOF,'(',type_name,')', 0 }, NULL },
{ unary_expression, (unsigned int[]){ NEW_FIELD, 0 }, NULL },
{ unary_expression, (unsigned int[]){ NEW_FIELD,'[',postfix_expression,']', 0 }, NULL },
{ unary_operator, (unsigned int[]){ '&', 0 }, NULL },
{ unary_operator, (unsigned int[]){ '*', 0 }, NULL },
{ unary_operator, (unsigned int[]){ '+', 0 }, NULL },
{ unary_operator, (unsigned int[]){ '-', 0 }, NULL },
{ unary_operator, (unsigned int[]){ '~', 0 }, NULL },
{ unary_operator, (unsigned int[]){ '!', 0 }, NULL },
{ cast_expression, (unsigned int[]){ unary_expression, 0 }, NULL },
{ cast_expression, (unsigned int[]){ '(',type_name,')',cast_expression, 0 }, NULL },
{ multiplicative_expression, (unsigned int[]){ cast_expression, 0 }, NULL },
{ multiplicative_expression, (unsigned int[]){ multiplicative_expression,'*',cast_expression, 0 }, NULL },
{ multiplicative_expression, (unsigned int[]){ multiplicative_expression,'/',cast_expression, 0 }, NULL },
{ multiplicative_expression, (unsigned int[]){ multiplicative_expression,'%',cast_expression, 0 }, NULL },
{ additive_expression, (unsigned int[]){ multiplicative_expression, 0 }, NULL },
{ additive_expression, (unsigned int[]){ additive_expression,'+',multiplicative_expression, 0 }, NULL },
{ additive_expression, (unsigned int[]){ additive_expression,'-',multiplicative_expression, 0 }, NULL },
{ shift_expression, (unsigned int[]){ additive_expression, 0 }, NULL },
{ shift_expression, (unsigned int[]){ shift_expression,LEFT_OP,additive_expression, 0 }, NULL },
{ shift_expression, (unsigned int[]){ shift_expression,RIGHT_OP,additive_expression, 0 }, NULL },
{ relational_expression, (unsigned int[]){ shift_expression, 0 }, NULL },
{ relational_expression, (unsigned int[]){ relational_expression,'<',shift_expression, 0 }, NULL },
{ relational_expression, (unsigned int[]){ relational_expression,'>',shift_expression, 0 }, NULL },
{ relational_expression, (unsigned int[]){ relational_expression,LE_OP,shift_expression, 0 }, NULL },
{ relational_expression, (unsigned int[]){ relational_expression,GE_OP,shift_expression, 0 }, NULL },
{ equality_expression, (unsigned int[]){ relational_expression, 0 }, NULL },
{ equality_expression, (unsigned int[]){ equality_expression,EQ_OP,relational_expression, 0 }, NULL },
{ equality_expression, (unsigned int[]){ equality_expression,NE_OP,relational_expression, 0 }, NULL },
{ and_expression, (unsigned int[]){ equality_expression, 0 }, NULL },
{ and_expression, (unsigned int[]){ and_expression,'&',equality_expression, 0 }, NULL },
{ exclusive_or_expression, (unsigned int[]){ and_expression, 0 }, NULL },
{ exclusive_or_expression, (unsigned int[]){ exclusive_or_expression,'^',and_expression, 0 }, NULL },
{ inclusive_or_expression, (unsigned int[]){ exclusive_or_expression, 0 }, NULL },
{ inclusive_or_expression, (unsigned int[]){ inclusive_or_expression,'|',exclusive_or_expression, 0 }, NULL },
{ logical_and_expression, (unsigned int[]){ inclusive_or_expression, 0 }, NULL },
{ logical_and_expression, (unsigned int[]){ logical_and_expression,AND_OP,inclusive_or_expression, 0 }, NULL },
{ logical_or_expression, (unsigned int[]){ logical_and_expression, 0 }, NULL },
{ logical_or_expression, (unsigned int[]){ logical_or_expression,OR_OP,logical_and_expression, 0 }, NULL },
{ conditional_expression, (unsigned int[]){ logical_or_expression, 0 }, NULL },
{ conditional_expression, (unsigned int[]){ logical_or_expression,'?',expression,':',conditional_expression, 0 }, NULL },
{ assignment_expression, (unsigned int[]){ conditional_expression, 0 }, NULL },
{ assignment_expression, (unsigned int[]){ unary_expression,assignment_operator,assignment_expression, 0 }, NULL },
{ assignment_expression, (unsigned int[]){ unary_expression,assignment_operator,postfix_initializer, 0 }, NULL },
{ assignment_expression, (unsigned int[]){ TYPEDEF_NAME,assignment_operator,assignment_expression, 0 }, NULL },
{ assignment_expression, (unsigned int[]){ TYPEDEF_NAME,assignment_operator,postfix_initializer, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ '=', 0 }, NULL },
{ assignment_operator, (unsigned int[]){ MUL_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ DIV_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ MOD_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ ADD_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ SUB_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ LEFT_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ RIGHT_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ AND_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ XOR_ASSIGN, 0 }, NULL },
{ assignment_operator, (unsigned int[]){ OR_ASSIGN, 0 }, NULL },
{ expression, (unsigned int[]){ assignment_expression, 0 }, NULL },
{ expression, (unsigned int[]){ expression,',',assignment_expression, 0 }, NULL },
{ constant_expression, (unsigned int[]){ conditional_expression, 0 }, NULL },
{ declaration, (unsigned int[]){ declaration_specifiers,';',type_not_specified, 0 }, declaration__declaration_specifiers_059_type_not_specified },
{ declaration, (unsigned int[]){ declaration_specifiers,init_declarator_list,';',type_not_specified, 0 }, declaration__declaration_specifiers_init_declarator_list_059_type_not_specified },
{ declaration, (unsigned int[]){ static_assert_declaration, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ storage_class_specifier,declaration_specifiers, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ storage_class_specifier, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ type_specifier,declaration_specifiers, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ type_specifier, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ type_qualifier,declaration_specifiers, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ type_qualifier, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ function_specifier,declaration_specifiers, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ function_specifier, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ alignment_specifier,declaration_specifiers, 0 }, NULL },
{ declaration_specifiers, (unsigned int[]){ alignment_specifier, 0 }, NULL },
{ init_declarator_list, (unsigned int[]){ init_declarator, 0 }, NULL },
{ init_declarator_list, (unsigned int[]){ init_declarator_list,',',init_declarator, 0 }, NULL },
{ init_declarator, (unsigned int[]){ declarator,'=',initializer, 0 }, NULL },
{ init_declarator, (unsigned int[]){ declarator, 0 }, NULL },
{ storage_class_specifier, (unsigned int[]){ TYPEDEF, 0 }, NULL },
{ storage_class_specifier, (unsigned int[]){ EXTERN, 0 }, NULL },
{ storage_class_specifier, (unsigned int[]){ STATIC, 0 }, NULL },
{ storage_class_specifier, (unsigned int[]){ THREAD_LOCAL, 0 }, NULL },
{ storage_class_specifier, (unsigned int[]){ AUTO, 0 }, NULL },
{ storage_class_specifier, (unsigned int[]){ REGISTER, 0 }, NULL },
{ storage_class_specifier, (unsigned int[]){ TRACE, 0 }, NULL },
{ type_specifier, (unsigned int[]){ types, 0 }, type_specifier__types },
{ types, (unsigned int[]){ VOID, 0 }, NULL },
{ types, (unsigned int[]){ CHAR, 0 }, NULL },
{ types, (unsigned int[]){ SHORT, 0 }, NULL },
{ types, (unsigned int[]){ INT, 0 }, NULL },
{ types, (unsigned int[]){ LONG, 0 }, NULL },
{ types, (unsigned int[]){ FLOAT, 0 }, NULL },
{ types, (unsigned int[]){ DOUBLE, 0 }, NULL },
{ types, (unsigned int[]){ SIGNED, 0 }, NULL },
{ types, (unsigned int[]){ UNSIGNED, 0 }, NULL },
{ types, (unsigned int[]){ BOOL, 0 }, NULL },
{ types, (unsigned int[]){ COMPLEX, 0 }, NULL },
{ types, (unsigned int[]){ IMAGINARY, 0 }, NULL },
{ types, (unsigned int[]){ atomic_type_specifier, 0 }, NULL },
{ types, (unsigned int[]){ struct_or_union_specifier, 0 }, NULL },
{ types, (unsigned int[]){ enum_specifier, 0 }, NULL },
{ types, (unsigned int[]){ TYPEDEF_NAME, 0 }, NULL },
{ struct_or_union_specifier, (unsigned int[]){ struct_or_union,'{',struct_declaration_list,'}', 0 }, NULL },
{ struct_or_union_specifier, (unsigned int[]){ struct_or_union,generic_identifier,'{',struct_declaration_list,'}', 0 }, NULL },
{ struct_or_union_specifier, (unsigned int[]){ struct_or_union,generic_identifier, 0 }, NULL },
{ struct_or_union_specifier, (unsigned int[]){ struct_or_union,'{',error,'}', 0 }, struct_or_union_specifier__struct_or_union_123_error_125 },
{ struct_or_union_specifier, (unsigned int[]){ struct_or_union,generic_identifier,'{',error,'}', 0 }, struct_or_union_specifier__struct_or_union_generic_identifier_123_error_125 },
{ struct_or_union, (unsigned int[]){ STRUCT, 0 }, NULL },
{ struct_or_union, (unsigned int[]){ UNION, 0 }, NULL },
{ struct_declaration_list, (unsigned int[]){ struct_declaration, 0 }, NULL },
{ struct_declaration_list, (unsigned int[]){ struct_declaration_list,struct_declaration, 0 }, NULL },
{ struct_declaration, (unsigned int[]){ specifier_qualifier_list,';',type_not_specified, 0 }, NULL },
{ struct_declaration, (unsigned int[]){ specifier_qualifier_list,struct_declarator_list,';',type_not_specified, 0 }, NULL },
{ struct_declaration, (unsigned int[]){ static_assert_declaration, 0 }, NULL },
{ specifier_qualifier_list, (unsigned int[]){ type_specifier,specifier_qualifier_list, 0 }, NULL },
{ specifier_qualifier_list, (unsigned int[]){ type_specifier, 0 }, NULL },
{ specifier_qualifier_list, (unsigned int[]){ type_qualifier,specifier_qualifier_list, 0 }, NULL },
{ specifier_qualifier_list, (unsigned int[]){ type_qualifier, 0 }, NULL },
{ struct_declarator_list, (unsigned int[]){ struct_declarator, 0 }, NULL },
{ struct_declarator_list, (unsigned int[]){ struct_declarator_list,',',struct_declarator, 0 }, NULL },
{ struct_declarator, (unsigned int[]){ ':',constant_expression, 0 }, NULL },
{ struct_declarator, (unsigned int[]){ declarator,':',constant_expression, 0 }, NULL },
{ struct_declarator, (unsigned int[]){ declarator, 0 }, NULL },
{ enum_specifier, (unsigned int[]){ ENUM,'{',enumerator_list,'}', 0 }, NULL },
{ enum_specifier, (unsigned int[]){ ENUM,'{',enumerator_list,',','}', 0 }, NULL },
{ enum_specifier, (unsigned int[]){ ENUM,generic_identifier,'{',enumerator_list,'}', 0 }, NULL },
{ enum_specifier, (unsigned int[]){ ENUM,generic_identifier,'{',enumerator_list,',','}', 0 }, NULL },
{ enum_specifier, (unsigned int[]){ ENUM,generic_identifier, 0 }, NULL },
{ enumerator_list, (unsigned int[]){ enumerator, 0 }, NULL },
{ enumerator_list, (unsigned int[]){ enumerator_list,',',enumerator, 0 }, NULL },
{ enumerator, (unsigned int[]){ enumeration_constant,'=',constant_expression, 0 }, NULL },
{ enumerator, (unsigned int[]){ enumeration_constant, 0 }, NULL },
{ atomic_type_specifier, (unsigned int[]){ ATOMIC,'(',type_name,')', 0 }, NULL },
{ type_qualifier, (unsigned int[]){ CONST, 0 }, NULL },
{ type_qualifier, (unsigned int[]){ RESTRICT, 0 }, NULL },
{ type_qualifier, (unsigned int[]){ VOLATILE, 0 }, NULL },
{ type_qualifier, (unsigned int[]){ ATOMIC, 0 }, NULL },
{ type_qualifier, (unsigned int[]){ MAYBECONST, 0 }, NULL },
{ function_specifier, (unsigned int[]){ INLINE, 0 }, NULL },
{ function_specifier, (unsigned int[]){ NORETURN, 0 }, NULL },
{ alignment_specifier, (unsigned int[]){ ALIGNAS,'(',type_name,')', 0 }, NULL },
{ alignment_specifier, (unsigned int[]){ ALIGNAS,'(',constant_expression,')', 0 }, NULL },
{ declarator, (unsigned int[]){ pointer,direct_declarator,type_not_specified, 0 }, NULL },
{ declarator, (unsigned int[]){ direct_declarator,type_not_specified, 0 }, NULL },
{ direct_declarator, (unsigned int[]){ generic_identifier, 0 }, NULL },
{ direct_declarator, (unsigned int[]){ '(',declarator,')', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[','*',']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',STATIC,type_qualifier_list,assignment_expression,']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',STATIC,assignment_expression,']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',type_qualifier_list,'*',']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',type_qualifier_list,STATIC,assignment_expression,']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',type_qualifier_list,assignment_expression,']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',type_qualifier_list,']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'[',assignment_expression,']', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'(',type_not_specified,parameter_type_list,')', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'(',type_not_specified,error,')', 0 }, direct_declarator__direct_declarator_040_type_not_specified_error_041 },
{ direct_declarator, (unsigned int[]){ direct_declarator,'(',type_not_specified,')', 0 }, NULL },
{ direct_declarator, (unsigned int[]){ direct_declarator,'(',type_not_specified,identifier_list,')', 0 }, NULL },
{ generic_identifier, (unsigned int[]){ IDENTIFIER, 0 }, NULL },
{ generic_identifier, (unsigned int[]){ TYPEDEF_NAME, 0 }, NULL },
{ pointer, (unsigned int[]){ '*',type_qualifier_list,pointer, 0 }, NULL },
{ pointer, (unsigned int[]){ '*',type_qualifier_list, 0 }, NULL },
{ pointer, (unsigned int[]){ '*',pointer, 0 }, NULL },
{ pointer, (unsigned int[]){ '*', 0 }, NULL },
{ type_qualifier_list, (unsigned int[]){ type_qualifier, 0 }, NULL },
{ type_qualifier_list, (unsigned int[]){ type_qualifier_list,type_qualifier, 0 }, NULL },
{ parameter_type_list, (unsigned int[]){ parameter_list,',',ELLIPSIS, 0 }, NULL },
{ parameter_type_list, (unsigned int[]){ parameter_list, 0 }, NULL },
{ parameter_list, (unsigned int[]){ parameter_declaration,type_not_specified, 0 }, NULL },
{ parameter_list, (unsigned int[]){ parameter_list,',',parameter_declaration,type_not_specified, 0 }, NULL },
{ parameter_declaration, (unsigned int[]){ declaration_specifiers,declarator, 0 }, NULL },
{ parameter_declaration, (unsigned int[]){ declaration_specifiers,abstract_declarator, 0 }, NULL },
{ parameter_declaration, (unsigned int[]){ declaration_specifiers, 0 }, NULL },
{ identifier_list, (unsigned int[]){ IDENTIFIER, 0 }, NULL },
{ identifier_list, (unsigned int[]){ identifier_list,',',IDENTIFIER, 0 }, NULL },
{ type_name, (unsigned int[]){ specifier_qualifier_list,abstract_declarator,type_not_specified, 0 }, NULL },
{ type_name, (unsigned int[]){ specifier_qualifier_list,type_not_specified, 0 }, NULL },
{ abstract_declarator, (unsigned int[]){ pointer,direct_abstract_declarator, 0 }, NULL },
{ abstract_declarator, (unsigned int[]){ pointer, 0 }, NULL },
{ abstract_declarator, (unsigned int[]){ direct_abstract_declarator, 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '(',abstract_declarator,')', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[',']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[','*',']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[',STATIC,type_qualifier_list,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[',STATIC,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[',type_qualifier_list,STATIC,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[',type_qualifier_list,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[',type_qualifier_list,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '[',assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[',']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[','*',']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[',STATIC,type_qualifier_list,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[',STATIC,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[',type_qualifier_list,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[',type_qualifier_list,STATIC,assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[',type_qualifier_list,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'[',assignment_expression,']', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '(',')', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ '(',parameter_type_list,')', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'(',type_not_specified,')', 0 }, NULL },
{ direct_abstract_declarator, (unsigned int[]){ direct_abstract_declarator,'(',type_not_specified,parameter_type_list,')', 0 }, NULL },
{ type_not_specified, NULL, type_not_specified__empty },
{ initializer, (unsigned int[]){ '{',initializer_list,'}', 0 }, NULL },
{ initializer, (unsigned int[]){ '{',initializer_list,',','}', 0 }, NULL },
{ initializer, (unsigned int[]){ assignment_expression, 0 }, NULL },
{ initializer_list, (unsigned int[]){ designation,initializer, 0 }, NULL },
{ initializer_list, (unsigned int[]){ initializer, 0 }, NULL },
{ initializer_list, (unsigned int[]){ initializer_list,',',designation,initializer, 0 }, NULL },
{ initializer_list, (unsigned int[]){ initializer_list,',',initializer, 0 }, NULL },
{ designation, (unsigned int[]){ designator_list,'=', 0 }, NULL },
{ designator_list, (unsigned int[]){ designator, 0 }, NULL },
{ designator_list, (unsigned int[]){ designator_list,designator, 0 }, NULL },
{ designator, (unsigned int[]){ '[',constant_expression,']', 0 }, NULL },
{ designator, (unsigned int[]){ '.',generic_identifier, 0 }, NULL },
{ static_assert_declaration, (unsigned int[]){ STATIC_ASSERT,'(',constant_expression,',',STRING_LITERAL,')',';', 0 }, NULL },
{ statement, (unsigned int[]){ labeled_statement, 0 }, NULL },
{ statement, (unsigned int[]){ compound_statement, 0 }, NULL },
{ statement, (unsigned int[]){ expression_statement, 0 }, NULL },
{ statement, (unsigned int[]){ selection_statement, 0 }, NULL },
{ statement, (unsigned int[]){ iteration_statement, 0 }, NULL },
{ statement, (unsigned int[]){ jump_statement, 0 }, NULL },
{ statement, (unsigned int[]){ basilisk_statements, 0 }, NULL },
{ statement, (unsigned int[]){ error,';', 0 }, statement__error_059 },
{ labeled_statement, (unsigned int[]){ generic_identifier,':',statement, 0 }, NULL },
{ labeled_statement, (unsigned int[]){ CASE,constant_expression,':',statement, 0 }, NULL },
{ labeled_statement, (unsigned int[]){ DEFAULT,':',statement, 0 }, NULL },
{ compound_statement, (unsigned int[]){ '{','}', 0 }, NULL },
{ compound_statement, (unsigned int[]){ '{',block_item_list,'}', 0 }, NULL },
{ block_item_list, (unsigned int[]){ block_item, 0 }, NULL },
{ block_item_list, (unsigned int[]){ block_item_list,block_item, 0 }, NULL },
{ block_item, (unsigned int[]){ declaration, 0 }, NULL },
{ block_item, (unsigned int[]){ statement, 0 }, NULL },
{ expression_statement, (unsigned int[]){ ';', 0 }, NULL },
{ expression_statement, (unsigned int[]){ expression,';', 0 }, NULL },
{ selection_statement, (unsigned int[]){ IF,'(',expression_error,')',statement,ELSE,statement, 0 }, NULL },
{ selection_statement, (unsigned int[]){ IF,'(',expression_error,')',statement, 0 }, NULL },
{ selection_statement, (unsigned int[]){ SWITCH,'(',expression_error,')',statement, 0 }, NULL },
{ for_scope, (unsigned int[]){ FOR, 0 }, for_scope__FOR },
{ iteration_statement, (unsigned int[]){ WHILE,'(',expression,')',statement, 0 }, NULL },
{ iteration_statement, (unsigned int[]){ DO,statement,WHILE,'(',expression,')',';', 0 }, NULL },
{ iteration_statement, (unsigned int[]){ for_scope,'(',expression_statement,expression_statement,')',statement, 0 }, iteration_statement__for_scope_040_expression_statement_expression_statement_041_statement },
{ iteration_statement, (unsigned int[]){ for_scope,'(',expression_statement,expression_statement,expression,')',statement, 0 }, iteration_statement__for_scope_040_expression_statement_expression_statement_expression_041_statement },
{ iteration_statement, (unsigned int[]){ for_declaration_statement, 0 }, NULL },
{ for_declaration_statement, (unsigned int[]){ for_scope,'(',declaration,expression_statement,')',statement, 0 }, for_declaration_statement__for_scope_040_declaration_expression_statement_041_statement },
{ for_declaration_statement, (unsigned int[]){ for_scope,'(',declaration,expression_statement,expression,')',statement, 0 }, for_declaration_statement__for_scope_040_declaration_expression_statement_expression_041_statement },
{ jump_statement, (unsigned int[]){ GOTO,generic_identifier,';', 0 }, NULL },
{ jump_statement, (unsigned int[]){ CONTINUE,';', 0 }, NULL },
{ jump_statement, (unsigned int[]){ BREAK,';', 0 }, NULL },
{ jump_statement, (unsigned int[]){ RETURN,';', 0 }, NULL },
{ jump_statement, (unsigned int[]){ RETURN,expression,';', 0 }, NULL },
{ external_declaration, (unsigned int[]){ function_definition, 0 }, NULL },
{ external_declaration, (unsigned int[]){ declaration, 0 }, NULL },
{ external_declaration, (unsigned int[]){ macro_statement, 0 }, NULL },
{ external_declaration, (unsigned int[]){ event_definition, 0 }, NULL },
{ external_declaration, (unsigned int[]){ boundary_definition, 0 }, NULL },
{ external_declaration, (unsigned int[]){ external_foreach_dimension, 0 }, NULL },
{ external_declaration, (unsigned int[]){ attribute, 0 }, NULL },
{ external_declaration, (unsigned int[]){ error,compound_statement, 0 }, external_declaration__error_compound_statement },
{ function_declaration, (unsigned int[]){ declaration_specifiers,declarator, 0 }, function_declaration__declaration_specifiers_declarator },
{ function_definition, (unsigned int[]){ function_declaration,declaration_list,compound_statement, 0 }, function_definition__function_declaration_declaration_list_compound_statement },
{ function_definition, (unsigned int[]){ function_declaration,compound_statement, 0 }, function_definition__function_declaration_compound_statement },
{ declaration_list, (unsigned int[]){ declaration, 0 }, NULL },
{ declaration_list, (unsigned int[]){ declaration_list,declaration, 0 }, NULL },
{ basilisk_statements, (unsigned int[]){ macro_statement, 0 }, NULL },
{ basilisk_statements, (unsigned int[]){ foreach_statement, 0 }, NULL },
{ basilisk_statements, (unsigned int[]){ foreach_inner_statement, 0 }, NULL },
{ basilisk_statements, (unsigned int[]){ foreach_dimension_statement, 0 }, NULL },
{ basilisk_statements, (unsigned int[]){ forin_declaration_statement, 0 }, NULL },
{ basilisk_statements, (unsigned int[]){ forin_statement, 0 }, NULL },
{ macro_statement, (unsigned int[]){ function_call,compound_statement, 0 }, NULL },
{ foreach_statement, (unsigned int[]){ FOREACH,'(',')',statement, 0 }, NULL },
{ foreach_statement, (unsigned int[]){ FOREACH,'(',foreach_parameters,')',statement, 0 }, NULL },
{ foreach_parameters, (unsigned int[]){ foreach_parameter, 0 }, NULL },
{ foreach_parameters, (unsigned int[]){ foreach_parameters,',',foreach_parameter, 0 }, NULL },
{ foreach_parameter, (unsigned int[]){ assignment_expression, 0 }, NULL },
{ foreach_parameter, (unsigned int[]){ reduction_list, 0 }, NULL },
{ reduction_list, (unsigned int[]){ reduction, 0 }, NULL },
{ reduction_list, (unsigned int[]){ reduction_list,reduction, 0 }, NULL },
{ reduction, (unsigned int[]){ REDUCTION,'(',reduction_operator,':',reduction_array,')', 0 }, NULL },
{ reduction_operator, (unsigned int[]){ generic_identifier, 0 }, NULL },
{ reduction_operator, (unsigned int[]){ '+', 0 }, NULL },
{ reduction_operator, (unsigned int[]){ OR_OP, 0 }, NULL },
{ reduction_array, (unsigned int[]){ generic_identifier, 0 }, NULL },
{ reduction_array, (unsigned int[]){ generic_identifier,'[',':',expression,']', 0 }, NULL },
{ foreach_inner_statement, (unsigned int[]){ FOREACH_INNER,'(',')',statement, 0 }, NULL },
{ foreach_inner_statement, (unsigned int[]){ FOREACH_INNER,'(',expression,')',statement, 0 }, NULL },
{ foreach_dimension_statement, (unsigned int[]){ FOREACH_DIMENSION,'(',')',statement, 0 }, NULL },
{ foreach_dimension_statement, (unsigned int[]){ FOREACH_DIMENSION,'(',I_CONSTANT,')',statement, 0 }, NULL },
{ forin_declaration_statement, (unsigned int[]){ for_scope,'(',declaration_specifiers,declarator,IDENTIFIER,forin_arguments,')',statement, 0 }, forin_declaration_statement__for_scope_040_declaration_specifiers_declarator_IDENTIFIER_forin_arguments_041_statement },
{ forin_statement, (unsigned int[]){ for_scope,'(',expression,IDENTIFIER,forin_arguments,')',statement, 0 }, forin_statement__for_scope_040_expression_IDENTIFIER_forin_arguments_041_statement },
{ forin_arguments, (unsigned int[]){ expression, 0 }, NULL },
{ forin_arguments, (unsigned int[]){ postfix_initializer, 0 }, NULL },
{ event_definition, (unsigned int[]){ generic_identifier,generic_identifier,'(',event_parameters,')',statement, 0 }, NULL },
{ event_parameters, (unsigned int[]){ event_parameter, 0 }, NULL },
{ event_parameters, (unsigned int[]){ event_parameters,',',event_parameter, 0 }, NULL },
{ event_parameters, (unsigned int[]){ event_parameters,';',event_parameter, 0 }, NULL },
{ event_parameter, (unsigned int[]){ conditional_expression, 0 }, NULL },
{ event_parameter, (unsigned int[]){ unary_expression,assignment_operator,conditional_expression, 0 }, NULL },
{ event_parameter, (unsigned int[]){ unary_expression,assignment_operator,postfix_initializer, 0 }, NULL },
{ boundary_definition, (unsigned int[]){ assignment_expression,';', 0 }, NULL },
{ external_foreach_dimension, (unsigned int[]){ FOREACH_DIMENSION,'(',')',function_definition, 0 }, NULL },
{ external_foreach_dimension, (unsigned int[]){ FOREACH_DIMENSION,'(',I_CONSTANT,')',function_definition, 0 }, NULL },
{ attribute, (unsigned int[]){ generic_identifier,'{',struct_declaration_list,'}', 0 }, NULL },
{ root, (unsigned int[]){ translation_unit, 0 }, root__translation_unit },
{ 0 }
};
