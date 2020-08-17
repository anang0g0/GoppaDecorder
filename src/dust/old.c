 
//date      :  20160310,20191218,20191220,20191221,20191223,20191224,20191225,20191229
//auther    : the queer who thinking about cryptographic future
//code name : OVP - One Variable Polynomial library with OpenMP friendly
//status    : now in debugging (ver 0.8)
// gcdの停止条件を修正した。vxの停止条件を修正した。
//date      :  20160310,20191218,20191220,20191221,20191223,20191224,20191225,20191229,20191230
//auther    : the queer who thinking about cryptographic future
//code name : OVP - One Variable Polynomial library with OpenMP friendly
//status    : now in debugging (ver 0.8)
// 0ベクトルが出ないように生成多項式のトレースチェックを入れた。
   
//date      :  20160310
//auther    : the queer who thinking about cryptographic future
//code name : OVP - One Variable Polynomial library with OpenMP friendly
//status    : now in debugging (ver 0.1)

#include "chash.c"
//#include "lu.c"
//#include "global.h"
//#include "8192.h"

#define DEG 256
#define K 64
#define T K/2
#define E 8
#define D 256

unsigned char tmp[E*K][M]={0};
unsigned char pub[E*K][M]={0};
unsigned char BH[E*K][M]={0};
unsigned short c[K+1]={0};
unsigned short mat[K][M]={0};
unsigned short m2[K][M]={0};
/*
unsigned short g[K+1]={1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		       0,0,0,0,0,0,0,0,0,0,
		       		       0,0,0,0,0,0,0,0,0,0,
		       		       0,0,0,0,0,0,0,0,0,0,
		       		       0,0,0,0,0,0,0,0,0,0,
		       0,1};
*/
  //  unsigned short g[K+1]={1,1,0,1,1,0,0,1,1,0,1};
unsigned short g[K+1]={1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1};

//,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
//unsigned short g[K+1]={1,0,0,0,1,0,1};
unsigned short syn[K]={0};
unsigned char A[M][M]={0};
//={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}; //={1,5,0,1,7,3,15}; //={1,2,9,4,0,6,4}; // //
unsigned short P[D]={0};
unsigned short inv_P[D]={0};
unsigned short uu;


typedef struct {
  unsigned short n;
  unsigned short a;
} oterm;

typedef struct{
  oterm t[DEG];
} OP;

typedef struct {
  unsigned int x[DEG];
} vec;

OP ss={0};
OP hh={0};
OP qq={0};
OP p0={0};


void random_permutation(unsigned short* a){
	int i,j,x;
	for(i = 0; i < D; i++){
		a[i] = i;
	}
	for(i = 0; i < D - 2; i++){
		j = (rand() % (D-1-i)) + i + 1;

		x = a[j];
		a[j] = a[i];
		a[i] = x;
	}
	if(a[D-1] == D-1){
		a[D-1] = a[D-2];
		a[D-2] = D - 1;
	}


}


void P2Mat(unsigned short P[M]){
int i,j;
	
  for(i=0;i<M;i++)
      A[i][P[i]]=1;
}


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


int deg(vec a){
  int i,n=0;

  for(i=0;i<DEG;i++){
    if(a.x[i]>0)
      n=i;
  }
  
  if(n>0){
    return n;
  }else{
    return 0;
  }

}


vec o2v(OP f){
  vec a={0};
  int i,count=0;


  for(i=0;i<DEG;i++){
    if(f.t[i].a>0)
      a.x[f.t[i].n]=f.t[i].a;
  }

  return a;
}


