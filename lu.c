#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 2040

unsigned char a[N][N]={0};
unsigned char cc[N][N]={0};
unsigned char bb[N][N]={0};

  //{{0,1,0,1},{1,0,0,1},{0,0,1,0},{0,0,1,1}};
//{{0,1,1,1},{1,0,1,1},{0,0,1,1},{1,0,0,1}}; //{{1,2,0,-1},{-1,1,2,0},{2,0,1,1},{1,-2,-1,1}}; //入力用の配列
unsigned char inv_a[N][N]; //ここに逆行列が入る
unsigned char buf; //一時的なデータを蓄える
int i,j,k; //カウンタ
int n=2040;  //配列の次数

unsigned long xor128(void)
{
  unsigned int a=0;
  static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned long t;
    a=rand();
    t=(a^(a<<11));a=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}


void g2(){
  int i,j,k;


  
  for(i=0;i<N;i++){
    a[i][i]=1;
    bb[i][i]=1;
  }
  for(i=0;i<N;i++){
    for(j=i+1;j<N;j++){
      a[i][j]=xor128()%2;
      
    }  
  }
  /*
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%d,",a[i][j]);
    printf("\n");
  }
  printf("\n");
  */
  for(i=0;i<N;i++){
    for(j=i+1;j<N;j++){
      bb[j][i]=xor128()%2;
    }
  }
  /*  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%d,",bb[i][j]);
    printf("\n");
  }
  printf("\n");
  //    exit(1);
  */
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      for(k=0;k<N;k++){
	cc[i][j]^=bb[i][k]&a[k][j];
      }
    }
  }
  /*
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%d,",cc[i][j]);
    printf("\n");
  }
  printf("\n");
  */
}


void main(){
  int i,j,k,l,ii;
  unsigned char b[N][N]={0};
  unsigned char c[N][N]={0};
  unsigned int flg=0,count=0;
  time_t t;

  
  while(flg<N || count!=N*N-N){
    
    srand(clock()+time(&t));

    g2();
    //
    //  exit(1);

    /*
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      a[i][j]=xor128()%2;
  }
    */
  flg=0;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      //  printf("%d,",a[i][j]);
      c[i][j]=cc[i][j];
    }
    //  printf("\n");
  }

  
//単位行列を作る
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
 inv_a[i][j]=(i==j)?1.0:0.0;
 }
}
/*
 printf("\n");
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     printf("%d,",a[i][j]);
   printf("\n");
 }
*/
//掃き出し法
for(i=0;i<n;i++){
  if(cc[i][i]==0){
  j=0;
  while(cc[j][i]==0){
    buf=cc[j++][i];
  }
  //  printf("j=%d\n",j);
  
  //  exit(1);
 for(k=0;k<n;k++){
 cc[i][k]^=cc[j][k];
 inv_a[i][k]^=inv_a[j][k];
 }
 /* 
 for(j=0;j<n;j++){
   for(k=0;k<n;k++)
     printf("%d",cc[j][k]);
   printf("\n");
   }
 for(j=0;j<n;j++){
   for(k=0;k<n;k++)
     printf("%d,",inv_a[j][k]);
   printf("\n");
   }
 */
  }
  //  exit(1);
  
 if(cc[i][i]==1){
 for(l=i+1;l<n;l++){
   if(cc[l][i]==1){
     for(k=0;k<n;k++){
     cc[l][k]^=cc[i][k];
     inv_a[l][k]^=inv_a[i][k];
     }
   }
 }

 // printf("@%d\n",i);
 }
 // printf("@i=%d\n",i);
 }
  
//  exit(1);
 for(i=1;i<n;i++){
   for(k=0;k<i;k++){
     if(cc[k][i]==1){
       for(j=0;j<n;j++){
       // if(a[k][i]==1){
	 cc[k][j]^=cc[i][j];
	 inv_a[k][j]^=inv_a[i][j];
	 //}
     }
     }
     /*  
   printf("i=%d\n",i);
   for(l=0;l<n;l++){
     for(ii=0;ii<n;ii++)
       printf("%d",cc[l][ii]);
     printf("\n");
   }
   for(l=0;l<n;l++){
     for(ii=0;ii<n;ii++)
       printf("%d, ",inv_a[l][ii]);
     printf("\n");
   }
     */
   }
 }
 
 /*
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     printf("%d,",cc[i][j]);
   printf("\n");
 }
 //   exit(1);
 
//逆行列を出力
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
  printf(" %d,",inv_a[i][j]);
 }
 printf("\n");
 }
 */
// exit(1);
//検算
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     for(k=0;k<n;k++){
       b[i][j]^=(c[i][k]&inv_a[k][j]);
     }
   }
 }
 /*
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     printf("%d,",b[i][j]);
   printf("\n");
  
 }
 */
 for(i=0;i<N;i++){
   //   printf("%d",b[i][i]);
   //printf("==\n");
  if(b[i][i]==1){
    //printf("baka");
     //   exit(1);
     flg++;
  } 
 }
 count=0;
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     if(b[i][j]==0 && i!=j)
       count++;
   }   
 }
 //
 if(flg==N && count==N*N-N){
  for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      printf("%d",c[i][j]);
    printf("\n");
  }
  for(i=0;i<n;i++){
    for(j=0;j<N;j++)
      printf("%d,",inv_a[i][j]);
    printf("\n");
  }
  for(i=0;i<n;i++){
    for(j=0;j<N;j++)
      printf("%d, ",b[i][j]);
    printf("\n");
  }
    exit(1);   
 }
  
 }

}
