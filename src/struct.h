#define DEG K*E

/* -*- mode: C; coding:utf-8 -*- */

//monomial
typedef struct
{
  unsigned short n; //単項式の次数
  unsigned short a; //単項式の係数
} oterm;

//polynomial
typedef struct
{
  oterm t[DEG]; //単項式の配列として多項式を表現する
} OP;

typedef struct 
{
  unsigned short x[DEG]; //配列の添字を次数に、配列の値を係数に持つ多項式の表現
} vec;

typedef struct {
  OP q;
  OP r;
} rem;

typedef struct
{
  unsigned short v[N];
  int f;
} MT;

//extra gcd
typedef struct
{
  OP u; //inverse of polynomial?
  OP v; //error locater
 OP d; //gcd
} EX;

typedef union
{ //test(SIMN)
  unsigned long long int u[4];
  unsigned short s[16];
} SU;

typedef union
{
  unsigned long long int u[8];
  unsigned char d[64];
} arrayul;

typedef struct a4
{
  unsigned char ar[4];
} array;

typedef struct a8
{
  unsigned char ar[8];
} array8;

typedef struct
{
  unsigned int h[16];
} array16;

typedef struct aN
{
  unsigned char ar[N];
} arrayn;

typedef struct pub
{
  unsigned char a[N];
  unsigned char b[N];
} set;


typedef struct {
  unsigned short x[N][N];
  OP f;
  int reg;
  int row; //行
  int col; //列
} MTX;


typedef struct {
  unsigned short x[N][K];
  unsigned char z[N][K*E];
  unsigned char w[K*E][K*E];
  int i;
  int rank;
} MAT;
