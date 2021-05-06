#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "8192.h"

//符号のパラーメータの指定。通常[N,K,T]として、
//Nは符号の長さ、Kが符号の次元、Tは訂正エラー数
//を表す。ここではDは符号長にしている。
#define N 256  // (^^;)?
#define M 256 //有限体の元の数
#define K (16) //符号の次元
#define DEG (K * E)
#define T (K / 2) //エラーの数
#define E (8)    //拡大体のビット数
#define D (256)  //符号長（短縮符号）
//#define F E *K    //2040
#define NN 16


unsigned char tmp[N][E * K] = {0};
//unsigned char pub[E * K][N] = {0};
//unsigned char BH[E * K][N] = {0};
static unsigned short c[E * K + 1] = {0};
unsigned short mat[N][K*E] = {0};
unsigned short ma[N][K*E] = {0};
unsigned short bm[N][K*E]={0};
unsigned short bm2[N][K*E]={0};

//unsigned short syn[K]={0};
unsigned short P[N] = {0};
unsigned short inv_P[N] = {0};
unsigned short uu = 0;
