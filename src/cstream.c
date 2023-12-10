#include "cstream.h"
#include "log.h"

#define CHECK_STREAM_PTR(func_name, return_value)                              \
  {                                                                            \
    if (!stream) {                                                             \
      LOG_WARNING(func_name, "stream is a NULL pointer.");                     \
      return return_value;                                                     \
    }                                                                          \
  }

bool cstream_init(struct cstream_t *stream) {
  CHECK_STREAM_PTR("cstream_init", false);

  struct cstream_file_row_t row = {.content = NULL, .len = 0};

  struct cstream_file_t file = {.file = NULL, .current_row = row};

  struct cstream_cell_t cell;
  if (!cstream_cell_init(&cell)) {
    LOG_WARNING("cstream_init", "creating cell failed.");
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

void cstream_open_full(struct cstream_t *stream, const char *filepath) {

  cstream_file_open(stream, filepath);

  // skip header
  if (stream->options.has_header) {
    cstream_file_readline(stream);
  }
}

bool cstream_next_row(struct cstream_t *stream) {
  return cstream_file_readline(stream) != -1;
}

struct cstream_cell_t *cstream_next_column(struct cstream_t *stream) {
  // TODO: implement this
  return NULL;
}

void cstream_close(struct cstream_t *stream) { cstream_file_close(stream); }

const char *cstream_get_row_content(const struct cstream_t *stream) {
  CHECK_STREAM_PTR("cstream_get_row_content", NULL);
  return stream->file.current_row.content;
}

const char *cstream_get_cell_content(const struct cstream_t *stream) {
  CHECK_STREAM_PTR("cstream_get_cell_content", NULL);
  return stream->cell.value;
}
