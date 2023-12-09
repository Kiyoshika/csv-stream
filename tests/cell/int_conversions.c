#include "cell.h"
#include <assert.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"

int main() {
  struct cstream_cell_t cell;
  assert(cstream_cell_init(&cell) == true);

  cstream_cell_set_int64(&cell, -10, false);
  assert(cstream_cell_as_int64(&cell) == -10);
  //assert(fabs(cstream_cell_as_double(&cell) - -10.0) < 0.00001);
  //assert(strcmp(cstream_cell_as_string(&cell), "-10") == 0);

  printf(GREEN "tests/cell/int_conversions.c --- All assertions passed.\n" RESET);
  return 0;
}
