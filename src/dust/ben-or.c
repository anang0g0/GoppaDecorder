// date:20200212 benor original version 
//auther    : the queer who thinking about cryptographic future
//code name : OVP - One Variable Polynomial library with OpenMP friendly
//status    : now in debugging (ver 0.8)
// 既約多項式生成モジュールだが、おそすぎて使い物にならない。
//なので本ソフトではランダムにGF(2^13)を係数に持つ多項式を取ってくるものとする。
//codeの分割コンパイルはまだよ、焦っちゃだめｗ


#include "chash.c"
#include "lu.c"
#include <stdint.h>


#define K 64*2
#define DEG 8192
#define T K/2
#define E 4
#define D 2*K

unsigned short c[2*K+1]={0};


typedef struct {
  unsigned long long int n;
  unsigned short a;
} oterm;

typedef struct{
  oterm t[256];
} OP;

typedef struct {
  unsigned int x[DEG];
} vec;

typedef union {
  unsigned long long int u[4];
  unsigned short s[16];
} SU;

OP ss={0};
OP hh={0};
OP qq={0};
OP p0={0};




unsigned short b2B(unsigned short b[E]){
  int i,j,k;
  unsigned short a=0;

  for(i=0;i<E;i++)
    a^=(b[i]<<i);

  return a;
}


unsigned short oinv(unsigned short a){
  int i;

  for(i=0;i<M;i++){
    if(gf[mlt(fg[a],i)]==1)
      return (unsigned short)i;
  }

}


unsigned short equ(unsigned short a,unsigned short b){
  int i;

  for(i=0;i<M;i++){
    if(gf[mlt(fg[a],fg[i])]==b)
      break;
  }
  return i;
}

int distance(OP f){
int i,j,k;

for(i=0;i<256;i++){
if(f.t[i].a>0)
  j=i;
}

return j;
}

int terms(OP f){
int i,count=0;

for(i=0;i<256;i++)
  if(f.t[i].a>0)
    count++;

return count;
}


int odeg(OP f){
int i,j=0,k;

for(i=0;i<terms(f)+1;i++){
  if(j<f.t[i].n && f.t[i].a>0)
    j=f.t[i].n;
}

return j;
}


int deg(vec a){
  int i,n=0;


#pragma omp parallel for   
  for(i=0;i<DEG;i++){
    if(a.x[i]>0)
      n=i;
  }
  
  if(n>0)
    return n;


}


vec o2v(OP f){
  vec a={0};
  int i,count=0;


  for(i=0;i<256;i++){
    if(f.t[i].a>0){
    //printf("%u,",f.t[i].n);
     a.x[f.t[i].n]=f.t[i].a;
    }
  }

  return a;
}


OP v2o(vec a){
  int i,count=0;
  OP f={0};
printf("deg=%d\n",deg(a));
//exit(1);

#pragma omp parallel for   
  for(i=0;i<DEG;i++){
    if(a.x[i]>0){
      f.t[count].n=i;
      f.t[count++].a=a.x[i];
    }
  }

  return f;
}


vec i2v(unsigned int n){
  vec v;
  int i;
  
  for(i=0;i<32;i++){
  v.x[i]=n%2;
  n=(n>>1);
  }
	
  return v;
}


unsigned int v2i(vec v){
  unsigned int d=0,i;

  for(i=0;i<32;i++){
    d=(d<<1);
    d^=v.x[i];
  }

  return d;
}




OP Setvec(int n){
int i,a,b=0;
OP v={0};


 for(i=0;i<n;i++){
  v.t[b].a=c[i];
  v.t[b++].n=i;
 }

 
  return v;
}


void oprintpol(OP f){
int i,j,k,n;

n=distance(f);
printf("n=%d\n",n);
printf("terms=%d\n",terms(f));
printf("deg=%d\n",odeg(f));
 
 if(n==0){
   printf("0");
   return;
 }
 
for(i=0;i<n+1;i++){
  if(f.t[i].a>0)
    printf("%ux^%u+",f.t[i].a,f.t[i].n);
}
//printf("\n");
//exit(1);
return;
}

