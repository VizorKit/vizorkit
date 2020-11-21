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
void test_quote();
void test_dbl_quote();

int main() {
  test_quote();
  test_dbl_quote();
  test_endline();
  test_separator();
  test_comment();
  test_value();
  test_multi();
  return 0;
}

void test_multi() {
  debug_print("test => %s\n", "multi");
  char * buffer = "const val";
  uint8_t size = 2;
  token_l l = token_get_list(buffer, 5);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == VALUE);
  assert(l.tokens[1].morpheme == VALUE);

}

void test_value() {
  debug_print("test => %s\n", "value");
  char * buffer = "test_value";
  uint8_t length = 10;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == 1);
  assert(l.tokens[0].length == length);
  assert(l.tokens[0].morpheme == VALUE);
}

void test_comment() {
  debug_print("test => %s\n", "comment");
  char * buffer = "// this is a comment.\n";
  token_l l = token_get_list(buffer, 4);
  assert(l.size == 1);
}

void test_separator() {
  debug_print("test => %s\n", "separator");
  char * buffer = " \t\n";
  token_l l = token_get_list(buffer, 7);
  assert(l.size == 0);
}

void test_endline() {
  debug_print("test => %s\n", "endline");
  char * buffer = "\n";
  token_l l = token_get_list(buffer, 4);
  assert(l.size == 0);
}

void test_quote() {
  debug_print("test => %s\n", "quote");
  char * buffer = "'this is a ;&test'";
  token_l l = token_get_list(buffer, 6);
  assert(l.size == 3);
  assert(l.tokens[0].morpheme == QUOTE);
  assert(l.tokens[1].morpheme == VALUE);
  assert(l.tokens[2].morpheme == QUOTE);
}

void test_dbl_quote() {
  debug_print("test => %s\n", "dblquote");
  char * buffer = "\"this is a ;&test\"";
  token_l l = token_get_list(buffer, 6);
  assert(l.size == 3);
  assert(l.tokens[0].morpheme == DBLQUOTE);
  assert(l.tokens[1].morpheme == VALUE);
  assert(l.tokens[2].morpheme == DBLQUOTE);
}
