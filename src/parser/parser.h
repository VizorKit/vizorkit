#include "../lexer/lexer.h"
#include <stdint.h>

typedef struct Definition def_t;
typedef struct Expression exp_t;
typedef struct Preprocess pre_t;
typedef struct Postprocess pos_t;

typedef enum __attribute__((__packed__)) _top_types_ {
  EXP,
  PRE,
  PRO,
  DEF
} TOPTYPES_E;

typedef struct Expression {
  exp_t * left;
  exp_t * right;
  exp_t * parent;
  
} exp_t;

typedef struct Preprocess {
  pre_t *prev;
  pre_t *next;
} pre_t;

typedef struct Definition {
  def_t *prev;
  def_t *next;
} def_t;

typedef union TopLevel {
  exp_t *expression;
  pre_t *preprocess;
  def_t *definition;
  pos_t *postprocess;
} top_lvl_u;

typedef struct ParseTree {
  top_lvl_u *tops;
  TOPTYPES_E *types;
  uint32_t size;
  uint32_t capacity;
} ptree_t;

ptree_t ast_create(token_l *list, uint32_t start_capacity);
