# CSV Stream
This is a data processing library to fully or partially stream CSV files.

## Motivation
Why am I building this?

Professionally, I work as a data scientist and not a software engineer. I work with a lot of data and from time to time I have to write custom algorithms.

In some cases, I would write these algorithms in C/C++ compared to Python if I really need the performance (sometimes Python doesn't cut it).

To make data processing easier for my algorithms, I want a relatively lightwight library to either read full CSV files or partially read them (e.g., a couple columns) with the ability to split these streams into multiple threads (e.g., process 3 independent columns at once) while also keeping the memory footprint fairly small (at least, don't read the entire file into memory).

# Building
In the root directory run `make` which will compile the library into a static library located in the `lib/` directory.

Run `make test` to run all the tests to validate everythign is working.

# Including in other projects
There is currently no global install target for this project (yet?) so the process is a bit manual at the moment...

To include this project in your own C/C++ projects, you can:
1. add this repo as a submodule `git submodule add git@github.com:Kiyoshika/csv-stream.git`
2. `cd csv-stream` and run `make` to build the library
3. in your own `Makefile` add the following additional flags:
	* `-Icsv-stream/include` to your include flag
	* `-Lcsv-stream/lib` to your link directory flag
	* `-lcstream` to your link flag
4. OR if you use CMake, the following should work (hopefully):
   	* `target_include_directories([your target] PUBLIC csv-stream/include)`
   	* `target_link_directories([your target] PUBLIC csv-stream/lib)`
   	* `target_link_libraries([your target] cstream)`

Now you can use `#include "cstream.h"` in your project.