void printpol(vec a){
  int i,n;

  n=deg(a);
  if(n<0){
    printf("baka\n");
    exit(1);
    }
  

  for(i=n;i>-1;i--){
    if(a.x[i]>0){
      printf("%u",a.x[i]);
      if(i>0)
	printf("x^%d",i);
    if(i>0)
      printf("+");
    }
  }
  //  printf("\n");

  return;
}

OP sort(OP f){
  oterm o={0};
  int i,j,k;

  
  k=terms(f);
  for (i=0; i<k+1; ++i) {
    for (j=i+1; j<k+1; ++j) {
      if (f.t[i].n > f.t[j].n) {
        o =  f.t[i];
        f.t[i] = f.t[j];
        f.t[j] = o;
      }
    }
  }

  return f;
}


OP oadd(OP f,OP g){
//  vec a={0},b={0},c={0};
  uint64_t i,k,j,n1=0,n2=0,tmp,m1,m2,flg=0,count=0;
  OP h={0},a={0},b={0};
  char *arr1; //[4294967296]={0};
  char *arr2; //[4294967296]={0};
  /*
  if ((arr1 = (char *)malloc(0 * sizeof(char))) == NULL) {
    fprintf(stderr, "\n Memory can not be allocated (%lu byte).\n", 4294967296/2 * sizeof(char));
       exit(1);
}
  */
  //exit(1);
  arr1=(char*)calloc(0xffffffff,sizeof(char));
  arr2=(char*)calloc(0xffffffff,sizeof(char));
  
n1=terms(f);
 printf("n1=%d\n",n1);
n2=terms(g);
 printf("n2=%d\n",n2);
 // exit(1);
 //
 memset(arr1,0,0xffffffff);
 memset(arr2,0,0xffffffff);
 /* 
#pragma omp parallel for
 for(i=0;i<0xfffffffff;i++){
   arr1[i]=0;
   arr2[i]=0;
 }
 */
 
 oprintpol(f);
 printf(" fff==============\n");
 oprintpol(g); 
 printf(" ggg==============\n");
 for(i=0;i<n1;i++){
   printf("fn=%d %d\n",f.t[i].n,i);
   arr1[f.t[i].n]=f.t[i].a;
 }
 for(i=0;i<n2;i++){
   arr2[g.t[i].n]=g.t[i].a;
   printf("%d %d\n",g.t[i].n,i);
 }
 // exit(1);
 if(odeg(f)>odeg(g)){
   m1=odeg(f);
 }else{
  m1=odeg(g);
 }
#pragma omp parallel for   
 for(i=0;i<0xffffffff;i++){
     arr1[i]^=arr2[i];
   //   if(arr1[i]>0 || arr2[i]>0){
     // printf("f=%d %d\n",arr1[i],i);
     //   printf("g=%d %d\n",arr2[i],i);
     
 //   exit(1);
   if(arr1[i]>0){
     printf("arr=%d %d\n",arr1[i],i);
     h.t[count].a=arr1[i];
     h.t[count++].n=i;
    }
 }
 if(terms(h)>0)
   oprintpol(h);
   printf(" hhh===============\n");
   free(arr1);
   free(arr2);
   
    printf("in oadd pol=========\n");
    //  exit(1);

  return h;
}


oterm LT(OP f){
  int i,k,j;
  oterm t={0},s={0};

  k=terms(f);
  s=f.t[0];
  for(i=0;i<k+1;i++){
    //printf("a=%d %d\n",f.t[i].a,f.t[i].n);
    if(f.t[i].a>0){
      printf("in LT=%d %d\n",s.a,s.n);
      for(j=i;j<k+1;j++){
	if(s.n<f.t[j].n){
	  s.n=f.t[j].n;
	  s.a=f.t[j].a;
	}
	/*
	else{
	  t=s;
	}
	*/
      }
    }
  }
  //  exit(1);
  return s;
}