OP v2o(vec a){
  int i,count=0;
  OP f={0};

  for(i=0;i<DEG;i++){
    if(a.x[i]>0){
      f.t[i].n=i;
      f.t[i].a=a.x[i];
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


OP init_op(OP f){
  int i;

  for(i=0;i<deg(o2v(f))+1;i++){
    f.t[i].a=0;
    f.t[i].n=0;
}
    
  return f;
}


vec init_vec(vec a){
int i;

for(i=0;i<deg(a)+1;i++)
  a.x[i]=0;

return a;
}


vec Setvec(int n){
int i,a,b;
vec v={0};


 printf("@\n");
 for(i=0;i<n;i++)
   printf("%d,",c[i]);
 printf("\n");

 for(i=0;i<n;i++){
  v.x[n-1-i]=c[i];
  printf("%d,",c[n-1-i]);
 }
 printf("\n");
 
  return v;
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
  printf("\n");

  return;
}


OP oadd(OP f,OP g){
  vec a={0},b={0},c={0};
  int i,k;
  OP h={0};

  a=o2v(f);
  b=o2v(g);
  if(deg(a)>=deg(b)){
    k=deg(a)+1;
  }else{

    k=deg(b)+1;

}
  for(i=0;i<k;i++)
    c.x[i]=a.x[i]^b.x[i];
  h=v2o(c);

  return h;
}


OP oterml(OP f,oterm t){
  int i;
  OP h={0};
  vec test;
  unsigned short n;

  
  for(i=0;i<deg(o2v(f))+1;i++){

    h.t[i].n=f.t[i].n+t.n;
    h.t[i].a=gf[mlt(fg[f.t[i].a],fg[t.a])];

  }

  return h;
}


OP omul(OP f,OP g){
  int i,count=0;
  oterm t;
  OP h={0},e={0},r={0};


  for(i=0;i<deg(o2v(g))+1;i++){
    t=g.t[i];
    e=oterml(f,t);
    h=oadd(h,e);
  }

  return h;
}


oterm LT(OP f){
  int i;
  oterm t;

  for(i=0;i<deg(o2v(f))+1;i++){
    if(f.t[i].a>0){
      t.n=f.t[i].n;
      t.a=f.t[i].a;
    }
  }

  return t;
}


oterm LTdiv(OP f,oterm t){
  oterm tt,s;

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
    printf("%u\n",s.a);
}

  return s;    
}


OP omod(OP f,OP g){
  int i=0,j,n;
  OP h={0},e={0};
  oterm a,b={0},c;

 
  //printpol(o2v(f));
  printf("omod-g=");
//  printpol(o2v(g));

  if(deg(o2v(f))==0 || deg(o2v(g))==0){
    printf("baka^\n");
    exit(1);
  }
  printf("in omod\n");
  //exit(1);  

  //  a=LT(f);
  b=LT(g);
  //printpol(o2v(g));
  while(deg(o2v(f))>=deg(o2v(g))){
    printf("n=======%u\n",deg(o2v(f)));
    printf("in omod before LTdiv\n");
    //printpol(o2v(f));
    printf("LT(g)=%dx^%d\n",b.a,b.n);

    c=LTdiv(f,b);
    printf("%dx^%d\n",c.a,c.n);
    //    exit(1);
    ss.t[i]=c;
    i++;
    h=oterml(g,c);
    printf("in omod after oterml\n");
    //printpol(o2v(h));
    //printpol(o2v(f));
    /*
    if(deg(o2v(h))==1){
      printpol(o2v(h));
      //   exit(1);
      return h;
    }
    */
    //printpol(o2v(ss));
//exit(1);
//    if(deg(o2v(f))>deg(o2v(h)))
//    if(deg(o2v(f))>deg(o2v(h)))
      f=oadd(f,h);
         //f=e;
    //printpol(o2v(f));
    //   exit(1);
    //  if(deg(o2v(f))>T)
    //break;

      }
  //exit(1);

  return f;
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

  /*
  if(deg(o2v(f))==84)
    printpol(o2v(f));
  exit(1);
  */
  for(i=0;i<deg(o2v(f))+1;i++){
    u^=gf[mlt(fg[f.t[i].a],mltn(f.t[i].n,fg[x]))];
  }
  
  //  if(u==0){
  if(f.t[0].a==0 && u==0){
    printf("x=%d\n",x);
    printf("baka14\n");
    printf("0x^0=%d\n",f.t[0].a);
    printpol(o2v(f));
    //  exit(1);
  }
  
  
  return u;
}


// invert of polynomial
OP inv(OP a,OP I){
  OP d,x={0},s={0},q={0},r={0},t={0};
  int i;

  d=I;
  //memcpy(d.t,I.t,sizeof(d.t));
 
  //  d = I;
  //  x = {0};
  s.t[0].a = 1;
  while (deg(o2v(r)) > 0){
    memset(ss.t,0,DEG);
    r=omod(d , a);
    //printpol(o2v(ss));
    //    exit(1);
    q=t;
    //memcpy(q.t,ss.t,sizeof(q.t));

    // r = d % a;
    d=a;
    //memcpy(d.t , a.t,sizeof(d.t));
    a=r;
    //memcpy(a.t , r.t,sizeof(a.t));
     //a = r;
    t = oadd(x,omul(q , s));
    x=s;
    //memcpy(x.t,s.t,sizeof(x.t));
    //    x = s;
    s=t;
    //memcpy(s.t,t.t,sizeof(s.t));
    //    s = t;
  }
  //  gcd = d;  // $\gcd(a, n)$
  memset(ss.t,0,DEG);
  omod(I,d);
  
    memset(ss.t,0,DEG);
 return omod(oadd(x , I) , ss);
}


OP ToHorner(OP f){
  OP h;
  int i;
  vec v;

  v=o2v(f);


  return h;
}


OP vx(OP f,OP g){
  OP h={0};
  OP v[K]={0},vv={0};
  oterm a,b;
  int i,j;

  v[0].t[0].a=0;
  v[0].t[1].n=0;
  v[1].t[0].a=1;
  v[1].t[1].n=0;

  a=LT(f);
  b=LT(g);
  printf("in vx\n");
  //  exit(1);
  i=2;
       for(i=2;i<T+2;i++){
  //  while(deg(o2v(v[i]))<T){
    printf("in vx befoe omod\n");
    //printpol(o2v(f));
    //printpol(o2v(g));
    //        exit(1);
    memset(ss.t,0,DEG);
    if(deg(o2v(f))>=deg(o2v(g))){
  h=omod(f,g);
    }/* else {
      h=omod(g,f);
      printf("baka17\n");
      //  exit(1);
      }*/
  /*
  if(deg(o2v(h))==0){
    printf("baka3!\n");
    exit(1);
  }
  */
  printf("ss=");
  //printpol(o2v(ss));
  printf("h=");
  //printpol(o2v(h));
  //  exit(1);
  v[i]=oadd(v[i-2],omul(ss,v[i-1]));
  printf("-------");
  //printpol(o2v(v[i]));

  //  exit(1);
  memset(f.t,0,sizeof(f.t));
  f=g;
  //memcpy(f.t,g.t,sizeof(g.t));
  memset(g.t,0,sizeof(g.t));
  g=h;
  //memcpy(g.t,h.t,sizeof(h.t));
  //  exit(1);
  
  if(deg(o2v(v[i]))<=T){
    vv=v[i];
    //    hh=h;
    //    break;
  } else {
    
    printf("-------");
    break;
    //    vv=v[i];  
	//  exit(1);
  }
  //  i++;
   }

  //printpol(o2v(v[i]));
 
  //  exit(1);
  //memcpy(vv.t,v[i].t,sizeof(v[i].t));
  //      exit(1);
  printf("%d\n",deg(o2v(vv)));
  //    exit(1);
  
  return vv;
}


OP uv(OP f,OP g){
  OP h={0};
  OP v[K]={0},vv={0};
  oterm a,b;
  int i,j;

  v[0].t[0].a=0;
  v[0].t[1].n=0;
  v[1].t[0].a=1;
  v[1].t[1].n=0;

  a=LT(f);
  b=LT(g);
  printf("in vx\n");
  //  exit(1);
  i=2;
       for(i=2;i<T+2;i++){
  //  while(deg(o2v(v[i]))<T){
    printf("in vx befoe omod\n");
    //printpol(o2v(f));
    //printpol(o2v(g));
    //        exit(1);
    memset(qq.t,0,DEG);
      while(deg(o2v(f))>=deg(o2v(g))){
      printf("++++++++\n");
  h=omod(f,g);
  //exit(1);
  printf("^^^^^^^^^^^^^^^^^\n");
  // exit(1);
  printpol(o2v(h));
  //exit(1);
  if(deg(o2v(h))<84)
    break;
      }
       }
  /*
  if(deg(o2v(h))==0){
    printf("baka3!\n");
    exit(1);
  }
  */
  printf("ss=");
  //printpol(o2v(ss));
  printf("h=");
  //printpol(o2v(h));
  //  exit(1);
  v[i]=oadd(v[i-2],omul(qq,v[i-1]));
  printf("-------");
  //printpol(o2v(v[i]));

  //  exit(1);
  memset(f.t,0,sizeof(f.t));
  f=g;
  //memcpy(f.t,g.t,sizeof(g.t));
  memset(g.t,0,sizeof(g.t));
  g=h;
  //memcpy(g.t,h.t,sizeof(h.t));
  //  exit(1);
  
  if(deg(o2v(v[i]))<=T){
    vv=v[i];
    p0=h;
    //    break;
  } else {
    
    printf("-------");
    //    vv=v[i];  
	//  exit(1);
  }
  //  i++;


  //printpol(o2v(v[i]));
 
  //  exit(1);
  //memcpy(vv.t,v[i].t,sizeof(v[i].t));
  //      exit(1);
  printf("%d\n",deg(o2v(vv)));
  //    exit(1);
  
  return vv;
}


vec genrandompol(int n){
  vec x={0};
  int i,j=0,k;

  x=init_vec(x);
  for(i=0;i<K+1;i++)
    x.x[i]=xor128()%2;
  
  return x;
}


OP ogcd(OP f,OP g){
  OP h;
  oterm a,b;
  int i=0;

  a=LT(f);
  b=LT(g);
  //printpol(o2v(f));
  //printpol(o2v(g));
  //  exit(1);
  
  while(i<T && deg(o2v(f))>=deg(o2v(g))){
    memset(ss.t,0,DEG);
    h=omod(f,g);
  //printpol(o2v(h));
  //  exit(1);
  f=g;
  g=h;
  //  memcpy(f.t,g.t,sizeof(g.t));
  //memcpy(g.t,h.t,sizeof(h.t));
  /*
  a=LT(f);
  printf("%dx%d\n",a.a,a.n);
  b=LT(g);
  printf("%dx%d\n",b.a,b.n);
  */
  i++;
   if(deg(o2v(g))<=T-1)
     break;
  }
  // exit(1);

    
  return h;
}


OP bibun(vec a){
  OP w[T]={0};
  OP l={0},t={0};
 int i,j,k,n;
 vec tmp={0};
 
 
 n=deg(a);
 printf("n=%d\n",n);
 if(n==0){
   printf("baka8\n");
  exit(1);
 }
 
 for(i=0;i<T;i++){
   w[i].t[0].a=a.x[i];
   w[i].t[0].n=0;
   w[i].t[1].a=1;
   w[i].t[1].n=1;
   //printpol(o2v(w[i]));
 }
 //  exit(1);

 for(i=0;i<T;i++){
   tmp.x[0]=1;
   t=v2o(tmp);
   for(j=0;j<T;j++){
     if(i!=j)
       t=omul(t,w[j]);
   }
   //printpol(o2v(t));
   if(deg(o2v(t))==0){
     printf("baka9\n");
     exit(1);
   }
   l=oadd(l,t);
    //printpol(o2v(l));
    /*
    if(deg(o2v(l))==0){
      printf("baka7\n");
      exit(1);
    }
    */
 }
 // printf("l=");
 //printpol(o2v(l));
 /*
 if(deg(o2v(l))==0){
   printf("baka6\n");
   exit(1);
 }
 */
 // printf("%d\n",oinv(2));
 // exit(1);
 

 
  return l;
}


vec chen(OP f){
  vec e={0};
  int i,count=0,n,x=0;
  unsigned short y[256]={0},z;
  oterm d={0};
  OP g={0};

  
//  e=o2v(f);
n=deg(o2v(f));
  for(x=0;x<M;x++){
    z=0;
    for(i=0;i<n+1;i++){
       if(f.t[i].a>0)
      z^=gf[mlt(mltn(f.t[i].n,fg[x]),fg[f.t[i].a])];
    }
    if(z==0){
      e.x[count]=x;
      count++;
    }
    //    printf("%d\n",x);
  }
  //printpol(e);
  // exit(1);
 

return e;
}

OP decode(OP f,OP s){
int i,j,k;
 OP r={0},h={0},w={0},e={0},l={0};
 oterm t1,t2,d1,a,b;
 vec x={0};
 unsigned short d=0;
 
 
 printf("in decode\n");
 r=vx(f,s);
 // exit(1);
 
 if(deg(o2v(r))==0){
   printf("baka12\n");
    exit(1);
 }
 x=chen(r);
 for(i=0;i<T;i++)
  printf("x=%d ",x.x[i]);
  printf("\n");
  printf("あっ、でる！\n");  

 
  if(deg(o2v(r))<T){
    printpol(o2v(r));
   printf("baka5 deg(r)<T\n");
   exit(1);
 }
 
 
 // printpol(x);
 //   exit(1);

 w=bibun(x);
 //  w=oterml(w,d1);
 //printpol(o2v(w));
printf("@@@@@@@@@\n");
//exit(1);

 h=ogcd(f,s);
 //printpol(o2v(h));
 // exit(1);
t1=LT(r);
t2.a=t1.a;
t2.n=0;
/*
 if(deg(o2v(w))==0){
   printf("baka3");
   exit(1);
 }
*/
 if(deg(o2v(w))==0){
   printpol(o2v(w));
 }
l=oterml(w,t2);
/*
 if(deg(o2v(l))==0){
   printf("baka5\n");
   exit(1);
 }
*/
 printf("\n");
 
 for(i=0;i<T;i++){
   printf("%d ",trace(l,x.x[i]));
   if(trace(l,x.x[i])==0 || trace(h,x.x[i])==0){
     printpol(o2v(l));
     printpol(o2v(h));
     if(trace(l,x.x[i])==0 && trace(h,x.x[i])>0){
     printf("l=%d is 0 deg(x)=%d\n",i,deg(x));
       }else if(trace(l,x.x[i])>0 && trace(h,x.x[i])==0){
	 printf("h=0\n");
     }else if(trace(l,x.x[i])==0 && trace(h,x.x[i])==0){
       printf("l=0 & h=0\n");
     }
     if(x.x[i]==1)
       printf("x=1\n");
     exit(1);
   }
 }
 printf("\n\n");
 for(i=0;i<T;i++){
   printf("%d ",trace(h,x.x[i]));
   if(trace(h,x.x[i])==0){
     printpol(o2v(l));
     printpol(o2v(h));
     if(deg(x)<T-1){
	 printf("h=%d %d is 0 too few error deg(x)=%d\n",i,x.x[i],deg(x));
	 exit(1);
     }
   }
 }

 printf("%d\n",deg(x)+1);
 
 //    exit(1);
for(i=0;i<deg(x)+1;i++){
  //  if(x.x[i]>0){
  e.t[i].a=gf[mlt(fg[trace(h,x.x[i])],oinv(trace(l,x.x[i])))];
e.t[i].n=x.x[i];

// }
 }

   for(i=0;i<T;i++)
    if(gf[trace(h,x.x[i])]==0)
      printf("h=0");
  printf("\n");
  for(i=0;i<T;i++)
    if(gf[oinv(trace(l,x.x[i]))]==0)
      printf("l=0");
  printf("\n");

  // exit(1);

 /*
   if(x.x[i]==0){
     printf("baka!");
     exit(1);
   }
 */

 printf("\n");

 
return e;
}


OP decode2(OP f,OP s){
  int i,j,k,u=0;
  OP r={0},h={0},w={0},e={0},l={0},ll={0},gg={0};
  oterm t1,t2,d1,b,c;
  vec x={0},y={0};

 gg.t[0].a=1;gg.t[0].n=0;
 gg.t[1].a=1;gg.t[1].n=1;
 printf("in decode\n");
 r=vx(f,s);
 r=omul(r,gg);
 printpol(o2v(r));
 if(deg(o2v(r))==0){
   printf("baka12\n");
    exit(1);
 }
 x=chen(r);
 // r=omul(v2o(x),gg);
 //x=o2v(r);
 for(i=0;i<T;i++)
   printf("x=%d\n",x.x[i]);
 printf("\n");
 // printpol(x);
 //  exit(1);
 if(deg(x)==0){
   printf("baka5\n");
   exit(1);
 }
   
 // printpol(x);
 //   exit(1);

 w=bibun(x);
 //  w=oterml(w,d1);
 printpol(o2v(w));
printf("@@@@@@@@@\n");
//exit(1);

 h=ogcd(f,s);
 printpol(o2v(h));
 // exit(1);
t1=LT(r);
t2.a=t1.a;
t2.n=0;
/*
 if(deg(o2v(w))==0){
   printf("baka3");
   exit(1);
 }
*/
 if(deg(o2v(w))==0){
   printpol(o2v(w));
 }
l=oterml(w,t2);
/*
 if(deg(o2v(l))==0){
   printf("baka5\n");
   exit(1);
 }
*/
printpol(o2v(l));
printpol(o2v(h));
 printf("%d\n",deg(x)+1);
 //    exit(1);
for(i=0;i<deg(x)+1;i++){
  //  if(x.x[i]>0){
  e.t[i].a=gf[mlt(fg[trace(h,x.x[i])],oinv(trace(l,x.x[i])))];
e.t[i].n=x.x[i];
// }
 }
 for(i=0;i<T;i++){
   printf("%d ",trace(h,x.x[i]));
 }
 printf("\n");
 for(i=0;i<T;i++){
   printf("%d ",trace(l,x.x[i]));
 }
 /*
   if(x.x[i]==0){
     printf("baka!");
     exit(1);
   }
 */

 printf("\n");

 return e;
}


OP setpol(unsigned short f[],int n){
OP g;
vec a;
 int i;

 
 //  memset(c,0,DEG);
 for(i=0;i<K+1;i++)
   c[i]=0;
  //memcpy(c,f,n);
  for(i=0;i<n;i++)
    c[i]=f[i];
  a=Setvec(n);
  g=v2o(a);


return g;
}


void det(unsigned short g[K+1]){
  OP f,h={0},w;
  unsigned short cc[K+1]={0},d[2]={0},HH[K][M]={0};
  int i,j,a,b;
  oterm t={0};
  vec e;
  
    for(i=0;i<K+1;i++)
      printf("%d ",cc[i]);
    printf("\n");

#pragma omp parallel for       
  for(i=0;i<M;i++){
    //memcpy(cc,g,K+1);
    for(j=0;j<K+1;j++)
      cc[j]=g[j];
    w=setpol(g,K+1);

    a=trace(w,i);

    
    printf("a=");
    printf("%d ",gf[oinv(a)]);
   
  printf("\n");

  
  for(j=0;j<K+1;j++)
    printf("%d ",cc[j]);
  printf("\n");
    
  cc[K]^=a;
  f=setpol(cc,K+1);
    printpol(o2v(f));
  //  exit(1);
     
  for(j=0;j<K+1;j++)
    printf("%d ",cc[j]);
  printf("\n");
    
  //    exit(1);
  //d[0]=i;
  //d[1]=1;
  h.t[0].a=i;
  h.t[0].n=0;
  h.t[1].a=1;
  h.t[1].n=1;

    memset(ss.t,0,DEG);
  omod(f,h);

  //  printpol(o2v(ss));
  //  exit(1);

  b=oinv(a);
  t.a=gf[b];
  t.n=0;
  //  printf("t=%d\n",t.a);
  //  exit(1);
  w=oterml(ss,t);
  //  printpol(o2v(w));
  e=o2v(w);
  //  #pragma omp parallel for 
  for(j=0;j<K;j++){
    printf("%d,",e.x[K-1-j]);
    HH[j][i]=e.x[K-1-j];
  }
  printf("\n");
  
  //    if(i==1)
  //  exit(1);
  }
  
  //#pragma omp parallel for    
  for(i=0;i<K;i++){
    for(j=0;j<M;j++){
    m2[i][j]=mat[i][j]=HH[i][j];
    //          printf("%d,",mat[i][j]);
  }
    printf("\n");
  }
    
    //      exit(1);
}
  

void bdet(){
  int i,j,k,l;
  unsigned char dd[E*K]={0};
  FILE *ff;
  

  ff=fopen("Hb.key","wb");
  

  for(i=0;i<M;i++){
    for(j=0;j<K;j++){
      l=mat[j][i];
      for(k=0;k<E;k++){
	BH[j*E+k][i]=l%2;
	l=(l>>1);
      }
    }
  }
  for(i=0;i<M;i++){
    for(j=0;j<E*K;j++){
      printf("%d,",BH[j][i]);
      dd[j]=BH[j][i];
    }
    fwrite(dd,1,E*K,ff);
    printf("\n");
  }
  fclose(ff);
}
 
/*
void pubkeygen(){
  int i,j,k,l;
  FILE *fp;
  unsigned char dd[E*K]={0};

  
  fp=fopen("pub.key","wb");
  for(i=0;i<E*K;i++){
    for(j=0;j<M;j++){
      for(k=0;k<E*K;k++){
	tmp[i][j]^=cl[i][k]&BH[k][j];
      }
    }
  }
  P2Mat(P);

  for(i=0;i<E*K;i++){
      for(j=0;j<M;j++){
      for(k=0;k<M;k++)
      pub[i][j]^=tmp[i][k]&A[k][j];
    }
  }
  for(i=0;i<M;i++){
    for(j=0;j<E*K;j++){
     dd[j]=pub[j][i];
    }
    fwrite(dd,1,E*K,fp);
  }
  fclose(fp);  
}
*/

void Pgen(){
  unsigned int i,j;
  FILE *fp;
  

  fp=fopen("P.key","wb");
  random_permutation(P);
  for(i=0;i<D;i++)
    inv_P[P[i]]=i;
  fwrite(P,2,M,fp);
  fclose(fp);
  
  for(i=0;i<D;i++)
    printf("%d,",inv_P[i]);
  printf("\n");
  

  fp=fopen("inv_P.key","wb");
  fwrite(inv_P,2,M,fp);
  fclose(fp);

}

/*
void keygen(){
  
  int i;
  FILE *fp;
  

  det(g);
  makeS();
  bdet();
  Pgen();
  pubkeygen();  


  
}
*/
void key2(){
  FILE *fp;
  unsigned short dd[K]={0};
  int i,j;

  
  fp=fopen("H.key","wb");
  det(g);  
      for(i=0;i<M;i++){
	for(j=0;j<K;j++)
	  dd[j]=mat[j][i];
	fwrite(dd,2,K,fp);
	
      }
      fclose(fp);

}

void encrypt(){


}


void decrypt(){



}


int main(int argc,char **argv){
  int i,j,k,l,c;
  unsigned long a,x,count=1;
  //  unsigned short cc[K]={0};
  unsigned short m[K],mm[T]={0},dd[K*M]={0};
  time_t timer;
  FILE *fp,*fq;

  unsigned short g2[7]={1,0,9,0,0,6,4};
  //  unsigned short s[K]={0}; //{4,12,7,8,11,13};
  unsigned short jj[T]={0};
  unsigned short ee[10]={1,2,3,4,5,6,7,8,9,10};
  unsigned short zz[M]={0};
  //  unsigned short zz[T]={10,97,114,105,97,98,108,101,32,80,111,108,121,110,111,109};
  int y,flg,o1=0;
  OP f={0},h={0},r={0},w={0},aa[T]={0},tt={0};
  vec v;
  unsigned short d=0;
  time_t t;
  

  //  unsigned short syn[K]={4,12,7,8,11,13};
  //  unsigned short g[K+1]={1,0,0,0,1,0,1};

  //  makegf(M);
  //  makefg(M);
  srand(clock()+time(&t));

  //keygen();
  //  key2(g);
  //exit(1);
  
  

  /*
  do{
  flg=0;
  v=genrandompol(K+1);
  for(i=0;i<K+1;i++)
    g[i]=(unsigned short)v.x[i];
    for(i=0;i<K+1;i++){
      w=setpol(g,K+1);
      a=trace(w,i);
    if(a==0)
      flg=1;
      }
  } while(deg(v)<K || flg==1);
  */

  w=setpol(g,K+1);
  printf("すげ、オレもうイキそ・・・\n");

  uu=0;
  for(i=0;i<M;i++){
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
  
  j=0;
  while(j<T){
    flg=0;
    if(jj[j]==0){
      l=xor128()%M;
   	for(k=0;k<T;k++){
	  if(l==jj[k])
	    flg=1;
	}
	if(flg==0){
	  jj[j]=l;
	  j++;
	}
    }
  }
  for(i=0;i<T;i++)
    zz[jj[i]]=1;
  
  
  det(g);
  //exit(1);
  /*
  fq=fopen("H.key","rb");

  fread(dd,2,K*M,fq);
  for(i=0;i<M;i++){
  for(j=0;j<K;j++)
    mat[j][i]=dd[K*i+j];
    }
   
  for(i=0;i<K;i++){
    for(j=0;j<M;j++)
      printf("%d,",mat[i][j]);
    printf("\n");
  }
  */
  for(j=0;j<M;j++){
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
  
  //  exit(1);   

  
  printf("zz=");
   #pragma omp parallel for
  for(i=0;i<K;i++){
    syn[i]=0;

    for(j=0;j<M;j++){
      printf("%u,",zz[j]);
      syn[i]^=gf[mlt(fg[zz[j]],fg[mat[i][j]])];
    }
    //    printf("%d,",syn[i]);
  }
  printf("\n");
  //    exit(1);  
  for(i=0;i<K;i++)
    printf("mat[%d][1]=%d\n",i,mat[i][1]);
  printf("\n");
  //  exit(1);

  
  f=setpol(syn,K);

  r=decode(w,f);

  
  
  for(i=0;i<T;i++){
    mm[i]=r.t[i].a;
    if(i==0){
     printf("e=%d %d %s\n",r.t[i].a,r.t[i].n,"う");
    }else{     printf("e=%d %d %s\n",r.t[i].a,r.t[i].n,"お");
}
    if(r.t[i].a==0 || r.t[i].n==0){
      printf("------------------\n");
      
       printf("err=%d i=%d\n",o1,i);
      exit(1);
    }
  }
  printf("         っ！！\n");
    for(i=0;i<M;i++){
    if(zz[i]>0)
      o1++;
  }
  printf("err=%d\n",o1);


  return 0;
}
