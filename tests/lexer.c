#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "../src/lexer/lexer.h"
#include "../src/debug/debug.h"

void test_multi();
void test_value();
void test_comment();
void test_separator();
void test_endline();


int main() {
  // test_endline();
  // test_separator();
  // test_comment();
    test_value();
    test_multi();
}

void test_multi() {
  // length should be 15
  char * buffer = "const val = method(); // comment\n let thing = 'string';";
  uint8_t size = 10;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == VALUE);
  assert(l.tokens[1].morpheme == VALUE);
  assert(l.tokens[2].morpheme == VALUE);
  assert(l.tokens[3].morpheme == VALUE);
  assert(l.tokens[4].morpheme == OPAREN);
  assert(l.tokens[5].morpheme == CPAREN);
  assert(l.tokens[6].morpheme == SEMICOLON);
  assert(l.tokens[7].morpheme == VALUE);
  assert(l.tokens[8].morpheme == VALUE);
  assert(l.tokens[9].morpheme == VALUE);
  assert(l.tokens[10].morpheme == QUOTE);
  assert(l.tokens[11].morpheme == VALUE);
  assert(l.tokens[12].morpheme == QUOTE);
  assert(l.tokens[13].morpheme == SEMICOLON);
  assert(l.tokens[14].morpheme == VALUE);

  assert(strncmp(buffer, l.tokens[0].data, 10));

}

void test_value() {
  char * buffer = "test_value";
  uint8_t length = 10;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == 1);
  assert(l.tokens[0].length == length);
  assert(l.tokens[0].morpheme == VALUE);
  //  debug_print("%d\n", strncmp(buffer, l.tokens[0].data, length));
  /* assert(strncmp(buffer, l.tokens[0].data, length)  == 0); */
}

void test_comment() {
  char * buffer = "// this is a comment.\n";
  token_l l = token_get_list(buffer, 4);
  assert(l.size == 1);
}

void test_separator() {
  char * buffer = " \t\n";
  token_l l = token_get_list(buffer, 7);
  assert(l.size == 0);
}

void test_endline() {
  char * buffer = "\n";
  token_l l = token_get_list(buffer, 4);
  assert(l.size == 0);
}
