#include "cell.h"
#include "log.h"
#include <assert.h>

int main() {
  struct cstream_cell_t cell;
  assert(cstream_cell_init(&cell) == true);

  /* INT64 */

  cstream_cell_set_int64(&cell, -10, false);
  assert(cell.type == CSTREAM_TYPE_INT);
  assert(cstream_cell_as_int64(&cell) == -10);
  assert(fabs(cstream_cell_as_decimal(&cell) - -10.0) < 0.00001);
  assert(strcmp(cstream_cell_as_string(&cell), "-10") == 0);

  cstream_cell_set_int64(&cell, 10, false);
  assert(cell.type == CSTREAM_TYPE_INT);
  assert(cstream_cell_as_int64(&cell) == 10);
  assert(fabs(cstream_cell_as_decimal(&cell) - 10.0) < 0.00001);
  assert(strcmp(cstream_cell_as_string(&cell), "10") == 0);

  /* DECIMAL */

  cstream_cell_set_decimal(&cell, -20.55, 2, false);
  assert(cell.type == CSTREAM_TYPE_DECIMAL);
  assert(cstream_cell_as_int64(&cell) == -20);
  assert(fabs(cstream_cell_as_decimal(&cell) - -20.55) < 0.00001);
  assert(strncmp(cstream_cell_as_string(&cell), "-20.55", 6) == 0);

  cstream_cell_set_decimal(&cell, 20.55, 2, false);
  assert(cell.type == CSTREAM_TYPE_DECIMAL);
  assert(cstream_cell_as_int64(&cell) == 20);
  assert(fabs(cstream_cell_as_decimal(&cell) - 20.55) < 0.00001);
  assert(strncmp(cstream_cell_as_string(&cell), "20.55", 5) == 0);

  /* STRING */

  cstream_cell_set_string(&cell, "giant chicken wings", false);
  assert(cell.type == CSTREAM_TYPE_STRING);
  assert(cstream_cell_as_int64(&cell) == 0);
  assert(fabs(cstream_cell_as_decimal(&cell) - 0.0) < 0.00001);
  assert(strcmp(cstream_cell_as_string(&cell), "giant chicken wings") == 0);

  /* NULL */
  cstream_cell_set_null(&cell, false);
  assert(cstream_cell_isnull(&cell) == true);

  LOG_OK("tests/cell/conversions.c --- All assertions passed.");
  return 0;
}
