#include <stdint.h>
#include "../lexer/lexer.h"

typedef enum __attribute__((__packed__)) _keywords_ {
  LET, // let
  FUNC, // function
  DBL, // double
  INT, // int
  STR, // string
  CHAR, // char
  TYPE, // type
  DEF, // def
  IMP, // implements
  USE, // use
  DATA, // data 
} KEYWORDS_E;

typedef struct Expression {
  
} exp_t;

typedef struct Import {

} imp_t;

typedef struct Definition {
  
} def_t;

typedef union TopLevel {
  exp_t expression;
  imp_t import;
  def_t definition;
} top_lvl_u;

typedef struct Ast {
  top_lvl_u * tops;
  uint8_t size;
  uint8_t capacity;
} ast_t;

ast_t *ast_create(token_l *list, uint8_t start_size);
ast_t *ast_insert(ast_t * ast, token_l *list, uint8_t index);
