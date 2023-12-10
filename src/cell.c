#include "cell.h"
#include "log.h"

#define CHECK_CELL_PTR(func_name, return_value) { \
  if (!cell) { \
    fprintf(stderr, YELLOW "%s: WARNING: cell is a NULL pointer.\n" RESET, func_name); \
    return return_value; \
  } \
}

#define CHECK_CELL_VALUE_NON_EMPTY(func_name, return_value) { \
  if (!cell->value) { \
    fprintf(stderr, "%s: WARNING: cell's value is a NULL pointer.\n", func_name); \
    return return_value; \
  } \
 if (cell->value[0] == '\0') { \
   fprintf(stderr, "%s: WARNING: cell's value is empty; returning 0.\n", func_name); \
   return return_value; \
 } \
}

bool
cstream_cell_init(
  struct cstream_cell_t* cell) {
  CHECK_CELL_PTR("cstream_cell_init", false); 

  char* value = calloc(10, sizeof(char));

  if (!value) {
    LOG_WARNING("cstream_cell_init", "value could not be allocated and is NULL.");
    return false;
  }

  *cell = (struct cstream_cell_t){
    .type = CSTREAM_TYPE_NOTYPE,
    .value = value
  };
   
   return true;
}

bool
cstream_cell_isnull(
  const struct cstream_cell_t* cell) {
  CHECK_CELL_PTR("cstream_cell_isnull", true); 
  return cell->type == CSTREAM_TYPE_NULL;
}

int64_t
cstream_cell_as_int64(
  const struct cstream_cell_t* cell) {
  CHECK_CELL_PTR("cstream_cell_as_int64", 0); 
  CHECK_CELL_VALUE_NON_EMPTY("cstream_cell_as_int64", 0); 

  char* endptr = NULL;
  int64_t value = strtoll(cell->value, &endptr, 10);
  return value;
}

double
cstream_cell_as_decimal(
  const struct cstream_cell_t* cell) {
  CHECK_CELL_PTR("cstream_cell_as_decimal", 0.0);
  CHECK_CELL_VALUE_NON_EMPTY("cstream_cell_as_decimal", 0.0);

  char* endptr = NULL;
  double value = strtod(cell->value, &endptr);
  return value;
}

const char*
cstream_cell_as_string(
  const struct cstream_cell_t* cell) {
  CHECK_CELL_PTR("cstream_cell_as_string", "");
  CHECK_CELL_VALUE_NON_EMPTY("cstream_cell_as_string", "");
  return cell->value;
}

// TODO: handle the write_to_file cases in the setters

void
cstream_cell_set_int64(
  struct cstream_cell_t* cell,
  const int64_t value,
  const bool write_to_file) {
  CHECK_CELL_PTR("cstream_cell_set_int64",); 

  cell->type = CSTREAM_TYPE_INT;

  int64_t temp_value = (int64_t)value;

  size_t value_len = 1; // initial +1 for null terminator
  if (value < 0) {
    value_len++; // +1 for negative sign
    temp_value = -1 * temp_value; // convert to positive to take log
  }
  value_len += (size_t)(ceil(log10(temp_value)) + 1);

  char* value_str = calloc(value_len, sizeof(char));
  if (!value_str) {
    LOG_WARNING("cstream_cell_set_int64", "couldn't allocate memory for value.");
    return;
  }
  snprintf(value_str, value_len, "%lld", value);

  free(cell->value);
  cell->value = value_str;
}

void
cstream_cell_set_decimal(
  struct cstream_cell_t* cell,
  const double value,
  const size_t precision,
  const bool write_to_file) {
  CHECK_CELL_PTR("cstream_cell_set_decimal",);

  cell->type = CSTREAM_TYPE_DECIMAL;

  double temp_value = (double)value;
  
  size_t value_len = 2; // initial +2 for null terminator and decimal point
  if (value < 0.0) {
    value_len++; // +1 for negative sign
    temp_value = -1.0 * temp_value; // convert to positive to take log
  }
  value_len += (size_t)(ceil(log10f(temp_value)) + 1) + precision;

  char* value_str = calloc(value_len, sizeof(char));
  if (!value_str) {
    LOG_WARNING("cstream_cell_set_decimal", "couldn't allocate memory for value.");
    return;
  }
  snprintf(value_str, value_len, "%f", value);

  free(cell->value);
  cell->value = value_str;
}

void
cstream_cell_set_string(
  struct cstream_cell_t* cell,
  const char* value,
  const bool write_to_file) {
  CHECK_CELL_PTR("cstream_cell_set_string",);

  cell->type = CSTREAM_TYPE_STRING;

  char* value_str = strdup(value);
  if (!value_str) {
    LOG_WARNING("cstream_cell_set_string", "couldn't allocate memory for value.");
    return;
  }

  free(cell->value);
  cell->value = value_str;
}

void
cstream_cell_set_null(
  struct cstream_cell_t* cell,
  const bool write_to_file) {
  CHECK_CELL_PTR("cstream_cell_set_null",);

  cell->type = CSTREAM_TYPE_NULL;

  free(cell->value);
  cell->value = NULL;
}
