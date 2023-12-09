#ifndef CSTREAM_CELL_H
#define CSTREAM_CELL_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

// TODO: expand the integer types (uint8, uint16, etc.)
enum cstream_cell_type_e {
  // has no type (default)
  CSTREAM_TYPE_NOTYPE,
  // empty value
  CSTREAM_TYPE_NULL,
  // 64-bit signed integer
  CSTREAM_TYPE_INT,
  // 64-bit decimal value
  CSTREAM_TYPE_DECIMAL,
  // string/text
  CSTREAM_TYPE_STRING
};

// Represents a single cell being read from a file.
// Contains a value associated with a type.
// Value will be heap allocated once during the initialization of
// cstream_init().
struct cstream_cell_t {
  bool is_null;
  enum cstream_cell_type_e type;
  char *value;
};

// Create a new cell struct by passing it by address.
// Returns true if creation was successful, false otherwise
// (e.g., from allocation failure)
bool
cstream_cell_init(
  struct cstream_cell_t* cell);

// Check if the cell value is null
bool
cstream_cell_isnull(
  const struct cstream_cell_t* cell);

// Get the cell value as an integer
int64_t
cstream_cell_as_int64(
  const struct cstream_cell_t* cell);

// Get the cell value as a decimal
double
cstream_cell_as_decimal(
  const struct cstream_cell_t* cell);

// Get the cell value as a string
// WARNING: DO NOT free the value returned from the cell
const char*
cstream_cell_as_string(
  const struct cstream_cell_t* cell);

// Set the value of the cell to an integer value.
// If write_to_file is true, writes the new value to the
// original file.
void
cstream_cell_set_int64(
  struct cstream_cell_t* cell,
  const int64_t value,
  const bool write_to_file);

// Set the value of the cell to a decimal value.
// If write_to_file is true, writes the new value to the
// original file.
void
cstream_cell_set_decimal(
  struct cstream_cell_t* cell,
  const double value,
  const bool write_to_file);

// Set the value of the cell to a string value.
// If write_to_file is true, writes the new value to the
// original file.
void
cstream_cell_set_string(
  struct cstream_cell_t* cell,
  const char* value,
  const bool write_to_file);

#endif
