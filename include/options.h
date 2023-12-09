#ifndef CSTREAM_OPTIONS_H
#define CSTREAM_OPTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define CSTREAM_NULL_TEXT_LEN 16

// Holds the configurable options for a cstream_t struct.
struct cstream_options_t {
  char null_text[CSTREAM_NULL_TEXT_LEN];
  char delimiter;
  bool has_header;
};

// Create a new cstream options struct with the default options.
//
// DEFAULTS:
// null_text: none set
// delimiter: ','
// has_header: true

struct cstream_options_t
cstream_options_init();

// Set the value of text that represents a null value
// with a max of 16 chars including null terminator.
//
// If a value encountered in the file equals this value,
// then is_null is set to true in the cell.
//
// NOTE: empty cells (i.e., cells with length of 0) will always be null,
// so this is to handle the special cases of software that output special
// values like "(null)" or "NA" to represent null values.
void
cstream_options_set_null_text(
  struct cstream_options_t* options,
  const char* null_text);

// Set the value of the delimiter for the file.
void
cstream_options_set_delimiter(
  struct cstream_options_t* options,
  const char delimiter);

// Set whether or not the file contains a header line
void
cstream_options_set_header(
  struct cstream_options_t* options,
  const bool has_header);

#endif

