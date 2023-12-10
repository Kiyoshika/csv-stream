#ifndef CSTREAM_FILE_H
#define CSTREAM_FILE_H

#include <stdio.h>
#include <stddef.h>

// forward declaration
struct cstream_t;

// Information about a given row in a file containing the
// text content of the row along as its length.
struct cstream_file_row_t {
	char* content;
	size_t len;
};

// A simple wrapper around a file pointer that holds a pointer
// to the file and the current row content.
struct cstream_file_t {
	FILE* file;
	struct cstream_file_row_t current_row;
};

void
cstream_file_open(
	struct cstream_t* stream,
	const char* filepath);

int
cstream_file_readline(
	struct cstream_t* stream);

void
cstream_file_close(
	struct cstream_t* stream);

#endif
