#!/bin/bash
for filename in ./src/*.c; do
	echo "Formatting: " ${filename}
	clang-format --style=llvm ${filename} > ${filename}.bak
	mv ${filename}.bak ${filename}
done
