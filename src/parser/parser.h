#include <stdint.h>
#include "../lexer/lexer.h"

typedef struct Definition def_t;
typedef struct Expression exp_t;
typedef struct Preprocess pre_t;

typedef enum __attribute__ ((__packed__)) _keywords_ {

} KEYWORDS_E;

typedef struct Expression {
  
} exp_t;

typedef struct Preprocess {
  pre_t* next;
} pre_t;

typedef struct Definition {
  def_t* next;
} def_t;

typedef union TopLevel {
  exp_t *expression;
  pre_t *preprocess;
  def_t *definition;
} top_lvl_u;

typedef struct Ast {
  top_lvl_u * tops;
  uint8_t size;
  uint8_t capacity;
} ast_t;

ast_t ast_create(token_l *list, uint8_t start_size);
