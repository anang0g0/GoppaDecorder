//#include "global.h"

//符号のパラーメータの指定。通常[N,K,T]として、
//Nは符号の長さ、Kが符号の次元、Tは訂正エラー数
//を表す。ここではDは符号長にしている。
#define N 6688 // (^^;)?
#define M 8192 //有限体の元の数
//#define K (128*2) //符号の次元
//#define DEG (2*K) //多項式の次数
#define T (K/2) //エラーの数
#define E (13) //拡大体のビット数
#define D (6688) //符号長（短縮符号）
#define F 256*13 //2040



extern unsigned char tmp[E * K][N];
extern unsigned char pub[E * K][N];
extern unsigned char BH[E * K][N];
extern unsigned short c[2 * K + 1];
extern unsigned short mat[K][N];
extern unsigned short m2[K][N];



extern unsigned char a[F][F];
extern unsigned char cc[F][F];
extern unsigned char bb[F][F];
extern unsigned char cl[F][F];


extern unsigned short syn[K];
extern unsigned char A[N][N];
extern unsigned short P[N];
extern unsigned short inv_P[N];

extern unsigned short uu;
extern unsigned char cl[F][F];



extern int mltn(int n,int x);
extern int mlt(int x, int y);
extern unsigned long xor128(void);
extern void ginit (void);
extern unsigned short oinv (unsigned short a);
extern unsigned short equ (unsigned short a, unsigned short b);
extern int distance (OP f);
extern int terms (OP f);
extern int odeg (OP f);
extern int deg (vec a);
extern vec o2v (OP f);
extern OP v2o (vec a);
extern vec Setvec (int n);
extern void oprintpol (OP f);
extern void printpol (vec a);
extern oterm LT (OP f);
extern oterm LT2 (OP f);
extern OP oadd (OP f, OP g);
extern OP sort (OP f);
extern OP oterml (OP f, oterm t);
extern OP omul (OP f, OP g);
extern oterm LTdiv (OP f, oterm t);
extern OP coeff (OP f, unsigned short d);
extern OP omod (OP f, OP g);
extern OP odiv (OP f, OP g);
extern unsigned short trace (OP f, unsigned short x);
extern OP inv (OP a, OP n);
extern OP vx(OP f,OP g);
extern EX xgcd (OP f, OP g);
extern OP bibun (vec a);
extern vec chen (OP f);
extern OP setpol (unsigned short *f, int n);
extern void det (unsigned short g[]);
extern void key2 (unsigned short g[]);
extern int isqrt (unsigned short u);
extern OP osqrt(OP f,OP w);

//extern unsigned short g[K+1];

extern void g2();
extern void makeS();

extern OP decode (OP f, OP s);
extern int pattarson (OP w, OP f);