OP add(OP f,OP g){
//  vec a={0},b={0},c={0};
  uint64_t i,k,j,n1=0,n2=0,tmp,m1=0,m2,flg=0,count=0;
  OP h={0},a={0},b={0};
  oterm o1={0},o2={0},oo={0};

  
n1=terms(f);
 printf("n1=%d\n",n1);
n2=terms(g);
 printf("n2=%d\n",n2);
 if(n1>n2){

 }

 oprintpol(f);
 printf(" fff==============\n");
 oprintpol(g); 
 printf(" ggg==============\n");
 o1=LT(f);
 o2=LT(g);
 printf("LTadd==%d %d\n",o1.n,o2.n);
 m1=n1+n2;
 printf("m1=%d\n",m1);
 // exit(1);
 
 for(i=0;i<n1+1;i++){
   for(j=0;j<n2+1;j++){
     if(f.t[i].n==g.t[j].n && g.t[j].a>0 && f.t[i].a>0){
       o1=LT(f);
       o2=LT(g);
       printf("LT==%d %d\n",o1.n,o2.n);
       printf("f.n==%d %d %d %d\n",f.t[i].n,g.t[j].n,i,j);
       f.t[i].a=0;
       g.t[j].a=0;
     }
   }
 }
 for(i=0;i<n2+1;i++){
   if(g.t[i].a>0){
     h.t[count++]=g.t[i];
     g.t[i].a=0;
   }
 }
 for(i=0;i<n1+1;i++){
   if(f.t[i].a>0){
     h.t[count++]=f.t[i];
     f.t[i].a=0;
   }
   
 }

 h=sort(h);
 /*
 for (i=0; i<count; ++i) {
    for (j=i+1; j<count; ++j) {
      if (h.t[i].n > h.t[j].n) {
        oo =  h.t[i];
        h.t[i] = h.t[j];
        h.t[j] = oo;
      }
    }
  }
 */
 if(odeg(h)>0)
 oprintpol(h);
 printf(" addh==============\n");
 //   exit(1);

 return h;
}


OP oterml(OP f,oterm t){
  int i;
  OP h={0};
  vec test;
  unsigned short n;

    
  for(i=0;i<terms(f)+1;i++){
    h.t[i].n=f.t[i].n+t.n;
    h.t[i].a=gf[mlt(fg[f.t[i].a],fg[t.a])];
  }

  return h;
}


OP omul(OP f,OP g){
  int i,count=0;
  oterm t={0};
  OP h={0},e={0},r={0};


  for(i=0;i<odeg(g)+1;i++){
    t=g.t[i];
    e=oterml(f,t);
    h=oadd(h,e);
  }

  return h;
}


 

oterm LT2(OP f){
  int i,k;
  oterm t={0};

      t.n=f.t[0].n;
      t.a=f.t[0].a;

  return t;
}


oterm LTdiv(OP f,oterm t){
  oterm tt={0},s={0};

  tt=LT(f);
  if(tt.n<t.n){
    s.n=0;
    s.a=0;
  } else if(tt.n==t.n){
    s.n=0;
    s.a=equ(t.a,tt.a);
  }else if(tt.n>t.n){
    s.n=tt.n-t.n;
    s.a=equ(t.a,tt.a);
    //printf("%u\n",s.a);
  }else if(t.n==0 && t.a>0){
    s.a=gf[mlt(fg[tt.a],oinv(t.a))];
    s.n=tt.n;
  }

  return s;    
}


