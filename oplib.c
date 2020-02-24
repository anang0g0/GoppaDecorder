//date 20200222 : pattarson algorithm implementation ver 1.0
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

#include "chash.cpp"
#include "lu.c"


#define K 128*2
#define DEG 3*K
#define T K/2
#define E 13
#define D 6688

unsigned char tmp[E*K][D]={0};
unsigned char pub[E*K][D]={0};
unsigned char BH[E*K][D]={0};
unsigned short c[2*K+1]={0};
unsigned short mat[K][D]={0};
unsigned short m2[K][D]={0};

static unsigned short g[K+1]={0};
//{1,0,0,0,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,0,1,0,1,1,0,0,1,0,0,0,0,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,1,0,0,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,1,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,0,0,1,1,1,1,0,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1};
  /*
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
		       0,0,0,0,0,0,0,0,0,0,
		       		       0,0,0,0,0,0,0,0,0,0,
		       		       0,0,0,0,0,0,0,0,0,0,
		       		       0,0,0,0,0,0,0,0,0,0,
		       0,1};
  */
  //  unsigned short g[K+1]={1,1,0,1,1,0,0,1,1,0,1};
//unsigned short g[K+1]={1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

//,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
//unsigned short g[K+1]={1,0,0,0,1,0,1};
unsigned short syn[K]={0};
unsigned char A[D][D]={0};
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

typedef struct {
  OP u;
  OP v;
  OP d;
} EX;

typedef union {
  unsigned long long int u[4];
  unsigned short s[16];
} SU;

OP ss={0};
OP hh={0};
OP qq={0};
OP p0={0};


static void ginit(void){
  int i,j,count=0;
  unsigned short gg[K+1]={0};
  //unsigned short g[K+1]={0};
  
  printf("in ginit\n");
  //   g[128]=g[126]=g[124]=g[120]=g[118]=g[117]=g[116]=g[115]=g[114]=g[113]=g[112]=g[110]=g[108]=g[106]=g[105]=g[104]=g[102]=g[101]=g[99]=g[98]=g[97]=g[94]=g[93]=g[89]=g[88]=g[85]=g[82]=g[81]=g[78]=g[77]=g[76]=g[74]=g[72]=g[69]=g[68]=g[66]=g[62]=g[61]=g[60]=g[57]=g[56]=g[54]=g[52]=g[51]=g[49]=g[48]=g[47]=g[46]=g[41]=g[40]=g[36]=g[35]=g[32]=g[30]=g[28]=g[27]=g[26]=g[24]=g[19]=g[17]=g[13]=g[10]=g[8]=g[6]=g[4]=g[3]=g[2]=g[1]=g[0]=1;
  // g[256]=g[254]=g[253]=g[249]=g[244]=g[242]=g[239]=g[238]=g[236]=g[235]=g[233]=g[232]=g[228]=g[222]=g[221]=g[220]=g[219]=g[217]=g[214]=g[213]=g[212]=g[206]=g[205]=g[203]=g[202]=g[201]=g[199]=g[195]=g[194]=g[193]=g[192]=g[191]=g[186]=g[183]=g[180]=g[179]=g[178]=g[177]=g[173]=g[170]=g[167]=g[166]=g[165]=g[162]=g[160]=g[157]=g[156]=g[154]=g[151]=g[147]=g[143]=g[142]=g[141]=g[140]=g[139]=g[137]=g[136]=g[135]=g[133]=g[132]=g[131]=g[128]=g[125]=g[122]=g[118]=g[117]=g[115]=g[112]=g[108]=g[107]=g[106]=g[104]=g[103]=g[102]=g[100]=g[97]=g[95]=g[94]=g[90]=g[89]=g[87]=g[85]=g[84]=g[83]=g[81]=g[80]=g[75]=g[70]=g[69]=g[67]=g[66]=g[65]=g[64]=g[63]=g[62]=g[61]=g[60]=g[59]=g[58]=g[57]=g[54]=g[51]=g[49]=g[48]=g[46]=g[45]=g[44]=g[43]=g[42]=g[41]=g[39]=g[36]=g[31]=g[30]=g[26]=g[23]=g[22]=g[21]=g[16]=g[14]=g[13]=g[10]=g[8]=g[7]=g[6]=g[5]=g[3]=g[1]=g[0]=1;
  
  g[K]=1;
  g[0]=1;
  while(count<K/2-1){
    printf("@\n");
    j=rand()%(K-1);
    if(j<K && j>0 && g[j]==0){
      g[j]=1;
      count++;
	}
  }
  
  
  for(i=0;i<K+1;i++)
    gg[i]=g[K-i];
  for(i=0;i<K+1;i++)
    g[i]=gg[i];
  
}




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


