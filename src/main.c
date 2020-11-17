#include "./debug/debug.h"
#include "./lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char * ptr = malloc(sizeof(char) * 20);
  debug_print("%s","print");
  token_l list = token_get_list("Hello;",5);
  token_list_free(list);
  return 0;
}
