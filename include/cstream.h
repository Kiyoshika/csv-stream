#ifndef CSTREAM_H
#define CSTREAM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cell.h"
#include "options.h"

// The core data structure for a file reader.
//
// Holds a pointer to the file along with options
// that can be configured through cstream_set_...() functions.
//
// Both full and partial streams can be created with this data structure.
// Meaning you can stream the entire file or only specific columns/rows
struct cstream_t {
  FILE *file;
  struct cstream_options_t options;
  struct cstream_cell_t cell;
};

// Create a new cstream struct with the default options
// by passing a struct by address.
//
// Returns true on success and false otherwise (e.g., on allocation
// failures)
//
// NOTE: if you want to run multiple streams in different threads,
// you must make a separate instance of a cstream_t since each struct
// maintains an open file pointer until the stream is closed.
bool
cstream_init(
  struct cstream_t* stream);

#endif

