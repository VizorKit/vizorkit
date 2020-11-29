#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "../src/lexer/lexer.h"
#include "../src/debug/debug.h"

void test_multi();
void test_value();
void test_comment();
void test_separator();
void test_endline();
void test_quote();
void test_dbl_quote();
void test_equal();
void test_pound();
void test_dollar();
void test_amp();
void test_bang();
void test_rel();
void test_parens();
void test_brackets();
void test_braces();
void test_dot();
void test_ref();
void test_backtick();
void test_pipe();
void test_colon();
void test_semicolon();
void test_lthan();
void test_gthan();
void test_question();
void test_at();

int main() {
  clock_t start,end;
  double time_taken;
  start = clock();
  test_quote();
  test_dbl_quote();
  test_endline();
  test_separator();
  test_comment();
  test_value();
  test_multi();
  test_equal();
  test_pound();
  test_dollar();
  test_amp();
  test_bang();
  test_rel();
  test_parens();
  test_brackets();
  test_braces();
  test_dot();
  test_ref();
  test_backtick();
  test_pipe();
  test_colon();
  test_semicolon();
  test_lthan();
  test_gthan();
  test_question();
  test_at();

  end = clock();
  time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
  debug_print("time taken := %f\n", time_taken);
  return 0;
}

void test_multi() {
  debug_print("test => %s\n", "multi");
  char * buffer = "const val;\n:";
  uint8_t size = 4;
  token_l l = token_get_list(buffer, 5);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == VALUE);
  assert(l.tokens[1].morpheme == VALUE);
  assert(l.tokens[2].morpheme == SEMICOLON);
  assert(l.tokens[3].morpheme == COLON);
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
  assert(l.size == 0);
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

void test_equal() {
  debug_print("test => %s\n", "equal");
  char * buffer = "=";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == EQ);
}

void test_pound() {
  debug_print("test => %s\n", "pound");
  char * buffer = "#";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == POUND);
}
void test_dollar() {
  debug_print("test => %s\n", "dollar");
  char * buffer = "$";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == DOLLAR);
}
void test_amp() {
  debug_print("test => %s\n", "amp");
  char * buffer = "&";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == AMP);
}
void test_bang() {
  debug_print("test => %s\n", "bang");
  char * buffer = "!";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == BANG);

}
void test_rel() {
  debug_print("test => %s\n", "rel");
  char * buffer = "%";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == REL);

}
void test_parens() {
  debug_print("test => %s\n", "parenthesis");
  char * buffer = "()";
  uint8_t size = 2;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == OPAREN);
  assert(l.tokens[1].morpheme == CPAREN);

}
void test_brackets() {
  debug_print("test => %s\n", "brackets");
  char * buffer = "[]";
  uint8_t size = 2;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == OBRACK);
  assert(l.tokens[1].morpheme == CBRACK);

}
void test_braces() {
  debug_print("test => %s\n", "braces");
  char * buffer = "{}";
  uint8_t size = 2;
  token_l l = token_get_list(buffer, 5);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == OBRACE);
  assert(l.tokens[1].morpheme == CBRACE);

}
void test_dot() {
  debug_print("test => %s\n", "dot");
  char * buffer = ".";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == DOT);

}
void test_ref() {
  debug_print("test => %s\n", "ref");
  char * buffer = "\\";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == REF);

}
void test_backtick() {
  debug_print("test => %s\n", "backtick");
  char * buffer = "`";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == BTICK);

}
void test_pipe() {
  debug_print("test => %s\n", "pipe");
  char * buffer = "|";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == PIPE);

}
void test_colon() {
  debug_print("test => %s\n", "colon");
  char * buffer = ":";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == COLON);

}
void test_semicolon() {
  debug_print("test => %s\n", "semicolon");
  char * buffer = ";";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == SEMICOLON);

}
void test_lthan() {
  debug_print("test => %s\n", "lthan");
  char * buffer = "<";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == LT);

}
void test_gthan() {
  debug_print("test => %s\n", "gthan");
  char * buffer = ">";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == GT);

}
void test_question() {
  debug_print("test => %s\n", "question");
  char * buffer = "?";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == QUESTION);

}
void test_at() {
  debug_print("test => %s\n", "at");
  char * buffer = "@";
  uint8_t size = 1;
  token_l l = token_get_list(buffer, 4);
  assert(l.size == size);
  assert(l.tokens[0].morpheme == AT);

}
