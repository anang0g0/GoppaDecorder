
all:
	clang-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op2.c

amd:
	clang-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

alg:
	clang-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp alg.c

ori:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op3.c

oo:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp oo.c

amd:
	clang-10 -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

gcc: 
	gcc -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

train:
	clang-10 -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp train.c

stable:
	clang-10 -Wall -O3 -g -pg -mtune=native -march=native -ffast-math -funroll-loops -fopenmp oplib.c

clean:
	rm -f a.out
