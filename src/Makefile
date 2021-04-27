all:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

amd:
	clang-11 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp experimental.c

clang: 
	clang-11 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op.c

test:
	gcc-10 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp ni.c

oo:
	gcc-10 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp oo.c

nie:
	gcc-10 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp Niederreiter.c

op:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp fangataufa.c

pat:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp Patterson.c

clean:
	rm -f a.out

