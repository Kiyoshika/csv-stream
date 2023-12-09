#include "cell.h"

bool
cstream_cell_init(
  struct cstream_cell_t* cell) {
  if (!cell) {
    fprintf(stderr, "cstream_cell_init: WARNING: cell is a NULL pointer; ignored.\n");
    return false;
  }

  char* value = calloc(10, sizeof(char));

  if (!value) {
    fprintf(stderr, "cstream_cell_init: WARNING: value could not be allocated and is NULL.\n");
    return false;
  }

  *cell = (struct cstream_cell_t){
    .is_null = false,
    .type = CSTREAM_TYPE_NOTYPE,
    .value = value
  };
   
   return true;
}

bool
cstream_cell_isnull(
  const struct cstream_cell_t* cell) {
  if (!cell) {
    fprintf(stderr, "cstream_cell_isnull: WARNING: cell is a NULL pointer; returning true.\n"); 
    return true;
  }

  return cell->is_null;
}

int64_t
cstream_cell_as_int64(
  const struct cstream_cell_t* cell) {
  if (!cell) {
    fprintf(stderr, "cstream_cell_as_int64: WARNING: cell is a NULL pointer; returning 0.\n");
    return 0;
  }

  if (!cell->value) {
    fprintf(stderr, "cstream_cell_as_int64: WARNING: cell's value is a NULL pointer; returning 0.\n");
    return 0;
  }
  
   if (cell->value[0] == '\0') {
     fprintf(stderr, "cstream_cell_as_int64: WARNING: cell's value is empty; returning 0.\n");
     return 0;
   }

  char* endptr = NULL;
  int64_t value = strtoll(cell->value, &endptr, 10);
  
  if (strlen(endptr) > 0) {
    fprintf(stderr, "cstream_cell_as_int64: WARNING: cell's value was not a valid integer; returning 0.\n");
    return 0;
  }

  return value;
}

void
cstream_cell_set_int64(
  struct cstream_cell_t* cell,
  const int64_t value,
  const bool write_to_file) {
  if (!cell) {
    fprintf(stderr, "cstream_cell_set_int64: WARNING: cell is a NULL pointer; ignored.\n");
    return;
  }

  int64_t temp_value = (int64_t)value;

  size_t value_len = 1; // initial +1 for null terminator
  if (value < 0) {
    value_len++; // +1 for negative sign
    temp_value = -1 * temp_value; // convert to positive to take log
  }
  value_len += (size_t)(ceil(log10(temp_value)) + 1);

  char* value_str = calloc(value_len, sizeof(char));
  snprintf(value_str, value_len, "%lld", value);

  free(cell->value);
  cell->value = value_str;
}