OP omod(OP f,OP g){
  int i=0,j,n,k,m,count=0;
  OP h={0},e={0};
  oterm a,b={0},c={0};
  
  k=odeg(f);
  printf("deg(f)=%d\n",k);
  m=LT(g).n;
  printf("n=%d\n",m);
  //  exit(1);

  
  if(odeg(f)==0){ 
    printf("baka^\n");
    exit(1);
  }
  if(odeg(g)==0){
    printf("baka--\n");
     exit(1);
  }
  if(odeg(f)<odeg(g)){
    return f;
  }

  //  printf("in omod\n");
  //exit(1);
  k=odeg(g);
  b=LT(g);
  
  printf("b=========%dx^%d\n",b.a,b.n);
    oprintpol(g);
    printf(" in omog g==============\n");
    oprintpol(f);
    printf(" in omog f==============\n");
    //  exit(1);
    printf("\nin omod g=============%d\n",odeg(g));
    while((odeg(f)-odeg(g))>=0){
      printf("in!\n");
      //    exit(1);
      
      c=LTdiv(f,b);
      printf("cc========%dx^%d\n",c.a,c.n);
      //   exit(1);
      //ss.t[i]=c;
      //i++;
      oprintpol(g);
      printf("\ng=================\n");
      
      h=oterml(g,c);
      oprintpol(h);
      // printf("\n");
      printf(" modh===================\n");
      //  exit(1);
      oprintpol(f);
      printf("\nmodf===================\n");
      //     exit(1);
      
      f=add(f,h);
      if(odeg(f)>0)
      oprintpol(f);
      printf(" ff1=====================\n");
      //  exit(1);
      if(odeg(f)>m+1){
	printf("baka500\n");
	//break;
      }
      count++;
    
      if(c.n==0)
	break;
    }
    
    return f;
}


OP odiv(OP f,OP g){
  int i=0,j,n,k,m;
  OP h={0},e={0},tt={0},o={0};
  oterm a,b={0},c={0};

  m=odeg(f);
  o=f; 

  if(odeg(f)==0){ 
    printf("baka^\n");
    exit(1);
  }
  if(odeg(g)==0 && g.t[0].a==0){
    printf("baka--\n");
    exit(1);
  }
    printf("in odiv\n");
    //printpol(o2v(g));
    
  //exit(1);
    k=deg(o2v(g));
    b=LT(g);
    printpol(o2v(g));
    printf("in odiv1 g===========%d %d\n",b.a,b.n);
  
    if(deg(o2v(f))<deg(o2v(g))){
  return f;
  //  a=LT(f);
    }
  printf("odiv in b=========%dx^%d\n",b.a,b.n);
printpol(o2v(g));
 printf("\nf===================\n");
 // e=omul(g,g);
 //printpol(o2v(e));
 //printf("\ng^2================\n");

 printf("\nin odiv2 g=============%d\n",deg(o2v(g)));
 i=0;
 while((deg(o2v(f))-deg(o2v(g)))>=0){
    //  printf("in!\n");
    //    exit(1);
    
    c=LTdiv(f,b);
    //    if(c.a>0){
    printf("in odev c========%dx^%d\n",c.a,c.n);
    //    exit(1);
    tt.t[c.n]=c;
    
    //printpol(o2v(g));
    //printf("\ng=================\n");

    h=oterml(g,c);
    //printpol(o2v(h));
    //printf("\n");
    //printf("h===================\n");
    //printpol(o2v(f));
    //printf("\nf===================\n");
    //     exit(1);
    
      f=add(f,h);
    
      //printpol(o2v(f));
      //printf("\nff=====================\n");
      if(deg(o2v(f))>m+1){
	printf("baka500\n");
	break;
      }
      
      if(c.n==0)
	break;
  }
  //exit(1);
  


    return tt;
}




  
OP opow(OP f,int n){
  int i;
  OP g={0};

  g=f;
  //memcpy(g.t,f.t,sizeof(f.t));
  
  for(i=1;i<n;i++)
    g=omul(g,f);

  return g;
}


OP opowmod(OP f,OP mod,int n){
  OP g;
  int i;
  
  g=omod(opow(f,n),mod);
  
  return g;
}


unsigned short trace(OP f,unsigned short x){
  int i;
    unsigned short u=0;

  for(i=0;i<deg(o2v(f))+1;i++){
    u^=gf[mlt(fg[f.t[i].a],mltn(f.t[i].n,fg[x]))];
  }
  
  return u;
}


OP coeff(OP f,unsigned short d){
  int i,j,k;
  //vec a,b;
  
  for(i=0;i<deg(o2v(f))+1;i++)
    f.t[i].a=gf[mlt(fg[f.t[i].a],oinv(d))];


  return f;

}


