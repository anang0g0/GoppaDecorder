//学校で習った知識を使ったら問題解決できました。大学行っといてよかったｗ


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "chash.c"

//#define D 4096
#define F 12

unsigned char a[F][F]={0};
unsigned char cc[F][F]={0};
unsigned char bb[F][F]={0};
unsigned char cl[F][F];
unsigned char s[F]={0};

  //{{0,1,0,1},{1,0,0,1},{0,0,1,0},{0,0,1,1}};
//{{0,1,1,1},{1,0,1,1},{0,0,1,1},{1,0,0,1}}; //{{1,2,0,-1},{-1,1,2,0},{2,0,1,1},{1,-2,-1,1}}; //入力用の配列

//extern unsigned long xor128();
//extern void makeS();


void g2(){
  int i,j,k,flg,count=0;

/*
while(1){
    memset(cc,0,sizeof(cc));
    for(j=0;j<F;j++)
    s[j]=rand()%2;
    flg=0;
    for(k=0;k<F;k++){
        for(j=0;j<F;j++)
        if(cc[k][j]!=s[j])
            flg=1;
    }
    if(flg==1){
    for(j=0;j<F;j++)
    cc[count][j]=s[j];
    count++;
    }
    if(count==F)
    break;
}
*/
//memset(a,0,sizeof(a));
//memset(cc,0,sizeof(cc));
#pragma omp parallel for    
  for(i=0;i<F;i++){
    a[i][i]=1;
    bb[i][i]=1;
  }
  
#pragma omp parallel for private(j)
  for(i=0;i<F;i++){
    for(j=i+1;j<F;j++){
      a[i][j]=xor128()%2;
      
    }  
  }
  
#pragma omp parallel for private(j)
  for(i=0;i<F;i++){
    for(j=i+1;j<F;j++){
      bb[j][i]=xor128()%2;
    }
  }
//a[1][1]=0;
  int l;

  for(i=0;i<F;i++){
      for(j=0;j<F;j++)
      cc[i][j]=rand()%2;
  }
  /*
#pragma omp parallel for private(j,k)
  for(i=0;i<F;i++){
#pragma omp parallel num_threads(8)
    {
    for(j=0;j<F;j++){
      l=0;
      for(k=0;k<F;k++){
	cc[i][j]^=bb[i][k]&a[k][j];
	//l^=bb[i][k]&a[k][j];
      }
      //cc[i][j]=l;
    }
    }
  }
cc[0][0]=rand()%2;
*/
}


