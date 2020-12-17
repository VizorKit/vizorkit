#include "./parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// forwards
ubyte_t is_directive(char * data, ubyte_t length);
void print_directive(char * data, ubyte_t length);
ptree_t ast_create(token_l *list, uint32_t start_capacity) {
  ptree_t tree = {
    .size = 0,
    .capacity = start_capacity,
    .tops = NULL,
    .types = NULL,
  };
  tree.types = malloc(sizeof(top_lvl_u) * start_capacity);
  tree.tops = malloc(sizeof(TOPTYPES_E) * start_capacity);
  uint32_t start = 0;
  while(start != list->size) {
    token_t curr_token = list->tokens[start];
    switch(curr_token.morpheme)
      {
      case POUND: {
	if(list->tokens[++start].morpheme == VALUE && is_directive(list->tokens[start].data, list->tokens[start].length))
	  {
	    
	  }
	else
	  {
	    printf("expected a directive (#import, #export) at %.*s\n", list->tokens[start].length, list->tokens[start].data);
	  }
	  break;
      }
      }
  }
  return tree;
}


ubyte_t is_directive(char * data, ubyte_t length) {
  if()
}
