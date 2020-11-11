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
  while(*buffer != '\0') {
    if(tokens.capacity == tokens.size) {
      tokens.capacity = tokens.capacity << 1;
      tokens.tokens = realloc((void*)(&tokens.tokens), tokens.capacity);
    }
    token_t token = token_get_individual(buffer);
    switch(token.morpheme) {
    case VALUE:
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
    case FORW:
      skip = 1;
    default:
      buffer++;
      break;
    }
    if(!skip) {
      memcpy((void *)(&tokens.tokens[tokens.size]), &token, sizeof(token_t));
      tokens.size++;
    }
  }
  return tokens;
}

void token_list_free(token_l list) {
  free(list.tokens);
}
