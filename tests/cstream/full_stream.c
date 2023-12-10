#include "cstream.h"
#include "log.h"
#include <assert.h>

int main() {
	struct cstream_t stream;
	assert(cstream_init(&stream) == true);

	cstream_open_full(&stream, "./tests/cstream/test.csv");
	while (cstream_next_row(&stream));
	cstream_close(&stream);
	return 0;
}
