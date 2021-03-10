
all:
	clang-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

amd:
	clang-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp experimental.c

gcc: 
	gcc -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp gcc.c

clean:
	rm -f a.out