// invert of polynomial
OP inv(OP a,OP n){
  OP d={0},x={0},s={0},q={0},r={0},t={0},u={0},v={0},w={0},tt={0},gcd={0};
  oterm b={0};
  vec vv={0},xx={0};

  
  if(odeg(a)>odeg(n)){
    printf("baka_i\n");
    exit(1);
  }
  //  v=n;
  printf("n=============\n");
  oprintpol(n);
  printf("\n");
  printf("a=============\n");
  oprintpol(a);
  printf("\n");
  //  exit(1);
  
  d = n;
  x.t[0].a = 0;
  x.t[0].n = 0;
  s.t[0].a = 1;
  s.t[0].n = 0;
  while (LT(a).n!=0){

    r=omod(d ,a);
    q=odiv(d, a);
    
    d = a;
    a = r;
    t=add(x,omul(q,s));
    oprintpol(a);
    printf("\nin roop a==================%d\n",deg(o2v(a)));
    printf("\n");
    if(LT(a).n==5 && a.t[0].n==1){
      //h=omod(h,e);
      oprintpol(a);
      printf("\nin modh=========\n");
      exit(1);
      }
    
    x = s;
    s = t;
  }
  if(a.t[0].a>0){
    d = a;
    a = r;
    oprintpol(a);
    printf("\nin roop a==================%d\n",deg(o2v(a)));
    printf("\n");
    
    x = s;
    s = t;

   oprintpol(d);
   printf("\nout1================\n");
     gcd = d;  // $\gcd(a, n)$
     oprintpol(gcd);
   printf("\n");
   oprintpol(n);
   printf("\n");
   printf("out2===============\n");
   
   printf("before odiv\n");
   w=n;

   b=LT(w);
   oprintpol(w);
   printf("\nw=======%d %d\n",b.a,b.n);
   //w=tt;
   v=oadd(x,n);
   oprintpol(v);
   printf("\n");
    printf("d==============\n");
  }
    oprintpol(w);
   printf("\n");
   printf("ss==============\n");
   //       exit(1);
   u=omod(v, w);
   u=odiv(u, d);
   //u=coeff(u,d.t[0].a);
   oprintpol(u);
   printf("\nu==================\n");
   
   return u;

}






OP gcd(OP a,OP b){
  OP r={0},s={0};
  int count=0;

  
  s=a;
 label:  
  oprintpol(a);
  printf(" a==============\n");
  oprintpol(b);
  printf(" b==============\n");
  //   exit(1);
  /* ユークリッドの互除法 */
  r = omod(a , b);
  if(odeg(r)>0){
  oprintpol(r);
  printf(" rrr==============\n");
  }
  //exit(1);
  //#pragma omp parallel  
  while(odeg(r)>0){
    oprintpol(r);
    printf(" r2==============\n");

    a = b;
    b = r;
     if(odeg(b)>0)
      r = omod(a ,b);
     if(odeg(r)>0)
     oprintpol(r);
    printf(" ttt==============\n");
    //  exit(1);
      //  } 
    
    if(odeg(r)==0 && r.t[0].a==1)
      return r;
    if(odeg(r)==0 && r.t[0].a==0)
      return b;
    
    if(odeg(b)==1)
      break;
    
    count++;
    if(count>0xff){
      printf("baka100\n");
      exit(1);
    }
  }

  
}




uint64_t ipow(unsigned int q,unsigned int u){
  unsigned int i;
  uint64_t m=1;

  
  for(i=0;i<u;i++){
    m*=2;
    printf("%llu,%d\n",m,i);
  }

  printf("in ipow====%llu\n",m);

  return m;
}





