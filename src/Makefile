
all:
	clang-10 -Wall -g -pg -O3 -mtune=znver1 -march=znver1 -ffast-math -funroll-loops  -fopenmp op.c

gcc:
	gcc -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

stable:
	gcc -Wall -O3 -g -pg -mtune=native -march=native -ffast-math -funroll-loops -fopenmp oplib.c

clean:
	rm -f a.out
