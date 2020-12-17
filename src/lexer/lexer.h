#pragma once
#include <stdint.h>
#include "../utils/utils.h"

typedef enum __attribute__ ((__packed__)) _morpheme_ {
  VALUE,
  EMPTY,     // beginning asciis / Invalid
  SPACE,     // ' '
  COMMA,     // ','
  ENDLINE,   // '\n'
  POUND,     // '#'
  DOLLAR,    // '$'
  AMP,       // '&'
  FORW,      // '/'
  TAB,       // '\t'
  BANG,      // '!'
  REL,       // '%'
  QUOTE,     // '''
  DBLQUOTE,  // '"'
  OPAREN,    // '('
  CPAREN,    // ')'
  OBRACK,    // '['
  CBRACK,    // ']'
  OBRACE,    // '{'
  CBRACE,    // '}'
  DOT,       // '.'
  REF,       // '\'
  BTICK,     // '`'
  PIPE,      // '|'
  COLON,     // ':'
  SEMICOLON, // ';'
  LT,        // '<'
  EQ,        // '='
  GT,        // '>'
  QUESTION,  // '?'
  AT         // '@'
} morpheme_e;

typedef struct Token {
  // null if root morpheme
  char * data;
  // 0 if root morpheme
  ubyte_t length; 
  morpheme_e morpheme;
} token_t;

typedef struct TokenList {
  token_t * tokens;
  uint32_t capacity;
  uint32_t size;
} token_l;

/* incomplete token. no data or length */
token_t token_get_individual(char * buffer);

token_l token_get_list(char * buffer, uint32_t start_capacity);

void token_list_free(token_l *list);


