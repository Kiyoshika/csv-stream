#include "cstream.h"

bool
cstream_init(
  struct cstream_t* stream) {
  if (!stream) {
    fprintf(stderr, "cstream_init: WARNING: stream is a NULL pointer; ignored.\n");
    return false;
  }

  struct cstream_file_row_t row = {
	  .content = NULL,
	  .len = 0
  };

  struct cstream_file_t file = {
	  .file = NULL,
	  .current_row = row
  };

  struct cstream_cell_t cell;
  if (!cstream_cell_init(&cell)) {
    fprintf(stderr, "cstream_init: WARNING: creating cell failed.\n");
    return false;
  }

  *stream = (struct cstream_t){
	.file = file,
    .options = cstream_options_init(),
    .cell = cell,
	.column_indices = NULL,
  };

  return true;
}

void
cstream_open_full(
	struct cstream_t* stream,
	const char* filepath) {

	char delim = stream->options.delimiter;

	cstream_file_open(stream, filepath);

	// skip header
	if (stream->options.has_header) {
		cstream_file_readline(stream);
	}
}

bool
cstream_next_row(
	struct cstream_t* stream) {
	int read = cstream_file_readline(stream);
	printf("ROW: %s\n", stream->file.current_row.content);
	return read != -1;
}

struct cstream_cell_t*
cstream_next_column(
	struct cstream_t* stream) {
	// TODO:
	return NULL;
}

void
cstream_close(
	struct cstream_t* stream) {
	cstream_file_close(stream);
}
