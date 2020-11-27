#include <stdint.h>
#include "../lexer/lexer.h"
typedef enum __attribute__ ((__packed__)) _keywords_ {
  
} KEYWORDS_E;
typedef struct Expression {
  
} exp_t;

typedef struct Ast {
  exp_t * exp_nodes;
  uint8_t size;
  uint8_t capacity;
} ast_t;
/* main must be first */
ast_t *ast_create(token_l *list, uint8_t start_size);
ast_t *ast_insert(ast_t * ast, token_l *list, uint8_t index);
