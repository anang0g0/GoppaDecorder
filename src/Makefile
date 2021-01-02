
all:
	clang-10 -Wall -g -pg -O3  -mtune=znver1 -march=znver1 -ffast-math -funroll-loops  -fopenmp op.c

ori:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp origin.c

oo:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp oo.c

gcc:
	gcc -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

train:
	clang-10 -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp train.c

stable:
	clang-10 -Wall -O3 -g -pg -mtune=native -march=native -ffast-math -funroll-loops -fopenmp oplib.c

clean:
	rm -f a.out
