#pragma once

#include <stdint.h>
typedef enum _morpheme_ {
  VALUE,
  EMPTY, // beginning asciis / Invalid
  SPACE, // ' '
  COMMA, // ','
  ENDLINE, // '\n'
  POUND, // '#'
  DOLLAR, // '$'
  AMP, // '&'
  FORW, // '/'
  TAB, // '\t'
  BANG,  // '!'
  REL,   // '%'
  QUOTE, // '''
  DBLQUOTE, // '"'
  OPAREN, // '('
  CPAREN, // ')'
  OBRACK, // '['
  CBRACK, // ']'
  OBRACE, // '{'
  CBRACE, // '}'
  DOT, // '.'
  REF, // '\'
  BTICK, // '`'
  PIPE, // '|'
  COLON, // ':'
  SEMICOLON, // ';'
} morpheme_e;

// TOPIC:: peek filename, line, pos? or store it?
typedef struct Token {
  // null if root morpheme
  char * data;
  // 0 if root morpheme
  uint8_t length; 
  morpheme_e morpheme;
} token_t;

typedef struct TokenList {
  token_t * tokens;
  uint8_t capacity;
  uint8_t size;
} token_l;

morpheme_e morpheme_get(const char c);
/* incomplete token. no data or length */
token_t token_get_individual(char * buffer);

token_l token_get_list(char * buffer, uint8_t start_size);

void token_list_free(token_l list);


