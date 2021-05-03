all:
	gcc-10 -Wall -g -pg -O3  -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp main.c

amd:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp main.c

clang:
	clang -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp main.c

old:
	clang -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op_old.c

nie:
	gcc-10 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp Niederreiter.c

fal:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp falos.c

pat:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp Patterson.c

mot:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

clean:
	rm -f a.out

