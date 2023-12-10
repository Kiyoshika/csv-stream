#include "file.h"
#include "cstream.h"
#include "log.h"

#define CHECK_STREAM_PTR(func_name, return_value)                              \
  {                                                                            \
    if (!stream) {                                                             \
      LOG_WARNING(func_name, "stream pointer is NULL.");                       \
      return return_value;                                                     \
    }                                                                          \
  }

#define CHECK_FILE_PTR(func_name, return_value)                                \
  {                                                                            \
    if (!stream->file.file) {                                                  \
      LOG_WARNING(func_name, "file pointer is NULL.");                         \
      return return_value;                                                     \
    }                                                                          \
  }

void cstream_file_open(struct cstream_t *stream, const char *filepath) {
  CHECK_STREAM_PTR("cstream_file_open", );

  stream->file.file = fopen(filepath, "r");

  if (!stream->file.file) {
    LOG_WARNING("cstream_file_open", "couldn't open file pointer.");
    return;
  }
}

int cstream_file_readline(struct cstream_t *stream) {
  CHECK_STREAM_PTR("cstream_file_readline", -1);
  CHECK_FILE_PTR("cstream_file_readline", -1);
  return getline(&stream->file.current_row.content,
                 &stream->file.current_row.len, stream->file.file);
}

void cstream_file_close(struct cstream_t *stream) {
  CHECK_STREAM_PTR("cstream_file_close", );
  CHECK_FILE_PTR("cstream_file_close", );
  fclose(stream->file.file);
}
