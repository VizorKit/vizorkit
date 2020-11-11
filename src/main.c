#include <stdio.h>
#include "./debug/debug.h"
#include "./flush/flush.h"

int main() {
  flush("cool.bin", (uint8_t *) "hello");
  debug_print("%s", "usage");
  return 42;
}