void makeS(){
  int i,j,k,l;
  unsigned char **b;
  unsigned char dd[F]={0};
  unsigned int flg=0,count=0;
  time_t t;
  FILE *fq;
  unsigned char inv_a[F][F]={0}; //ここに逆行列が入る
  unsigned char buf; //一時的なデータを蓄える
  int n=F;  //配列の次数


  b=malloc(F*sizeof(unsigned char *));
  for(i=0;i<F;i++)
    b[i]=malloc(F*sizeof(unsigned char *));
  
  while(flg!=F || count!=F*F-F)
  //while(count!=F*F-F)
  //while(flg!=F)
  {
labo:
//memset(b,0,sizeof(b));
    flg=0;
    srand(clock()+time(&t));

    g2();
    printf("end of g2\n");
    //exit(1);
    
    flg=0;
#pragma omp parallel for private(j)
  for(i=0;i<F;i++){

    for(j=0;j<F;j++){
      //  printf("%d,",a[i][j]);
      cl[i][j]=cc[i][j];
      dd[j]=cc[i][j];

    }
    //  printf("\n");
  }

//memset(inv_a,0,sizeof(inv_a));  
for(i=0;i<F;i++){
    for(j=0;j<F;j++)
    inv_a[i][j]=0;
}
//単位行列を作る
#pragma omp parallel for private(j)
for(i=0;i<F;i++){
 for(j=0;j<F;j++){
 inv_a[i][j]=(i==j)?1.0:0.0;
 }
 }


//掃き出し法

for(i=0;i<F;i++){
  if(cc[i][i]==0){
  j=i;
  while(cc[j][i]==0 && j<F){
    j++;
    //buf=cc[j++][i];
  }
//  cc[i][i]=1;
  //  printf("j=%d\n",j);
  
  //  exit(1);
  //#pragma omp parallel for  
  if(j>=F)
  goto labo;
 for(k=0;k<F;k++){
 cc[i][k]^=cc[j][k]%2;
 inv_a[i][k]^=inv_a[j][k];
 }
 
  }
  //  exit(1);
  
 if(cc[i][i]==1){
 for(l=i+1;l<F;l++){
   if(cc[l][i]==1){
     //#pragma omp parallel for  
     for(k=0;k<F;k++){
     cc[l][k]^=cc[i][k]%2;
     inv_a[l][k]^=inv_a[i][k];
     }
   }
 }

 // printf("@%d\n",i);
 }
 // printf("@i=%d\n",i);
 }

//  exit(1);
//#pragma omp parallel for private(j,k)
 for(i=1;i<F;i++){
   for(k=0;k<i;k++){
     if(cc[k][i]==1){
       for(j=0;j<F;j++){
       // if(a[k][i]==1){
	 cc[k][j]^=cc[i][j]%2;
	 inv_a[k][j]^=inv_a[i][j];
	 //}
     }
     }

   }
}

 

//逆行列を出力
for(i=0;i<F;i++){
 for(j=0;j<F;j++){
  printf("a %d,",inv_a[i][j]);
 }
 printf("\n");
 }
 
// exit(1);
//検算

#pragma omp parallel for private(j,k)
 for(i=0;i<F;i++){
#pragma omp parallel num_threads(8) //private(j,k)
     {
     for(j=0;j<F;j++){
       l=0;
       //#pragma omp parallel for reduction(^:l)
       for(k=0;k<F;k++){
	 b[i][j]^=(cl[i][k]&inv_a[k][j]);
	 //l^=(cl[i][k]&inv_a[k][j]);
       }
       //b[i][j]=l;
     }
     }
 }
 

 for(i=0;i<F;i++){
   //   printf("%d",b[i][i]);
   //printf("==\n");
  if(b[i][i]==1){
    //printf("baka");
     //   exit(1);
     flg++;
  } 
 }
 count=0;

 for(i=0;i<F;i++){
   for(j=0;j<F;j++){
     if(b[i][j]==0 && i!=j)
       count++;
   }   
 }
  
  //if(cl[0][0]>0)
  //  goto labo;
 //
 printf("S[K][K]=\n{\n");
 if(flg==F && count==(F*F-F))
//if(flg==F)
 {
  for(i=0;i<F;i++){
    printf("{");
    for(j=0;j<F;j++){
      printf("%d,",cl[i][j]);
      dd[j]=cl[i][j];
    }
  
    printf("},\n");
  }
  printf("};\n");
 
  
  printf("Sa[K][K]=\n{\n");
 if(flg==F && count==F*F-F){
  for(i=0;i<F;i++){
    printf("0b");
    for(j=0;j<F;j++){
      printf("%d",cl[i][j]);
      dd[j]=cl[i][j];
    }
  
    printf(",\n");
  }
  printf("};\n");
 }
  //exit(1);
  printf("inv_S[K][K]=\n{\n");
  for(i=0;i<F;i++){
    printf("{");
    for(j=0;j<F;j++){
      printf("%d,",inv_a[i][j]);
      dd[j]=inv_a[i][j];
    }
    printf("},\n");
  }
  printf("};\n");
 
  
  printf("inv_Sa[K][K]=\n{\n");
  for(i=0;i<F;i++){
    printf("0b");
    for(j=0;j<F;j++){
      printf("%d",inv_a[i][j]);
      dd[j]=inv_a[i][j];
    }
    printf(",\n");
  }
  printf("};\n");
     
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d, ",b[i][j]);
    printf("\n");
  }
  //  exit(1);   
 }
  
 }

 /*
  fq=fopen("S.key","wb");
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      dd[j]=cl[i][j];
    fwrite(dd,1,n,fq);
    
  }
  fclose(fq);

  fq=fopen("inv_S.key","wb");
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      dd[j]=inv_a[i][j];
    fwrite(dd,1,n,fq);  
  }
  fclose(fq);
*/

  free(b);
  
}


main(){

makeS();

}