#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "sha3.h"


#define N 6688
#define T 128

void main(void){
  int i,j,k,l,b;
  unsigned short zz[6688]={0};
  uint8_t *hash;
  sha3_context c;
  int image_size=512;
  time_t t;
  FILE *fp,*fq;
  
  
  srand(clock()+time(&t));
  
for (i = 0; i < N; i++)
    zz[i] = 0;
  
  j = 0;
  while (j < T * 2)
    {
      l = xor128 () % N;
      printf ("l=%d\n", l);
      if (0 == zz[l])
	{
	  zz[l] = 1;
	  j++;
	}
    }
  
  //printf("%d",zz[i]);
  //printf("\n");
  //exit(1);
  
  fp=fopen("data.bin","rb");
  fq=fopen("test.dat","wb");
  //exit(1);
  
  
  unsigned char buf[10000],buf1[10]={0},tmp[64]={0};
  
  for(i=0;i<N;i++){
    snprintf(buf1, 10, "%d",zz[i] );
    strcat(buf,buf1);
  }

  puts(buf);
  printf("vector=%d\n",strlen(buf));
  
  sha3_Init256(&c);
  sha3_Update(&c, (char *)buf, strlen(buf));
  hash = sha3_Finalize(&c);
  
  j=0;
  k=0;
  while((b=fread(tmp,1,64,fp))>0){
    //    memset(msg,0,sizeof(msg));
    strncpy( buf, buf, 8192 );
    buf[8193]='\0';
    
    sha3_Init256(&c);
    sha3_Update(&c, (char *)buf, strlen(buf));
    hash = sha3_Finalize(&c);

    //puts(buf);
    //printf("srt=%d\n",strlen(buf));
    //wait();
    #pragma omp parallel for
    for(k=0;k<64;k++)
      tmp[k]^=hash[k];
    memset(buf, '\0', sizeof(buf));
#pragma omp parallel for
    for(i=0;i<64;i++){
      snprintf(buf1, 10, "%d",hash[i] );
      strcat(buf,buf1);
    }
    j++;
    // printf("\nlen=%d\n",strlen(buf));
    //puts(buf);
    fwrite(tmp,1,b,fq);
    //memset(msg,0,sizeof(msg));
    
  }
  //    exit(1);       
  //  fclose(fp);
  fclose(fq);
  printf("len=%d\n",strlen(buf));
}
