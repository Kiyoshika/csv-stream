#include "cstream.h"
#include "log.h"
#include <assert.h>

int main() {
	struct cstream_t stream;
	assert(cstream_init(&stream) == true);

	cstream_open_full(&stream, "./tests/cstream/test.csv");
	while (cstream_next_row(&stream)) {
		printf("%s\n", cstream_get_row_content(&stream));
	}
	cstream_close(&stream);

	LOG_OK("tests/cstream/full_stream.c --- All assertions passed.");
	return 0;
}