void P2Mat(unsigned short P[D]){
int i,j;
	
  for(i=0;i<D;i++)
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


int distance(OP f){
int i,j,k;

for(i=0;i<DEG;i++){
if(f.t[i].a>0)
  j=i;
}

return j;
}

int terms(OP f){
int i,count=0;

for(i=0;i<DEG;i++)
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


 for(i=0;i<n;i++){
  v.x[n-1-i]=c[i];
 }

 
  return v;
}



void oprintpol(OP f){
int i,j,k,n;

n=distance(f);
printf("n=%d\n",n);
printf("terms=%d\n",terms(f));
printf("deg=%d\n",odeg(f));
 
//exit(1);

for(i=n;i>-1;i--){
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


OP oadd(OP f,OP g){
  vec a={0},b={0},c={0};
  int i,k;
  OP h={0};

  a=o2v(f);
  //exit(1);
  b=o2v(g);
  //  oprintpol((g));
  //  exit(1);
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
  int i,k;
  OP h={0};
  vec test;
  unsigned short n;

  k=distance(f);
  for(i=0;i<k+1;i++){

    h.t[i].n=f.t[i].n+t.n;
    h.t[i].a=gf[mlt(fg[f.t[i].a],fg[t.a])];

  }

  return h;
}


OP omul(OP f,OP g){
  int i,count=0,k;
  oterm t={0};
  OP h={0},e={0},r={0};

  if(deg(o2v(f))>deg(o2v(g))){
    k=deg(o2v(f));
  }else{
    k=deg(o2v(g));
  }

  for(i=0;i<k+1;i++){
    t=g.t[i];
    e=oterml(f,t);
    h=oadd(h,e);
  }

  //printpol(o2v(h));
  //printf(" debug======\n");
  //  exit(1);
  
  return h;
}


oterm LT(OP f){
  int i,k;
  oterm t={0};

  k=deg(o2v(f));
  for(i=0;i<k+1;i++){
    //printf("a=%d %d\n",f.t[i].a,f.t[i].n);
    if(f.t[i].a>0){
      t.n=f.t[i].n;
      t.a=f.t[i].a;
    }
  }

  return t;
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


OP coeff(OP f,unsigned short d){
  int i,j,k;
  vec a,b;
  
  for(i=0;i<deg(o2v(f))+1;i++)
    f.t[i].a=gf[mlt(fg[f.t[i].a],oinv(d))];


  return f;

}


OP omod(OP f,OP g){
  int i=0,j,n,k;
  OP h={0},e={0};
  oterm a,b={0},c={0};
  
  
  n=LT(g).n;
  if(deg(o2v(f))==0){ 
    printf("baka^\n");
    //return f;
    exit(1);
  }
  if(deg(o2v(g))==0){
    printf("baka--\n");
    //return g;
         exit(1);
  }
  if(deg(o2v(f))<deg(o2v(g))){
    //    exit(1);
    return f;
  }

  //  printf("in omod\n");
  //exit(1);
  k=deg(o2v(g));
  b=LT(g);
  
  

    printf("b=========%dx^%d\n",b.a,b.n);
    printpol(o2v(g));
    if(b.a==0 && b.n==0){
      printf("double baka\n");
      exit(1);
    }
      
    printf("\nin omod g=============%d\n",deg(o2v(g)));
    while((deg(o2v(f))>0 && deg(o2v(g)))>0){
      printf("in!\n");
      //    exit(1);
      
      c=LTdiv(f,b);
      //   printf("c========%dx^%d\n",c.a,c.n);
      //    exit(1);
      //ss.t[i]=c;
      //i++;
      printpol(o2v(g));
      printf("\ng=================\n");
      
      h=oterml(g,c);
      printpol(o2v(h));
      printf("\n");
      printf("modh===================\n");

      printpol(o2v(f));
      printf("\nmodf===================\n");
      //     exit(1);
      
      f=oadd(f,h);
      if(deg(o2v(f))>0)
      printpol(o2v(f));
      printf("\nff1=====================\n");
      if(LT(f).a==0 || LT(g).a==0){
	printf("baka500\n");
	return f;
      }

      if(c.n==0)
	break;
    }
    
    return f;
}


OP odiv(OP f,OP g){
  int i=0,j,n,k;
  OP h={0},e={0},tt={0},o={0};
  oterm a,b={0},c={0};

  o=f; 

  if(deg(o2v(f))==0 && g.t[0].a==0){ 
    printf("baka^\n");
    //return f;
        exit(1);
  }
  if(LT(g).a==0){
    printf("baka--\n");
    exit(1);
  }
  if(deg(o2v(g))==0 && g.t[0].a>1)
    return coeff(f,g.t[0].a);
    printf("in odiv\n");
    //printpol(o2v(g));
    
  //exit(1);
    k=deg(o2v(g));
    b=LT(g);
    printpol(o2v(g));
    printf("in odiv1 g===========%d %d\n",b.a,b.n);
    if(b.a==1 && b.n==0)
      return f;
    if(b.a==0 && b.n==0){
      printf("baka in odiv\n");
      exit(1);
    }
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
 while(deg(o2v(f))>0 && deg(o2v(g))>0){
    //  printf("in!\n");
    //    exit(1);
    
    c=LTdiv(f,b);
    //    if(c.a>0){
    // printf("in odev c========%dx^%d\n",c.a,c.n);
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
    
      f=oadd(f,h);
    
      //printpol(o2v(f));
      //printf("\nff=====================\n");
      if(deg(o2v(f))>500){
	printf("baka500\n");
	exit(1);
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




// invert of polynomial
OP inv(OP a,OP n){
  OP d={0},x={0},s={0},q={0},r={0},t={0},u={0},v={0},w={0},tt={0},gcd={0};
  oterm b={0};
  vec vv={0},xx={0};

  
  if(deg(o2v(a))>deg(o2v(n))){
    printf("baka_i\n");
    exit(1);
  }
  if(LT(a).a==0){
    printf(" a ga 0\n");
    exit(1);
  }
    
  tt=n;
  
  printf("n=============\n");
  printpol(o2v(n));
  printf("\n");
  printf("a=============\n");
  printpol(o2v(a));
  printf("\n");
  //  exit(1);
  
  d = n;
  x.t[0].a = 0;
  x.t[0].n = 0;
  s.t[0].a = 1;
  s.t[0].n = 0;
  while (LT(a).n>0){

    r=omod(d ,a);
    q=odiv(d, a);
    
    d = a;
    a = r;
    t=oadd(x,omul(q,s));
    printpol(o2v(a));
    printf("\nin roop a==================%d\n",deg(o2v(a)));
    printf("\n");
    
    x = s;
    s = t;
  }
  // exit(1);
  //  if(LT(a).a>0){
    d = a;
    a = r;
    printpol(o2v(a));
    printf("\nin roop a|==================%d\n",deg(o2v(a)));
    printf("\n");
    
    x = s;
    s = t;

   printpol(o2v(d));
   printf("\nout1================\n");
     gcd = d;  // $\gcd(a, n)$
     printpol(o2v(gcd));
   printf("\n");
   printpol(o2v(n));
   printf("\n");
   printf("out2===============\n");
   
   printf("before odiv\n");
   //w=tt;

   b=LT(w);
   printpol(o2v(w));
   printf("\nw=======%d %d\n",b.a,b.n);
   //w=tt;
   v=oadd(x,n);
   printpol(o2v(v));
   printf("\n");
   if(LT(v).a==0){
     printf("v=============0\n");
   }
     
    printf("d==============\n");
    //  } //end of a>0
  w=tt;
  printpol(o2v(v));
  printf("\n");
  printf("ss==============\n");
  //       exit(1);
  // if(deg(o2v(w))>0)
  if(LT(v).a>0){
  u=omod(v, w);
  }else{
    printpol(o2v(x));
    printf(" x==0?\n");
    printpol(o2v(n));
    printf(" n==0?\n");
    
    exit(1);
  }
  if(LT(u).a>0 && LT(d).a>0){
    u=odiv(u, d);
  }

  if(LT(u).a==0 || LT(d).a==0){
    printf("inv div u or d==0\n");
    // exit(1);
  }
  //u=coeff(u,d.t[0].a);
  printpol(o2v(u));
  printf("\nu==================\n");
  if(LT(u).a==0){
    printf("no return at u==0\n");
    exit(1);
  }

  
  return u;

}


OP ToHorner(OP f){
  OP h;
  int i;
  vec v;

  v=o2v(f);


  return h;
}


OP vx(OP f,OP g){
  OP h={0},ww={0};
  OP v[K]={0},vv={0};
  oterm a,b;
  int i,j;

  v[0].t[0].a=0;
  v[0].t[1].n=0;
  v[1].t[0].a=1;
  v[1].t[1].n=0;

  //printf("in vx\n");
  //  exit(1);
  
  for(i=0;i<T;i++){
    // memset(ss.t,0,DEG*sizeof(ss));
    //    if(deg(o2v(f))>=deg(o2v(g)) && deg(o2v(g))>0){
    if(deg(o2v(vv))<T){
      
      h=omod(f,g);
      printpol(o2v(h));
      printf(" modh vx==============\n");
      ww=odiv(f,g);
    }
    
    printf("ww======= ");
    printpol(o2v(ww));
    printf("\n");
    v[i+2]=oadd(v[i],omul(ww,v[i+1]));
    printf("-------");
    memset(f.t,0,sizeof(f.t));
    f=g;
    //memcpy(f.t,g.t,sizeof(g.t));
    memset(g.t,0,sizeof(g.t));
    g=h;
    
    if(deg(o2v(v[i+2]))<=T){
      vv=v[i+2];
      printf("vv==");
      printpol(o2v(vv));
      printf("\n");
      ss=h;
      // printpol(o2v(h));
      printf(" ll========\n");
      //    return vv;
      
    } else {
      
      printf("-------");
      break;
    }
  }
  printpol(o2v(vv));
  printf(" vv============\n");
  //exit(1);
  
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






unsigned int ipow(unsigned int q,unsigned int u){
unsigned int i,m=1;

  for(i=0;i<u;i++)
    m*=q;

  printf("in ipow====%d\n",m);

  return m;
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


  //oprintpol((f));
  //oprintpol((g));
  //  exit(1);
  
  for(i=0;i<T;i++){// && deg(o2v(f))>=deg(o2v(g))){
  //while(deg(o2v(g))<T){
    //    memset(ss.t,0,DEG);
    h=omod(f,g);
    ww=odiv(f,g);
  f=g;
  g=h;
  //  i++;
  //   if(deg(o2v(g))<T)
  // break;
  }
  // exit(1);

    
  return h;
}



EX xgcd(OP f,OP g){
  OP h={0},ww={0},v[K*2]={0},u[K*2]={0};
  oterm a,b;
  int i=0,j,k;
  EX e={0};

  
  u[0].t[0].a=1;
  u[0].t[0].n=0;
  u[1].t[0].a=0;
  u[1].t[0].n=0;
  u[2].t[0].a=1;
  u[2].t[0].n=0;

  v[0].t[0].a=0;
  v[0].t[0].n=0;
  v[1].t[0].a=1;
  v[1].t[0].n=0;


  //printpol(o2v(f));
  //printpol(o2v(g));
  //  exit(1);


  k=0;
  //i=1;
  for(i=0;i<T;i++){
    if(LT(g).a==0)
      break;
    h=omod(f,g);
    ww=odiv(f,g);
   
    v[i+2]=oadd(v[i],omul(ww,v[i+1]));
    u[i+2]=oadd(u[i],omul(ww,u[i+1]));
    printf("i+1=%d\n",i+1);
    f=g;
    g=h;
  
  }  
    
    //v[i]=odiv(v[i],h);
    //u[i]=odiv(u[i],h);
    // h.t[0].a=1;
    //h.t[0].n=0;
    printf("i=%d\n",i);
    printpol(o2v(v[i]));
    printf(" v=============\n");
    printpol(o2v(u[i]));
    printf(" u=============\n");
    printpol(o2v(h));
    printf(" h=============\n");
    //exit(1);
    
    e.d=h;
    e.v=v[i];
    e.u=u[i];
    
  
    
  return e;
}


OP bibun(vec a){
  OP w[T*2]={0};
  OP l={0},t={0};
 int i,j,k,n;
 vec tmp={0};
 
 
 n=deg(a);
 printf("n=%d\n",n);
 if(n==0){
   printf("baka8\n");
   //  exit(1);
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
     // exit(1);
   }
   l=oadd(l,t);
 }
 
 
  return l;
}


vec chen(OP f){
  vec e={0};
  int i,count=0,n,x=0;
  unsigned short y[256]={0},z;
  oterm d={0};
  OP g={0};

  //  exit(1);
//  e=o2v(f);
n=deg(o2v(f));
//exit(1);
  for(x=0;x<D;x++){
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
 OP r={0},w={0},e={0},l={0};
 oterm t1,t2,d1,a,b;
 vec x={0};
 unsigned short d=0;
 OP h={0};
 EX hh={0};

 
 printf("in decode\n");
 printpol(o2v(s));
 printf("\nsyn===========\n");
  r=vx(f,s);
  //hh=xgcd(f,s);
 
 if(deg(o2v(r))==0){
   printf("baka12\n");
    exit(1);
 }
 k=0;
 // exit(1);
 x=chen(r);
 // exit(1);


 
 for(i=0;i<T;i++){
  printf("x[%d]=1\n",x.x[i]);
  if(x.x[i]==0)
    k++;
  if(k>1){
    printf("baka0\n");
    exit(1);
  }
 }
 //   exit(1);
 
 //  printf("\n");
 
  printf("あっ、でる！\n");  
  //  exit(1);
 
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

 hh=xgcd(f,s);
 printpol(o2v(hh.d));

 //  exit(1);
t1=LT(r);
// printf("t1=%d %d\n",t1.a,t1.n);
// exit(1);
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
 printf("%d\n",deg(x)+1);
 
 //    exit(1);
for(i=0;i<deg(x)+1;i++){
  //  if(x.x[i]>0){
  e.t[i].a=gf[mlt(fg[trace(hh.d,x.x[i])],oinv(trace(l,x.x[i])))];
e.t[i].n=x.x[i];

// }
 }

   for(i=0;i<T;i++)
    if(gf[trace(hh.d,x.x[i])]==0)
      printf("h=0");
   //printf("\n");
  for(i=0;i<T;i++)
    if(gf[oinv(trace(l,x.x[i]))]==0)
      printf("l=0\n");
  //  printf("\n");
  
 
return e;
}




OP setpol(unsigned short *f,int n){
OP g;
vec a;
 int i;

 
 memset(c,0,sizeof(c));
   // for(i=0;i<K+1;i++)
   // c[i]=0;
 memcpy(c,f,sizeof(c));
 //  for(i=0;i<n;i++)
 //  c[i]=f[i];
  a=Setvec(n);
  g=v2o(a);


return g;
}




void det(unsigned short g[]){
  OP f,h={0},w,u;
  unsigned short cc[K+1]={0},d[2]={0};
  unsigned short **HH;
  int i,j,a,b;
  oterm t={0};
  vec e;

  HH=malloc(D*sizeof(unsigned short *));
  for(i=0;i<2*K+1;i++) {
	HH[i] = malloc(sizeof(unsigned short) * D);
}
  //    memcpy(cc,g,sizeof(g));
  for(i=0;i<K+1;i++){
      cc[i]=g[i];
    printf("%d,",g[i]);
  }
  printf("\n");
  //  exit(1);
    //    cc[i]=g[i];
  k=cc[K];
  w=setpol(g,K+1);

  //#pragma omp parallel for       
  for(i=0;i<D;i++){
  
  a=trace(w,i);
  cc[K]=k;
  
  cc[K]^=a;
  f=setpol(cc,K+1);
  
  h.t[0].a=i;
  h.t[0].n=0;
  h.t[1].a=1;
  h.t[1].n=1;

  OP ww={0};

  memset(ss.t,0,sizeof(ss.t));
  ww=odiv(f,h);

  b=oinv(a);
  t.a=gf[b];
  t.n=0;

  u=oterml(ww,t);
  e=o2v(u);
  
  #pragma omp parallel for 
  for(j=0;j<K;j++)
    HH[j][i]=e.x[K-1-j];  

  }
  
  
  //#pragma omp parallel for    
  for(i=0;i<K;i++){
    //#pragma omp parallel for
    for(j=0;j<D;j++){
    m2[i][j]=mat[i][j]=HH[i][j];
    printf("%d,",mat[i][j]);
    }
    printf("\n");
  }  
  // exit(1);
}


void det2(unsigned short g[]){
  OP f,h={0},w,u;
  unsigned short cc[K+1]={0},d[2]={0};
  unsigned short **HH;
  int i,j,a,b,aa=0;
  oterm t={0};
  vec e[2*K]={0};

  
  HH=malloc(D*sizeof(unsigned short *));
  for(i=0;i<2*K+1;i++) {
	HH[i] = malloc(sizeof(unsigned short) * D);
}
  //    memcpy(cc,g,sizeof(g));
  for(i=0;i<K/2+1;i++){
      cc[i]=g[i];
    printf("%d,",g[i]);
  }
  printf("\n");
  //exit(1);
    //    cc[i]=g[i];
  k=cc[K];
  w=setpol(g,K/2+1);
  printpol(o2v(w));
  printf("\nw=================\n");
  //  exit(1);
  //#pragma omp parallel for       
  for(i=0;i<D;i++){
  
  a=trace(w,gf[i]);
  //  cc[K]=k;
  
  //cc[K]^=a;
  //f=setpol(cc,K+1);
  
  h.t[0].a=gf[i];
  h.t[0].n=0;
  h.t[1].a=1;
  h.t[1].n=1;

  OP ww={0};

  //  memset(ss.t,0,sizeof(ss.t));
  // ww=odiv(f,h);

  b=oinv(a);
  // b=b-1;
  printf("g^-%d=%d\n",i,mlt(b,b));
  //for(j=0;j<K;j++)
  //  for(j=0;j<K;j++){

  /*
  e[0].x[i]=b;
  e[1].x[i]=mlt(b,fg[gf[i]^f.t[1].a]);
  */

  e[0].x[i]=mlt(b,b);
  aa=gf[i]; //gf[mltn(j,i)]^gf[mlt(j-1,mlt(7,7))];
  e[1].x[i]=mlt(mlt(b,b),fg[aa]);
  e[2].x[i]=mlt(mlt(b,b),fg[gf[mltn(2,fg[aa])]^gf[15]]);
   e[3].x[i]=mlt(mlt(b,b),fg[gf[mltn(3,fg[aa])]^gf[mlt(15,fg[aa])]]);
  /*
    aa=0;
  for(j=1;j<2*K+1;j++){
    aa^=gf[mltn(j,i)]^gf[mlt(j-1,mlt(7,7))];
    e[j].x[i]=mlt(mlt(b,b),fg[aa]);
    }
  t.n=0;
  */
  //  exit(1);
  //u=oterml(ww,t);
  //e=o2v(u);
  
  #pragma omp parallel for 
  for(j=0;j<2*K;j++)
    HH[j][i]=e[j].x[i]; //e.x[K-1-j];  

  }
  
  
  //#pragma omp parallel for    
  for(i=0;i<K;i++){
    //#pragma omp parallel for
    for(j=0;j<D;j++){
    m2[i][j]=mat[i][j]=HH[i][j];
    printf("%d,",mat[i][j]);
    }
    printf("\n");
  }  
  //  exit(1);
}



void bdet(){
  int i,j,k,l;
  unsigned char dd[E*K]={0};
  FILE *ff;
  

  ff=fopen("Hb.key","wb");
  

  for(i=0;i<D;i++){
    for(j=0;j<K;j++){
      l=mat[j][i];
      //#pragma omp parallel for 
      for(k=0;k<E;k++){
	BH[j*E+k][i]=l%2;
	l=(l>>1);
      }
    }
  }
  for(i=0;i<D;i++){
    //#pragma omp parallel for 
    for(j=0;j<E*K;j++){
      //  printf("%d,",BH[j][i]);
      dd[j]=BH[j][i];
    }
    fwrite(dd,1,E*K,ff);
    //printf("\n");
  }
  fclose(ff);
}
 

void pubkeygen(){
  int i,j,k,l;
  FILE *fp;
  unsigned char dd[E*K]={0};

  
  fp=fopen("pub.key","wb");
  for(i=0;i<E*K;i++){
    for(j=0;j<D;j++){
      //#pragma omp parallel for 
      for(k=0;k<E*K;k++){
	tmp[i][j]^=cl[i][k]&BH[k][j];
      }
    }
  }
  P2Mat(P);

  for(i=0;i<E*K;i++){
    //  for(j=0;j<D;j++){
    //#pragma omp parallel for 
      for(k=0;k<D;k++)
	pub[i][k]=tmp[i][P[k]];//&A[k][j];
      //    }
  }
  for(i=0;i<D;i++){
    //#pragma omp parallel for 
    for(j=0;j<E*K;j++){
     dd[j]=pub[j][i];
    }
    fwrite(dd,1,E*K,fp);
  }
  fclose(fp);  

}


void Pgen(){
  unsigned int i,j;
  FILE *fp;
  

  fp=fopen("P.key","wb");
  random_permutation(P);
  for(i=0;i<D;i++)
    inv_P[P[i]]=i;
  fwrite(P,2,D,fp);
  fclose(fp);
  
  for(i=0;i<D;i++)
    printf("%d,",inv_P[i]);
  printf("\n");
  

  fp=fopen("inv_P.key","wb");
  fwrite(inv_P,2,D,fp);
  fclose(fp);

}


void key2(unsigned short g[]){
  FILE *fp;
  unsigned short dd[K]={0};

  printf("鍵を生成中です。４分程かかります。\n");
  fp=fopen("H.key","wb");
  det(g);
  //  exit(1);
      for(i=0;i<D;i++){
	for(j=0;j<K;j++)
	  dd[j]=mat[j][i];
	fwrite(dd,2,K,fp);
	
      }
      fclose(fp);

}


void keygen(unsigned short *g){
  
  int i;
  FILE *fp;
  

  key2(g);
  printf("end of ky2\n");
  makeS();
  printf("end of S\n");
  bdet();
  printf("end of bdet\n");
  Pgen();
  printf("end of Pgen\n");
  pubkeygen();  


  
}


void encrypt(){


}


void decrypt(){



}



int isqrt(unsigned short u){
  int i,j,k;

  for(i=0;i<M;i++){
    if(gf[mlt(i,i)]==u)
      return i;
  }

}



OP osqrt(OP f,OP w){
  int i,j,k,jj;
  OP even={0},odd={0},h={0},r={0},ww={0},s={0},tmp={0},t={0};
  oterm o={0};
  vec v={0};

  j=0;
  jj=0;
  k=distance(f);
  for(i=0;i<k+1;i++){
    if(f.t[i].n%2==0){
      even.t[j].n=f.t[i].n/2;
      even.t[j++].a=gf[isqrt(f.t[i].a)];
      printf("a=%d %d\n",f.t[i].a,i);
    }
    if(f.t[i].n%2==1){
      odd.t[jj].n=(f.t[i].n-1)/2;
      odd.t[jj++].a=gf[isqrt(f.t[i].a)];
      printf(" odd %d\n",i);
    }
  }
  printpol(o2v(even));
  printf(" T0============\n");
  printpol(o2v(odd));
  printf(" T1============\n");
  // exit(1);

  
  k=deg(o2v(w));
  printf("%d\n",k);
  //exit(1);
  j=0;
  jj=0;
  for(i=0;i<k+1;i++){
    if(w.t[i].n%2==0){
      h.t[j].a=gf[isqrt(w.t[i].a)];
      h.t[j++].n=w.t[i].n/2;
      printf("wi==%d %d\n",(w.t[i].n/2),i);
    }
    if(w.t[i].n%2==1){
      r.t[jj].a=gf[isqrt(w.t[i].a)];
      r.t[jj++].n=(w.t[i].n-1)/2;

    }
  }
  printpol(o2v(r));
  printf(" sqrt(g0)=======\n");
  
  //  exit(1);
  if(LT(r).n>0){
  s=inv(r,w);
  }else if(LT(r).n==0){
    printpol(o2v(r));
    printf(" r======0\n");
    exit(1);
  }

  
  if(LT(omod(omul(s,r),w)).n>0){
    printf(" r is not inv\n");
     exit(1);
  }
  if(LT(h).n>0){
    ww=omod(omul(h,s),w);
  }else if(LT(h).n==0){
    printf("h=========0\n");
    exit(1);
  }

  if(LT(ww).n==0 && LT(ww).a==0){
    printpol(o2v(s));
    printf(" s===========\n");
    printpol(o2v(w));
    printf(" w==============\n");
    printpol(o2v(h));
    printf(" omod mul h,r===0\n");
    return ww;;
    // exit(1);
  }
  
  tmp=omod(omul(ww,ww),w);
  if(LT(tmp).n==1){
    printpol(o2v(ww));
    printf(" ww succsess!===========\n");
  }else{
    printpol(o2v(tmp));
    printf(" mod w^2==========\n");
    printpol(o2v(ww));
    printf(" ww^2 failed!========\n");
    printpol(o2v(w));
    printf(" w==============\n");

    return ww;
    // exit(1);
  }

  
    //    exit(1);
  printpol(o2v(s));
  printf(" g1^-1=========\n");
  printpol(o2v(h));
  printf(" g0=========\n");
  //exit(1);
  printpol(o2v(ww));
  printf(" ww==========\n");
  //  exit(1);
   h=ww;
  if(odeg(omod(omul(h,ww),w))==1){
    ww=h;
    h=omod(oadd(even,omul(ww,odd)),w);
    return h;
  }else if(LT(ww).a==0){
    printf("vaka\n");
    exit(1);
  }
  
  printpol(o2v(ww));
  printf(" w==========\n");

}


void pattarson(OP w,OP f){

    OP g1={0},ll={0},s={0};
  int i,j,k,l,c;
  unsigned long a,x,count=0;
  //  unsigned short cc[K]={0};
  unsigned short m[K],mm[T]={0},dd[K*D]={0};
  time_t timer;
  FILE *fp,*fq;

  unsigned short g2[7]={1,0,9,0,0,6,4};
  //  unsigned short s[K]={0}; //{4,12,7,8,11,13};
  unsigned short jj[T*2]={0};
  unsigned short ee[10]={1,2,3,4,5,6,7,8,9,10};
  unsigned short zz[D]={0};
  //  unsigned short zz[T]={10,97,114,105,97,98,108,101,32,80,111,108,121,110,111,109};
  int y,flg,o1=0;
  OP h={0},r={0},aa[K]={0},tt={0},ff={0};
  EX hh={0};
  vec v;
  unsigned short d=0;
  time_t t;
  unsigned short gg[K+1]={0};
  oterm rr={0};
  OP r1={0},r2={0},t1={0},t2={0},a1={0},b1={0},a2={0},b2={0};
  
  //unsigned short g[K+1]={2,2,12,1,2,8,4,13,5,10,8,2,15,10,7,3,5};
  unsigned short yy[5]={15,0,8,0,11};

  //srand(clock()+time(&t));
  //printf("@");
  //ginit();

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

  tt.t[0].n=1;
  tt.t[0].a=1;

  
  ff=inv(f,w);
  printpol(o2v(ff));
  printf("locater==========\n");
  //exit(1);
  r2=oadd(ff,tt);
  printpol(o2v(r2));
  printf(" h+x==============\n");
  //  exit(1);
  g1=osqrt(r2,w);
    printpol(o2v(g1));
  printf(" g1!=========\n");
  if(LT(g1).n==0 && LT(g1).a==0){
    printpol(o2v(w));
    printf(" badkey=========\n");
    exit(1);
    // goto label;
  }
  //exit(1);
   hh=xgcd(w,g1);

  ff=omod(omul(hh.v,g1),w);
  printpol(o2v(ff));
  printf(" beta!=========\n");
  if(deg(o2v(ff))!=K/2){
    printf("beta baka\n");
    if(LT(hh.v).n%2==0){
    hh.v=osqrt(hh.v,w);
    ff=omod(omul(hh.v,g1),w);
    printpol(o2v(ff));
    printf("re culc\n");
    //exit(1);
    }else if(LT(ff).n%2==1){
      printpol(o2v(ff));
      printf(" degree baka=============\n");
      exit(1);
    }
  }
  printpol(o2v(hh.v));
  printf(" alpha!=========\n");
  //exit(1);
  ll=oadd(omul(ff,ff),omul(tt,omul(hh.v,hh.v)));
  if(deg(o2v(ll))==0){
    printf("baka0\n");
    exit(1);
  }
  printf("あっ、でる・・・！\n");
  count=0;
  v=chen(ll);
   printf("う\n"); 
   for(i=0;i<T*2;i++){
       
    printf("%d お\n",v.x[i]);
    if(v.x[i]>0)
    ++count;
   }
   printf("err=%dっ!! \n",count);

   //printpol(o2v(w));
   //printf(" poly==========\n");
   //  exit(1);


}


OP keyfinder(void){
  int i,j,k,l,c;
  unsigned long a,x,count=1;
  //  unsigned short cc[K]={0};
  unsigned short m[K],mm[T]={0},dd[K*D]={0};
  time_t timer;
  FILE *fp,*fq;

  unsigned short g2[7]={1,0,9,0,0,6,4};
  //  unsigned short s[K]={0}; //{4,12,7,8,11,13};
  unsigned short jj[T*2]={0};
  unsigned short ee[10]={1,2,3,4,5,6,7,8,9,10};
  short zz[D]={0};
  //  unsigned short zz[T]={10,97,114,105,97,98,108,101,32,80,111,108,121,110,111,109};
  int y,flg,o1=0;
  OP f={0},h={0},r={0},w={0},aa[8]={0},tt={0},ff={0},g1={0};
  EX hh={0};
  vec v;
  unsigned short d=0;
  time_t t;
  unsigned short gg[K+1]={0};
  oterm rr={0};
  OP r1={0},r2={0},t1={0},t2={0},a1={0},b1={0},a2={0},b2={0};

 label:
  for(i=0;i<K+1;i++)
    g[i]=0;
  ginit();
  
  
    w=setpol(g,K+1);
    oprintpol(w);

    #pragma omp parallel for  
  for(i=0;i<D;i++){
    a=trace(w,i);
    if(a==0){
      printf("trace 0 @ %d\n",i);
      goto label;
      //  exit(1);
    }
  }
  printf("@");
  //keygen(g);
  key2(g);

  fq=fopen("H.key","rb");
  
  fread(dd,2,K*D,fq);
  #pragma omp parallel for
  for(i=0;i<D;i++){
  for(j=0;j<K;j++)
    mat[j][i]=dd[K*i+j];
    }
  
  
  for(j=0;j<D;j++){
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
  for(i=0;i<D;i++)
    zz[i]=0;
  
  
  j=0;
  while(j<T*2){
    l=xor128()%D;
    printf("l=%d\n",l);
    if(0==zz[l]){
      zz[l]=1;
      j++;
    }
  }
  

  
  printf("zz=");
  for(i=0;i<D;i++)
    printf("%d,",zz[i]);
  printf("\n");
  //    exit(1);
  //  
  for(i=0;i<K;i++){
    syn[i]=0;
    //#pragma omp parallel for
    for(j=0;j<D;j++){
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

  tt.t[0].n=1;
  tt.t[0].a=1;

  
  ff=inv(f,w);
  printpol(o2v(ff));
  printf("locater==========\n");
  //exit(1);
  r2=oadd(ff,tt);
  printpol(o2v(r2));
  printf(" h+x==============\n");
  //  exit(1);
  g1=osqrt(r2,w);
    printpol(o2v(g1));
  printf(" g1!=========\n");
  if(LT(g1).n==0 && LT(g1).a==0){
    printpol(o2v(w));
    printf(" badkey=========\n");
    goto label;
  }

  
  return w;
}

int main(int argc,char **argv){
  int i,j,k,l,c;
  unsigned long a,x,count=0;
  //  unsigned short cc[K]={0};
  unsigned short m[K],mm[T]={0},dd[K*D]={0};
  time_t timer;
  FILE *fp,*fq;

  unsigned short g2[7]={1,0,9,0,0,6,4};
  //  unsigned short s[K]={0}; //{4,12,7,8,11,13};
  unsigned short jj[T*2]={0};
  unsigned short ee[10]={1,2,3,4,5,6,7,8,9,10};
  short zz[D]={0};
  //  unsigned short zz[T]={10,97,114,105,97,98,108,101,32,80,111,108,121,110,111,109};
  int y,flg,o1=0;
  OP f={0},h={0},r={0},w={0},aa[8]={0},tt={0},ff={0};
  EX hh={0};
  vec v;
  unsigned short d=0;
  time_t t;
  unsigned short gg[K+1]={0};
  oterm rr={0};
  OP r1={0},r2={0},t1={0},t2={0},a1={0},b1={0},a2={0},b2={0};
  OP g1={0};

  
  
  srand(clock()+time(&t));
  printf("@");  
 label:
  
  for(i=0;i<K+1;i++)
    g[i]=0;
  ginit();
  
  
  w=setpol(g,K+1);
  oprintpol(w);
  
#pragma omp parallel for  
  for(i=0;i<D;i++){
    a=trace(w,i);
    if(a==0){
      printf("trace 0 @ %d\n",i);
      goto label;
      //  exit(1);
    }
  }
  printf("@");
  //keygen(g);
  key2(g);

  fq=fopen("H.key","rb");
  
  fread(dd,2,K*D,fq);
  #pragma omp parallel for
  for(i=0;i<D;i++){
  for(j=0;j<K;j++)
    mat[j][i]=dd[K*i+j];
    }
  
  
  for(j=0;j<D;j++){
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
  

  printf("すげ、オレもうイキそ・・・\n");

  uu=0;
  #pragma omp parallel for
  for(i=0;i<D;i++){
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


  fq=fopen("H.key","rb");
  
  fread(dd,2,K*D,fq);
  #pragma omp parallel for
  for(i=0;i<D;i++){
  for(j=0;j<K;j++)
    mat[j][i]=dd[K*i+j];
    }
  
  
  for(j=0;j<D;j++){
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

  
  while(1){

  belal:
    count=0;    

    //  exit(1);   
  for(i=0;i<D;i++)
    zz[i]=0;
  
  j=0;
  while(j<T){
    l=xor128()%D;
    //printf("l=%d\n",l);
    if(0==zz[l] && l>0){
      zz[l]=l;
      j++;
    }
  }
  /*
  for(j=0;j<D;j++){
    if(zz[j]>0)
      count++;
  }
  if(count<T){
    printf("error pattarn too few\n");
    goto belal;
  }
  */
  
  for(i=0;i<K;i++){
    syn[i]=0;
    //#pragma omp parallel for
    for(j=0;j<D;j++){
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
    mm[i]=r.t[i].a;
    if(i==0){
     printf("e=%d %d %s\n",r.t[i].a,r.t[i].n,"う");
    }else if(r.t[i].a==r.t[i].n){
      printf("e=%d %d %s\n",r.t[i].a,r.t[i].n,"お");
    }else if(r.t[i].a!=r.t[i].n){
	printpol(o2v(w));
	printf(" goppa polynomial==============\n");
	for(l=0;l<D;l++){
	  printf("%d,",zz[l]);
	  if(zz[l]>0)
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
      for(l=0;l<D;l++)
	printf("%d,",zz[l]);
      printf("\n");
       exit(1);
    }
  }
    for(i=0;i<D;i++){
    if(zz[i]>0)
      o1++;
  }
  printf("err=%dっ！！\n",o1);
  

  k=0;  
  printf("パターソンアルゴリズムを実行します。何か数字を入れてください。\n");
  //scanf("%d",&n);



  
    //    while(1){
       
    for(i=0;i<D;i++)
      zz[i]=0;
  
  
  j=0;
  while(j<T*2){
    l=xor128()%D;
    printf("l=%d\n",l);
    if(0==zz[l]){
      zz[l]=1;
      j++;
    }
  }
  

  
  printf("zz=");
  for(i=0;i<D;i++)
    printf("%d,",zz[i]);
  printf("\n");
  //    exit(1);
  //  
  for(i=0;i<K;i++){
    syn[i]=0;
    //#pragma omp parallel for
    for(j=0;j<D;j++){
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
    //exit(1);

  //  w=keyfinder();
    
    for(i=0;i<D;i++)
      zz[i]=0;
    
    
  j=0;
  while(j<T*2){
    l=xor128()%D;
    printf("l=%d\n",l);
    if(0==zz[l]){
      zz[l]=1;
      j++;
    }
  }
  

  
  printf("zz=");
  for(i=0;i<D;i++)
    printf("%d,",zz[i]);
  printf("\n");
  //    exit(1);
  //  
  for(i=0;i<K;i++){
    syn[i]=0;
    //#pragma omp parallel for
    for(j=0;j<D;j++){
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


  
  tt.t[0].n=1;
  tt.t[0].a=1;

  
  ff=inv(f,w);
  printpol(o2v(ff));
  printf("locater==========\n");
  //exit(1);
  r2=oadd(ff,tt);
  printpol(o2v(r2));
  printf(" h+x==============\n");
  //  exit(1);
  g1=osqrt(r2,w);
    printpol(o2v(g1));
  printf(" g1!=========\n");
  if(LT(g1).n==0 && LT(g1).a==0){
    printpol(o2v(w));
    printf(" badkey=========\n");
    goto label;
  }

  hh=xgcd(w,g1);

  ff=omod(omul(hh.v,g1),w);
  printpol(o2v(ff));
  printf(" beta!=========\n");
  if(deg(o2v(ff))!=K/2){
    printf("逆元が計算できない鍵です。\n");
    //  scanf("%d",&n);
    goto label;
  }



  
  pattarson(w,f);
  k++;
  if(k>1)
    goto label;
  }
  

  return 0;
}
