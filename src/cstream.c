#include "cstream.h"

bool
cstream_init(
  struct cstream_t* stream) {
  if (!stream) {
    fprintf(stderr, "cstream_init: WARNING: stream is a NULL pointer; ignored.\n");
    return false;
  }

  struct cstream_cell_t cell;
  if (!cstream_cell_init(&cell)) {
    fprintf(stderr, "cstream_init: WARNING: creating cell failed.\n");
    return false;
  }

  *stream = (struct cstream_t){
    .file = NULL,
    .options = cstream_options_init(),
    .cell = cell
  };

  return true;
}