OP benor(int ww,int nn){
  OP w={0},ff={0},f={0},tt={0};
  unsigned int flg=0,i,j,jj[64]={0},k,count=0;
  OP v={0};
  oterm o={0};


  //  while(1){
  printf("ww=%d\n",ww);
 label:
#pragma omp parallel for   
    for(i=0;i<256;i++){
      v.t[i].a=0;
      v.t[i].n=0;
    }
    
    for(i=0;i<256;i++)
    printf("a,n=%d %d\n",v.t[i].a,v.t[i].n);
    //    oprintpol(v);
    // exit(1);
    printf("ww,nn=%d %d\n",ww,nn);
    //exit(1);

    v.t[0].a=1;
    v.t[0].n=0;
    v.t[ww+1].a=1;
    v.t[ww+1].n=nn;
    //    v.x[6]=1;
    oprintpol(v);
    //exit(1);
    k=1;
    count=0;
    while(1){
      flg=0;
      j=xor128()%36;
      if(j>0 && j<nn){// && v.t[k-1].n<j){
	for(i=0;i<k+1;i++){
	  if(v.t[i].n==j)
	    flg=1;
	}
	if(flg==0){
	  v.t[k].a=1;
	  v.t[k].n=j;
	  k++;
	  printf("k=%d\n",k);
	}
      }
      count++;
      if(terms(v)==ww+2 || count==100)
	break;
    }
     if(terms(v)<ww+2)
       exit(1);

     v=sort(v);
     /*
     for (i=0; i<ww+2; ++i) {
       for (j=i+1; j<ww+2; ++j) {
	 if (v.t[i].n > v.t[j].n) {
	   o =  v.t[i];
	   v.t[i] = v.t[j];
	   v.t[j] = o;
	 }
       }
     }
     */
     oprintpol(v);
     printf(" sorted======\n");
     // exit(1);
     
    //goto label;

    /*
    do{
      k=1;
      while(k<ww+1){
	j=xor128()%36;
      if(j>0 && j<nn && v.t[k-1].n<j){
	v.t[k].a=1;
        v.t[k].n=j;
	k++;
	printf("k=%d\n",k);
      }
      }
      count++;
      if(count>100){
        k=0;
        for(i=1;i<256;i++){
          v.t[i].a=0;
          v.t[i].n=0;
        }
  
        k=1;
	if(count==100)
	  break;
        //break;
      }
      printf("nozomi=%d\n",ww+2);
      oprintpol(v);
      //if(odeg(v)==0)
      //break;
      printf(" v==============\n");
      
    }while(terms(v)<ww+2);
    */
    if(terms(v)<ww+2)
      exit(1);
  printf("ww,deg,k=%d %d %d\n",ww,odeg(v),k);
  oprintpol(v);  
  printf(" v=============\n");
  printf("odeg=%d\n",odeg(v));
  printf("terms=%d\n",terms(v));

  tt=v;
  //  exit(1);
  for(i=0;i<64;i++)
  jj[i]=0;
  //    tt=irr(1,10);
  #pragma omp parallel for  
  for(i=1;i<nn/2+1;i++){
    f.t[0].a=1;
    f.t[0].n=1;
    f.t[1].a=1;
    if(i>64)
      exit(1);
    f.t[1].n=ipow(2,i);
    oprintpol(f);
    // exit(1);
    if(odeg(tt)>0)
    ff=gcd(tt,f);
    if(odeg(ff)>0)
    oprintpol(ff);
    printf(" benor===========\n");
    if(odeg(ff)>0){
      oprintpol(ff);
      printf(" lcm==============%d\n",i);
      break;
      // goto label;
      // jj[i]=0;
    }
    if(odeg(ff)==0){
      jj[i]++;

      //  oprintpol(ff);
    printf(" ffaa=============\n");
    }
    printf("jj=%d\n",jj[i]);
    oprintpol(v);
    printf(" vv===================\n");
  }
  k=0;
  for(i=0;i<nn/2+1;i++)
    k+=jj[i];
  if(k==nn/2 && terms(tt)==ww+2 && odeg(tt)>0){
    oprintpol(tt);
    printf(" irr?============\n");
    return tt;
    printf("i==%d\n",i);
  }
//  j=0;
  if(terms(v)<ww+2)
  return v;  
  //  }
  //exit(1);
  
}



