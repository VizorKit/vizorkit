#include "./lexer.h"
#include "../debug/debug.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// forwards
morpheme_e const static lookup[128];

token_t static inline token_create(char *data, uint8_t length,
                                   morpheme_e morpheme) {
  token_t token = {.data = data, .length = length, .morpheme = morpheme};
  return token;
}

void static inline token_l_add(token_l *tokens, token_t *token) {
  memcpy((void *)(&tokens->tokens[tokens->size]), token, sizeof(token_t));
  tokens->size++;
}
token_l token_get_list(char *buffer, uint8_t start_size) {
  token_l tokens = {.size = 0, .tokens = NULL, .capacity = start_size};
  tokens.tokens = malloc(sizeof(token_t) * start_size);
  while (*buffer != '\0') {
    if (tokens.capacity <= tokens.size + 3) {
      tokens.capacity = tokens.capacity << 1;
      tokens.tokens =
	realloc((void *)(tokens.tokens), tokens.capacity * sizeof(token_t));
    }
    morpheme_e morph = lookup[(int)*buffer];
    switch (morph)
      {
      case VALUE:
	{
	  char *start = buffer;
	  uint8_t cont = 1;
	  while (*++buffer != '\0' && cont) {
	    if (lookup[(int)*buffer] != VALUE) cont = 0;
	  }
	  token_t t = token_create(start, buffer - start, VALUE);
	  token_l_add(&tokens, &t);
          break;
	}
      case EMPTY:
	{
	  buffer++;
	  break;
	}
      case ENDLINE:
	{
	  buffer++;
	  break;
	}
      case TAB:
	{
	  buffer++;
	  break;
	}
      case SPACE:
	{
	  buffer++;
	  break;
	}
      case QUOTE:
	{
	  token_t t = token_create(NULL, 0, QUOTE);
	  token_l_add(&tokens, &t);

	  char *start = ++buffer;
	  uint8_t cont = 1;
	  while (*buffer++ != '\0' && cont) {
	    if (lookup[(int)*buffer] == REF) {
	      if()
	    
            }
	  token_t t = token_create(start, buffer - start, VALUE);
	  token_l_add(&tokens, &t);

	    morpheme_e local_morph = lookup[(int)(*buffer)];
	    if (local_morph == REF) {
	      if (*++buffer != '\'')
		cont = 0;
	    } else if (local_morph == QUOTE)
	      cont = 0;
	    buffer++;
	  }
	  token_t start_t = token_create(NULL, 0, QUOTE);
	  token_l_add(&tokens, &start_t);
	  if (start <= --buffer) {
	    token_t t = token_create(start, buffer - start, VALUE);
	    token_l_add(&tokens, &t);

	    token_t end_t = token_create(NULL, 0, QUOTE);
	    token_l_add(&tokens, &end_t);
	  }
	  break;
	}
      case DBLQUOTE:
	{
	  char *start = ++buffer;
	  uint8_t cont = 1;
	  while (*buffer != '\0' && cont) {
	    morpheme_e local_morph = lookup[(int)(*buffer)];
	    if (local_morph == REF) {
	      if (*++buffer != '\"')
		cont = 0;
	    } else if (local_morph == DBLQUOTE)
	      cont = 0;
	    buffer++;
	  }
	  token_t start_t = token_create(NULL, 0, DBLQUOTE);
	  token_l_add(&tokens, &start_t);
	  if (start <= --buffer) {
	    token_t t = token_create(start, buffer - start, VALUE);
	    token_l_add(&tokens, &t);

	    token_t end_t = token_create(NULL, 0, DBLQUOTE);
	    token_l_add(&tokens, &end_t);
	  }
	  break;
	}
      case FORW:
	{
	  buffer++;
	  if (*buffer != '\0' && lookup[(int)(*buffer)] == FORW) {
	    while (*buffer != '\0' && lookup[(int)(*buffer)] != ENDLINE) {
	      buffer++;
	    }
	  } else {
	    buffer--;
	  }
	}
      default:
	{
	  token_t t = token_create(NULL, 0, morph);
	  token_l_add(&tokens, &t);
	  buffer++; break;
	}
      }
  }
  return tokens;
}

void token_list_free(token_l list) { free(list.tokens); }

const static morpheme_e lookup[128] = {
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  TAB,
  ENDLINE, // '10'
  EMPTY,
  EMPTY,
  EMPTY, // '13'
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  EMPTY,
  SPACE, // 32
  BANG,
  DBLQUOTE,
  POUND, // 35
  DOLLAR,
  REL, // 37
  AMP,
  QUOTE,
  OPAREN,
  CPAREN, // 41
  VALUE,
  VALUE,
  COMMA, // 44
  VALUE,
  DOT,
  FORW,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  COLON, // 58
  SEMICOLON,
  LT,
  EQ,
  GT,
  QUESTION,
  AT,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  OBRACK,
  REF,
  CBRACK, // 93
  VALUE,
  VALUE,
  BTICK,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  VALUE,
  OBRACE,
  PIPE,
  CBRACE,
  VALUE
};
