/* generate GF(2^n) using irreducible polynomial */
//ゼフ対数表を作るためのプログラム。正規基底を生成します。


#include <stdio.h>
#include <stdlib.h>

#define O 8192

/* generate Galois Field over GF(2^?) */
static const char *normal[14]={
  "1011",
  //"11001", /* GF(16) */
  "10011",
  "110111",
  "1100001",
  "11000001",
  "110101001",
//"100011011",
  "1100110001",
  "11000010011",
  "110000001101",
  "1100101000001", /* 4096 */
//"11011000000001", /* 8192 */
  "10000000011011",/* Classic McEliece */
  "110000100010001",
  "1100000000000001",
  "11010000000010001"};

unsigned int gf[O],fg[O];


void makefg(int n){
int i,j;

for(i=0;i<n;i++){
  for(j=0;j<n;j++){
    if(gf[i]==j)
      fg[j]=i;
  }
}
  printf("unsigned short fg[%d]={",O);
  for(i=0;i<O;i++)
  printf("%d,",fg[i]);
printf("};\n");

 
return;
}


void mkgf(int n)
{
  int i,j,bit,count=0;
  unsigned int pol,N,M,L;


  for(i=0;i<13;i++)
    pol=strtoul(normal[i],(char **)NULL,2);


  /* define pol */
  switch(n){

  case 8:
    pol=strtoul(normal[0],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 16:
    pol=strtoul(normal[1],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 32:
    pol=strtoul(normal[2],(char **)NULL,2);
printf("%d\n",n);
    break;

  case 64:
    pol=strtoul(normal[3],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 128:
   pol=strtoul(normal[4],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 256:
    pol=strtoul(normal[5],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 512:
    pol=strtoul(normal[6],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 1024:
    pol=strtoul(normal[7],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 2048:
    pol=strtoul(normal[8],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 4096:
    pol=strtoul(normal[9],(char **)NULL,2);
    printf("%d\n",n);
    break;

  case 8192:
   pol=strtoul(normal[10],(char **)NULL,2);
    printf("%d\n",n);
    break;

  default : /* 16384 */
    pol=strtoul(normal[11],(char **)NULL,2);
    printf("%d\n",n);
    break;
  }


  L=1;
  while(pol>L){
    L=(L<<1);
    count++;
  }
  L=(L>>1);
  N=pol^L;
  M=pol;
  //  printf("%u %u %u\n",N,L,M);

  gf[0]=0;
  bit=1;
  for(i=1;i<L;i++){
    if(bit>L-1){
      bit=bit-L;
      bit=bit^N;
    }
    gf[i]=bit;
    bit=(bit<<1);
  }
  printf("unsigned short gf[%d]={",O);
  for(i=0;i<L;i++)
    printf("%u,",gf[i]);
  
  printf("};\n");

}


int main(){
  int i,j,k;

  mkgf(O);
  makefg(O);


return 0;
}
