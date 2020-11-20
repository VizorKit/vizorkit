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
  test_endline();
  test_separator();
  test_comment();
  test_value();
  //test_multi();
  return 0;
}

void test_multi() {
  // length should be 15
  char * buffer = "const val";
  uint8_t size = 3;
  token_l l = token_get_list(buffer, 5);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == VALUE);
  assert(l.tokens[1].morpheme == VALUE);

}

void test_value() {
  char * buffer = "test_value";
  uint8_t length = 10;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == 1);
  assert(l.tokens[0].length == length);
  assert(l.tokens[0].morpheme == VALUE);
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
