#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "8192.h"

//符号のパラーメータの指定。通常[N,K,T]として、
//Nは符号の長さ、Kが符号の次元、Tは訂正エラー数
//を表す。ここではDは符号長にしている。
#define N 16  // (^^;)?
#define M 16  //有限体の元の数
#define K (6) //符号の次元
#define DEG (K * 2)
#define T (K / 2) //エラーの数
#define E (4)    //拡大体のビット数
#define D (16)  //符号長（短縮符号）
#define F E *K    //2040

unsigned char tmp[E * K][N] = {0};
//unsigned char pub[E * K][N] = {0};
//unsigned char BH[E * K][N] = {0};
static unsigned short c[2 * K + 1] = {0};
unsigned short mat[N][K*2] = {0};
unsigned short ma[N][K*2] = {0};
unsigned short bm[N][K*2]={0};
unsigned short bm2[N][K*2]={0};

//unsigned short syn[K]={0};
unsigned short P[N] = {0};
unsigned short inv_P[N] = {0};
unsigned short uu = 0;
