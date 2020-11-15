#include "./lexer.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


token_t token_get_individual(char * buffer) {
  token_t token = {
    .data = NULL,
    .length = 0,
    .morpheme = morpheme_get(*buffer)
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
    if(tokens.capacity == tokens.size) {
      tokens.capacity = tokens.capacity << 1;
      tokens.tokens = realloc((void*)(&tokens.tokens), tokens.capacity);
    }
    token_t t  = token_get_individual(buffer);
    switch(t.morpheme) {
    case VALUE:
      buffer++;
      
      break;
    case EMPTY:
      buffer++;
      skip = 1;
      break;
    case ENDLINE:
      buffer++;
      skip = 1;
      break;
    case TAB:
      buffer++;
      skip = 1;
      break;
    case SPACE:
      buffer++;
      skip = 1;
      break;
    case QUOTE:
      void* ptr = buffer;
      uint8_t cont = 1;
      while(*buffer != '\0' && cont) {
	morpheme_e local_morph = morpheme_get(*buffer);
	if(local_morph == REF)
	  {
	    if(*++buffer != '\'') cont = 0;
	  }
	else if(local_morph == QUOTE) cont = 0;
      }
      memcpy((void *)(&tokens.tokens[tokens.size]), &t, sizeof(token_t));
      
      tokens.size++;      
      break;
    case DBLQUOTE:
      buffer++;
      break;
    case FORW:
      buffer++;
      if(morpheme_get(*buffer == FORW))
	{
	  while(*buffer != '\0' && morpheme_get(*buffer) != ENDLINE)
	    {
	      buffer++;
	    }
	  skip = 1;
	  t = token_get_individual(" ");
	}
      else {
	buffer--;
      }
    default:
      buffer++;
      break;
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
