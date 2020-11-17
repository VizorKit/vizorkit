#include "./lexer.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debug.h"
// forwards
morpheme_e const static lookup[128];

token_t token_get_individual(char * buffer) {
  token_t token = {
    .data = NULL,
    .length = 0,
    .morpheme = lookup[(int)*buffer]
  };
  return token;
}

token_l token_get_list(char * buffer, uint8_t start_size) {
  token_l tokens = {
    .size = 0,
    .tokens = NULL,
    .capacity = start_size
  };
  tokens.tokens = malloc(sizeof(token_t) * start_size);

  uint8_t skip = 0;
  token_t prev_t = token_get_individual(" ");
  while(*buffer != '\0') {
    if(tokens.capacity <= tokens.size + 3) {
      tokens.capacity = tokens.capacity << 1;
      tokens.tokens = realloc((void*)(tokens.tokens), tokens.capacity);
    }
    token_t t  = token_get_individual(buffer);
    switch(t.morpheme) {
    case VALUE:
      {
	buffer++;
	break;
      }
    case EMPTY:
      {
	buffer++;
	skip = 1;
	break;
      }
    case ENDLINE:
      {
	buffer++;
	skip = 1;
	break;
      }
    case TAB:
      {
	buffer++;
      skip = 1;
      break;
      }
    case SPACE:
      {
	buffer++;
      skip = 1;
      break;
      }
    case QUOTE:
      {
	char * start = ++buffer;
	uint8_t cont = 1;
	while(*buffer != '\0' && cont) {
	  morpheme_e local_morph = lookup[(int)(*buffer)];
	  if(local_morph == REF)
	    {
	      if(*++buffer != '\'') cont = 0;
	    }
	  else if(local_morph == QUOTE) cont = 0;
	  buffer++;
	}
	memcpy((void *)(&tokens.tokens[tokens.size]), &t, sizeof(token_t));
	tokens.size++;
	if(start <= --buffer)
	  {
	    token_t value = token_get_individual("a");
	    value.data = buffer;
	    value.length = buffer - start;
	    memcpy((void *)(&tokens.tokens[tokens.size]), &value, sizeof(token_t));
	    tokens.size++;
	    token_t end = token_get_individual("'");
	    memcpy((void *)(&tokens.tokens[tokens.size]), &end, sizeof(token_t));
	    tokens.size++;
	  }
	skip = 1;
	break;
      }
    case DBLQUOTE:
      {
	char * start = ++buffer;
	uint8_t cont = 1;
	while(*buffer != '\0' && cont) {
	  morpheme_e local_morph = lookup[(int)(*buffer)];
	  if(local_morph == REF)
	    {
	      if(*++buffer != '\"') cont = 0;
	    }
	  else if(local_morph == QUOTE) cont = 0;
	  buffer++;
	}
	memcpy((void *)(&tokens.tokens[tokens.size]), &t, sizeof(token_t));
	tokens.size++;
	if(start <= --buffer)
	  {
	    token_t value = token_get_individual("a");
	    value.data = buffer;
	    value.length = buffer - start;
	    memcpy((void *)(&tokens.tokens[tokens.size]), &value, sizeof(token_t));
	    tokens.size++;
	    token_t end = token_get_individual("'");
	    memcpy((void *)(&tokens.tokens[tokens.size]), &end, sizeof(token_t));
	    tokens.size++;
	  }
	skip = 1;
	break;
      }
    case FORW:
      {
	buffer++;
	if(lookup[(int)(*buffer)] == FORW)
	  {
	    while(*buffer != '\0' && lookup[(int)(*buffer)] != ENDLINE)
	      {
		buffer++;
	      }
	    skip = 1;
	    t = token_get_individual(" ");
	  }
	else {
	  buffer--;
	}
      }
    default:
      {
      buffer++;
      break;
      }
    }
    if(!skip) {
      memcpy((void *)(&tokens.tokens[tokens.size]), &t, sizeof(token_t));
      tokens.size++;
    }
    prev_t = t;
  }
  return tokens;
}

void token_list_free(token_l list) {
  free(list.tokens);
}

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
    VALUE,
    VALUE,
    VALUE,
    VALUE,
    VALUE,
    OBRACK,
    REF,
    CBRACK,
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
