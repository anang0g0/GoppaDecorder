#include <stdio.h>
#include <stdlib.h>


#include "8192.h"
#include "global.h"
#include "struct.h"
//#include "oplib.h"
#include "oplib.c"


//extern unsigned short g[K+1];

//言わずもがな
int main (void){
  int i, j, k, l, c,ii=0,n;
  unsigned long a, x, count = 0;
  //  unsigned short cc[K]={0};
  unsigned short m[K], dd[K * N] = { 0 };
  time_t timer;
  FILE *fp, *fq;
  unsigned short jj[T * 2] = { 0 };
  unsigned short zz[N] = { 0 },ufu[K+1]={0};
  int y, flg, o1 = 0;
  OP f = { 0 }, h = { 0 }, r = { 0 }, w = { 0 }, aa[2*T] = { 0 }, tt = { 0 }, ff = { 0 };
  EX hh = { 0 },ee={0},bb={0};
  vec v;
  unsigned short d = 0;
  time_t t;
  unsigned short gg[K + 1] = { 0 };
  oterm rr = { 0 };
  OP r1 = { 0 }, r2 = { 0 }, t1 = { 0 }, t2 = { 0 }, a1 = { 0 }, b1 = { 0 }, a2 = { 0 }, b2 = { 0 };
  OP g1 = { 0 },tmp={0},ll={0};
  


  srand (clock () + time (&t));
  printf ("@");
  //getkey();
  //  exit(1);
  
label:
  
  for (i = 0; i < K + 1; i++)
    g[i] = 0;
  ginit ();
  /*  
  fp=fopen("sk.key","rb");
  fread(g,2,K+1,fp);
  fclose(fp);
  for(i=0;i<K+1;i++)
    gg[K-i]=g[i];
  for(i=0;i<K+1;i++)
    g[i]=gg[i];
  */
  
  w = setpol (g, K + 1);
  oprintpol (w);
  //exit(1);
  
#pragma omp parallel for
  for (i = 0; i < N; i++)
    {
      a = trace (w, i);
      if (a == 0)
	{
	  printf ("trace 0 @ %d\n", i);
	  goto label;
	  //  exit(1);
	}
    }
  printf ("@");
  //keygen(g);
  //key2 (g);
  det(g);

  /*
  fq = fopen ("H.key", "rb");

  fread (dd, 2, K * N, fq);

#pragma omp parallel for
  for (i = 0; i < N; i++)
    {
      for (j = 0; j < K; j++)
	mat[j][i] = dd[K * i + j];
    }
  fclose (fq);
  */
  
  for (j = 0; j < N; j++)
    {
      flg = 0;
      for (i = 0; i < K; i++)
	{
	  //printf("%d,",mat[i][j]);
	  if (mat[i][j] > 0)
	    flg = 1;
	  //      printf("\n");
	}
      if (flg == 0)
	printf ("0 is %d\n", j);
    }

  // exit(1);

  /*  
     //-------------２乗するとき外す
     w=setpol(g,K/2+1);
     printpol(o2v(w));
     printf("\n");
     //   exit(1);
     w=omul(w,w);
     printpol(o2v(w));
     printf("\n");
     //exit(1);

     v=o2v(w);
     for(i=0;i<K+1;i++){
     printf("%d,",v.x[K-i]);
     gg[K-i]=v.x[i];
     }
     printf("\n");
     //w=setpol(gg,K+1);
     //printpol(o2v(w));
     //printf("\n");
     //   exit(1);
     //--------------
   */

  //  w=keyfinder();


  printf ("すげ、オレもうイキそ・・・\n");

  uu=0;
  #pragma omp parallel for
  for(i=0;i<N;i++){
  a=trace(w,i);
  if(a==0){
    printf("trace 0\n");
       exit(1);
  }
  }
  //printpol(o2v(w));
  //    exit(1);

  /*
  fp=fopen(argv[1],"rb");
  fq=fopen(argv[2],"wb");
  
  
  while((c=fread(zz,1,T,fp))>0){
  
  for(i=0;i<M;i++){
    d=trace(w,(unsigned short)i);
    printf("%d,",d);
    if(d==0){
      printf("%i bad trace 0\n",i);
      exit(1);
    }
  }
  printf("\n");
  //exit(1);
  */

 

  for(j=0;j<N;j++){
    flg=0;
    for(i=0;i<K;i++){
      //printf("%d,",mat[i][j]);
      if(mat[i][j]>0)
	flg=1;
      //      printf("\n");
    }
    if(flg==0)
      printf("0 is %d\n",j);
  }


    k=0;  
    while(1){
      o1=0;

    count=0;    

    //  exit(1);
    
  for(i=0;i<N;i++)
    zz[i]=0;
  
  j=0;
  while(j<T){
    l=xor128()%N;
    //printf("l=%d\n",l);
    if(0==zz[l] && l>0){
      zz[l]=l;
      j++;
    }
  }
    
  
  for(i=0;i<K;i++){
    syn[i]=0;
    //#pragma omp parallel for
    for(j=0;j<N;j++){
      //   printf("%u,",zz[jj[j]]);
      syn[i]^=gf[mlt(fg[zz[j]],fg[mat[i][j]])];
    }
       printf("syn%d,",syn[i]);
  }
  printf("\n");
  //    exit(1);  
  for(i=0;i<K;i++)
    printf("mat[%d][1]=%d\n",i,mat[i][1]);
  printf("\n");
  //    exit(1);
  
  f=setpol(syn,K);
  printpol(o2v(f));
  printf(" syn=============\n");
  //   exit(1);
  
  r=decode(w,f);
  
  
  for(i=0;i<T;i++){
    if(i==0){
     printf("e=%d %d %s\n",r.t[i].a,r.t[i].n,"う");
    }else if(r.t[i].a==r.t[i].n){
      printf("e=%d %d %s\n",r.t[i].a,r.t[i].n,"お");
    }else if(r.t[i].a!=r.t[i].n){
	printpol(o2v(w));
	printf(" goppa polynomial==============\n");
	for(l=0;l<N;l++){
	  // printf("%d,",zz[l]);
	  if(zz[l]>0 && zz[l]==l)
	    count++;
	}
	if(count<T){
	  printf("error pattarn too few\n");
	  exit(1);
	}

}
    if(r.t[i].a==0){
      printf("------------------\n");
       printf("err=%d i=%d\n",o1,i);
      printpol(o2v(w));
      printf(" w==============\n");
      printpol(o2v(f));
      printf(" w==============\n");
      for(l=0;l<N;l++)
	printf("%d,",zz[l]);
      printf("\n");
       exit(1);
    }
  }
    for(i=0;i<N;i++){
    if(zz[i]>0)
      o1++;
  }
  printf("err=%dっ！！\n",o1);
  
 
  //  exit(1);

      printf("パターソンアルゴリズムを実行します。何か数字を入れてください。\n");
       scanf("%d",&n);
      //system("PAUSE");
      
      //fp=fopen("sk.key","wb");
      
      flg=0;
      //  while(1){

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



      printf ("zz=");
      for (i = 0; i < N; i++)
	printf ("%d,", zz[i]);
      printf ("\n");
      //    exit(1);
      //  
      for (i = 0; i < K; i++)
	{
	  syn[i] = 0;
	  //#pragma omp parallel for
	  for (j = 0; j < N; j++)
	    {
	      //   printf("%u,",zz[jj[j]]);
	      syn[i] ^= gf[mlt (fg[zz[j]], fg[mat[i][j]])];
	    }
	  printf ("syn%d,", syn[i]);
	}
      printf ("\n");
      //    exit(1);  
      for (i = 0; i < K; i++)
	printf ("mat[%d][1]=%d\n", i, mat[i][1]);
      printf ("\n");
      //    exit(1);


      f = setpol (syn, K);
      printpol (o2v (f));
      printf (" syn=============\n");
      //exit(1);
      
      hh=xgcd(w,f);
      if(deg(o2v(hh.d))>0){
	printf(" s,wは互いに素じゃありません。\n");
	scanf("%d",&n);
	goto label;
      }
	

      tt.t[0].n = 1;
      tt.t[0].a = 1;

      
      ff = inv (f, w);
      tmp=omod(omul(ff,f),w);
      if(deg(o2v(tmp))>0){
	printpol(o2v(tmp));
	printf(" inv(h+x)============\n");
	printpol(o2v(w));
	printf(" w============\n");
	printf("この多項式では逆元計算ができません。");
	printf("count=%d\n",k);
	//scanf("%d",&n);
	goto label;
      } 
      r2 = oadd (ff, tt);
      printpol (o2v (r2));
      printf (" h+x==============\n");
      //  exit(1);
      g1 = osqrt (r2, w);
      printpol (o2v (g1));
      printf (" g1!=========\n");
      r1 = omod(omul(g1,g1),w);
      printpol(o2v(r1));
      printf(" g1^2 mod w===========\n");
      printpol(o2v(r2));
      printf(" r2===========same?\n");
      //scanf("%d",&n);
      if(deg(o2v(r1))!=deg(o2v(r2)) && deg(o2v(g1))>0){
	printpol(o2v(w));
	printf(" w===========\n");
	printpol(o2v(r2));
	printf(" r2===========\n");
	printf("平方根の計算に失敗しました。\n");
	printf("count=%d\n",k);
	//scanf("%d",&n);
	goto label;
	//exit(1);
      }
      if (deg(o2v(g1)) == 0)
	{
	  printpol(o2v(g1));
	  printf(" sqrt(h+x)==============\n");
	  printpol (o2v (w));
	  printf (" badkey=========\n");
	  printf ("平方根が０になりました。\n");
	  printf("count=%d\n",k);
	  //scanf ("%d", &n);
	  //exit(1);
	  goto label;
	}

      hh = xgcd (w, g1);

      ff = omod (omul (hh.v, g1), w);
      printpol (o2v (ff));
      printf (" beta!=========\n");
      if (deg (o2v (ff)) != K / 2)
	{
	  printf("count=%d\n",k);
	  exit(1);
	  //goto label;
	}

      n=0;
      hh=xgcd(w,f);
      if(deg(o2v(hh.d))>0){
	printf("wとfが互いに素ではありません。");
	printf("count=%d\n",k);
	//scanf("%d",&n);
	goto label;
      }	
      if(deg(o2v(hh.d))==0)
	pattarson (w, f);

      scanf("%d",&n);

      //break;
    }


  return 0;
    }

