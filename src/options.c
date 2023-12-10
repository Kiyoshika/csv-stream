#include "options.h"
#include "log.h"

struct cstream_options_t cstream_options_init() {
  return (struct cstream_options_t){
      .null_text = {0}, .delimiter = ',', .has_header = true};
}

void cstream_options_set_null_text(struct cstream_options_t *options,
                                   const char *null_text) {
  if (!options) {
    LOG_WARNING("cstream_options_set_null_text", "options is a NULL pointer.");
    return;
  }
  if (!null_text) {
    LOG_WARNING("cstream_options_set_null_text",
                "null_text is a NULL pointer.");
    return;
  }
  memset(options->null_text, 0, CSTREAM_NULL_TEXT_LEN);
  strncat(&options->null_text[0], null_text, CSTREAM_NULL_TEXT_LEN - 1);
}

void cstream_options_set_delimiter(struct cstream_options_t *options,
                                   const char delimiter) {
  if (!options) {
    LOG_WARNING("cstream_options_set_delimiter",
                "passed a NULL pointer; ignored.");
    return;
  }
  options->delimiter = (char)delimiter;
}

void cstream_options_set_header(struct cstream_options_t *options,
                                const bool has_header) {
  if (!options) {
    LOG_WARNING("cstream_options_set_header",
                "options is a NULL pointer; ignored.");
    return;
  }
}
