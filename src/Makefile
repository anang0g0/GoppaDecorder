all:
	gcc-10 -Wall -g -pg -O3  -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op.c

amd:
	clang-11 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp op.c

clang: 
	clang-11 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op.c

old:
	gcc-10 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp op_old.c

nie:
	gcc-10 -Wall -g -pg -O3 -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp Niederreiter.c

fal:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp fals.c

pat:
	gcc-10 -Wall -g -pg -O3  -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp Patterson.c

clean:
	rm -f a.out

