#ifndef CSTREAM_H
#define CSTREAM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cell.h"
#include "file.h"
#include "options.h"

// The core data structure for a file reader.
//
// Both full and partial streams can be created with this data structure.
// Meaning you can stream the entire file or only specific columns/rows
//
// If reading a full stream, column_indices will stay NULL. Otherwise, it will
// contain the indices to the columns of interest to read.
struct cstream_t {
  struct cstream_file_t file;
  struct cstream_options_t options;
  struct cstream_cell_t cell;
  size_t* column_indices;
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

// Open a full stream to the file to read all columns.
// THIS MUST BE CLOSED WITH cstream_close()
void
cstream_open_full(
	struct cstream_t* stream,
	const char* filepath);

// Get the next row in a stream.
// Returns true if row was obtained, false otherwise (e.g., end of file)
bool
cstream_next_row(
	struct cstream_t* stream);

// Get the next column cel in a stream.
// Returns a pointer to the cell on success, returns NULL if end of columns was reached.
struct cstream_cell_t*
cstream_next_column(
	struct cstream_t* stream);

void
cstream_close(
	struct cstream_t* stream);

#endif