unsigned char chk(OP f){
  int i,j,flg=0;
  vec x={0};

  x=o2v(f);
  for(i=0;i<DEG;i++){
    if(x.x[i]>0){
      flg=1;
      return 1;
    }
  }
  if(flg==0)
    return 0;
  
}



OP ogcd(OP f,OP g){
  OP h={0},ww={0};
  oterm a,b;
  int i=0;


  //printpol(o2v(f));
  //printpol(o2v(g));
  //  exit(1);
  
  while(i<T && deg(o2v(f))>=deg(o2v(g))){
    //    memset(ss.t,0,DEG*sizeof(ss));
    h=omod(f,g);
    ww=odiv(f,g);
  f=g;
  g=h;
  i++;
   if(deg(o2v(g))<=T-1)
     break;
  }
  // exit(1);

    
  return h;
}




OP setpol(unsigned short *f,int n){
OP g;
vec a;
 int i;

 
 memset(c,0,sizeof(c));
   // for(i=0;i<K+1;i++)
   // c[i]=0;
 // memcpy(c,f,sizeof(c));
   for(i=0;i<n;i++)
   c[i]=f[i];
  g=Setvec(n);
  //g=v2o(a);


return g;
}




int main(int argc,char **argv){
  int i,j,k,l,c;
  unsigned long a,x,count=1;
  //  unsigned short cc[K]={0};
  unsigned short m[K],mm[T]={0},dd[K*D]={0};
  time_t timer;
  FILE *fp,*fq;

  unsigned short g2[7]={1,0,9,0,0,6,4};
  //  unsigned short s[K]={0}; //{4,12,7,8,11,13};
  unsigned short jj[T]={0};
  unsigned short ee[10]={1,2,3,4,5,6,7,8,9,10};
  unsigned short zz[D]={0};
  //  unsigned short zz[T]={10,97,114,105,97,98,108,101,32,80,111,108,121,110,111,109};
  int y,flg,o1=0;
  OP f={0},h={0},r={0},w={0},aa[T]={0},tt={0},ff={0};
  vec v;
  unsigned short d=0;
  time_t t;
  unsigned short gg[K+1]={0};
  oterm rr={0};
  uint64_t u=0;


  srand(clock()+time(&t));

  
  //u=ipow(2,64);
  //printf("%llu\n",u);
  
  ff.t[0].a=1;
  ff.t[0].n=0;
  ff.t[1].a=1;
  ff.t[1].n=1;
  ff.t[2].a=1;
  ff.t[2].n=16;
  f.t[0].a=1;
  f.t[0].n=1;
  f.t[1].a=1;
  f.t[1].n=256;
  h=gcd(f,ff);
  if(odeg(h)>0)
    oprintpol(h);
  printf("\n");
  if(odeg(h)==0 && odeg(omod(f,ff))==0){
    oprintpol(ff);
    printf(" gcd=======\n");
    printf("terms=%d\n",terms(ff));
    printf("LT(h)=%d\n",LT(ff).n);
    // exit(1);
  }
  
  /*
  f.t[3].a=1;
  f.t[3].n=4;
  f.t[4].a=1;
  f.t[4].n=8;
  f.t[5].a=1;
  f.t[5].n=10;
  */
  /*
  f.t[0].a=1;
  f.t[0].n=1;
  f.t[1].a=1;
  f.t[1].n=32;
  
    tt=add(ff,f);
   oprintpol(tt);
  printf(" tt============\n");
  */
  //  exit(1);
  //rr=LT(tt);
  //printf("LT=%d %d\n",rr.a,rr.n);
  //    exit(1);
  //  h=omod(f,ff);
  //oprintpol(h);
  printf(" h================\n");
  //  exit(1);
  
  //  h=gcd(f,ff);
  //oprintpol(h);
  //printf("gcd=========\n");
  //     exit(1);
   

  while(odeg(ff)<40){
      ff=benor(7,40);
  }
    oprintpol(ff);
    printf(" irr?=============\n");
    exit(1);

  return 0;
}
