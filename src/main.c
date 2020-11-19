#include "./debug/debug.h"
#include "./lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main() {
  token_l list = token_get_list("Hello;",5);
  assert(strncmp(list.tokens[0].data, "Hello", list.tokens[0].length) == 0);
  token_list_free(list);
  return 0;
}
