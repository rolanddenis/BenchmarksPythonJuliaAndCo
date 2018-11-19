all: kernel_run.so

kernel_run.so: kernel_run.py
	pythran -O3 -march=native -mtune=native -fopenmp -DUSE_BOOST_SIMD kernel_run.py

clean:
	rm -f kernel_run.so

.PHONY: all clean
