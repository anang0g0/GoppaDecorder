
all:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

amd:
	clang-11 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp experimental.c

clang: 
	clang -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op.c

oo: 
	clang-11 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op2.c

ae:
	clang-11 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op4.c

clean:
	rm -f a.out

