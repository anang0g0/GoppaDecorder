
all:
<<<<<<< HEAD
<<<<<<< HEAD
=======
	clang -Wall -g -pg -O3  -mtune=narive -march=native -ffast-math -funroll-loops  -fopenmp op.c

amd:
>>>>>>> refs/remotes/origin/main
	clang-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

ori:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp origin.c

oo:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp oo.c
=======
	clang -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op.c

amd:
	clang-10 -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c
>>>>>>> 8e7868be154f4bc49b3de2329ad8286ed0fb8198

gcc:
	gcc -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

train:
	clang-10 -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp train.c

stable:
	clang-10 -Wall -O3 -g -pg -mtune=native -march=native -ffast-math -funroll-loops -fopenmp oplib.c

clean:
	rm -f a.out
