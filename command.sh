#!/bin/sh
#for test in {'a','b','c','d','e','f'}; do mv $test* $test.in; done;
clang++ -std=c++11 -stdlib=libc++ -o pro code.cpp
for test in {'a','b','c','d','e','f'}; do
	echo $test
	./pro < $test.in > $test.out
done

