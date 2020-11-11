#include "./flush.h"
#include <stdio.h>

int flush(const char *fileName, const uint8_t *buffer) {
  FILE *handle = fopen(fileName, "w+b");
  fwrite(buffer, sizeof(buffer),1,handle);
  if(handle == NULL)
    printf_s("error: writing file: %s", fileName);
  return 0;

  }
