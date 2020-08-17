/*
//ファイルの暗号化(too slow)
void fileenc(int argc,char **argv[]){
  int i,j,k,b,l;
  FILE *fp,*fq;
  unsigned char msg[64]={0};
  unsigned short zz[N]={0};
  uint8_t *hash;
  sha3_context c;
  int image_size=512;
  vec v;
  OP f={0};


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

  fp=fopen(argv[1],"rb");
  fq=fopen(argv[2],"wb");
  printf("%s\n",argv[1]);
  printf("%s\n",argv[2]);
  //exit(1);

  f=synd(zz);
  // v=o2v(f);
    //
  //for(i=0;i<K;i++)
  // sy[i]=v.x[i];

  fwrite(sy,2,K,fq);
  //fclose(fq);
  printf("in file\n");
  // return 0;


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


  k=0;
  while((b=fread(msg,1,64,fp))>0){
    //    memset(msg,0,sizeof(msg));
    strncpy( buf, buf, 8192 );
    buf[8193]='\0';

    sha3_Init256(&c);
    sha3_Update(&c, (char *)buf, strlen(buf));
    hash = sha3_Finalize(&c);

    //puts(buf);
    //printf("srt=%d\n",strlen(buf));
    //wait();


    j=0;
    for(i=0; i<image_size/8; i++) {
      //printf("%d", hash[i]);
      //char s[3];
      //byte_to_hex(hash[i],s);

      msg[i]^=hash[i];

      //hash[i]^=k;
      k++;
      if(k==255)
	k=0;
    }

    memset(buf, '\0', sizeof(buf));
    for(i=0;i<64;i++){
      snprintf(buf1, 10, "%d",hash[i] );
      strcat(buf,buf1);
    }
    // printf("\nlen=%d\n",strlen(buf));
    //puts(buf);
    fwrite(msg,1,b,fq);
    memset(msg,0,sizeof(msg));

  }
  //    exit(1);
  fclose(fp);
  fclose(fq);
  printf("len=%d\n",strlen(buf));


//  return 0;
}


//ファイルの復号(don't start,too late)
void filedec(OP w,int argc,char **argv[]){
  int i,j,b,k;
  FILE *fp,*fq;
  unsigned char msg[64];
    unsigned short s[K]={0},tmp[K]={0},err[N]={0};
  OP f;
  vec v;
  uint8_t *hash;
  sha3_context c;
  int image_size=512;


  fp=fopen(argv[2],"rb");
  fq=fopen(argv[3],"wb");

  fread(tmp,2,K,fp);
  for(i=0;i<K;i++){
    s[i]=tmp[K-i-1];
    printf("%d,",s[i]);
  }
  printf("\n");
  f=setpol(tmp,K);
  v=pattarson(w,f);
  //exit(1);

  j=0;
  if(v.x[1]>0 && v.x[0]==0){
    err[0]=1;
    j++;
  }
  printf("j=%d\n",j);
  printf("after j\n");
  for(i=j;i<2*T;i++){
    if(v.x[i]>0){
      err[v.x[i]]=1;
    }
  }

  unsigned char buf[10000],buf1[10]={0};

  for(i=0;i<N;i++){
    snprintf(buf1, 10, "%d",err[i] );
    strcat(buf,buf1);
  }

  //puts(buf);
  printf("vector=%d\n",strlen(buf));

  sha3_Init256(&c);
  sha3_Update(&c, (char *)buf, strlen(buf));
  hash = sha3_Finalize(&c);


  k=0;
  while((b=fread(msg,1,64,fp))>0){
    //    memset(msg,0,sizeof(msg));

    strncpy( buf, buf, 8192 );
    buf[8193]='\0';

    sha3_Init256(&c);
    sha3_Update(&c, (char *)buf, strlen(buf));
    hash = sha3_Finalize(&c);

    //puts(buf);
    //printf("srt=%d\n",strlen(buf));
    //wait();


    j=0;
    //#pragma omp parallel for
    for(i=0; i<image_size/8; i++) {
      // printf("%d", hash[i]);
      //char s[3];
      //byte_to_hex(hash[i],s);

      msg[i]^=hash[i];

      //hash[i]^=k;
      k++;
      if(k==255)
	k=0;
    }
    printf("\n");
    memset(buf, '\0', sizeof(buf));
    for(i=0;i<64;i++){
      snprintf(buf1, 10, "%d",hash[i] );
      strcat(buf,buf1);
    }
    printf("\nlen=%d\n",strlen(buf));
    puts(buf);
    fwrite(msg,1,b,fq);
    memset(msg,0,sizeof(msg));

  }
  //    exit(1);
  fclose(fp);
  fclose(fq);
  printf("len=%d\n",strlen(buf));

}
*/
