
unsigned short tr[N] = {0};
unsigned short ta[N] = {0};

void det2(int i, unsigned short g[])
{
  OP f[16] = {0}, h[16] = {0}, w, u[16] = {0};
  unsigned short cc[K + 1] = {0}, d[2] = {
                                      0};
  int j, a, b, k, t1, l = 0, flg = 0, id;
  oterm t[16] = {0};
  vec e[16] = {0};
  OP ww[16] = {0};

  memcpy(cc, g, sizeof(cc));

  k = cc[K];
  w = setpol(g, K + 1);

  //  omp_set_num_threads(8);
  id = omp_get_thread_num();

  // h[id] = x+i
  if (i == 0)
  {
    h[id].t[0].a = 1;
    h[id].t[0].n = 1;
  }
  else
  {
    h[id].t[0].a = i;
    h[id].t[1].a = 1;
    h[id].t[1].n = 1;
  }

  t[id].n = 0;

  f[id] = setpol(cc, K + 1);

  cc[K] = k ^ ta[i];
  //tr[i];
  f[id] = setpol(cc, K + 1);

  //f.t[0].a=k^ta[i]; //cc[K];

  ww[id] = odiv(f[id], h[id]);

  //b = oinv (a);
  t[id].a = gf[tr[i]];
  u[id] = oterml(ww[id], t[id]);
  e[id] = o2v(u[id]);

  memcpy(mat[i], e[id].x, sizeof(mat[i]));
}

//パリティチェック行列を生成する
int deta(unsigned short g[])
{
  int i, j, a, b, k, t1, l = 0, flg = 0, id;

  //
  //
#pragma omp parallel num_threads(8)
  {
#pragma omp for schedule(static)
    for (i = 0; i < D; i++)
    {
      det2(i, g);
    }
  }
  for (j = 0; j < D; j++)
  {
    flg = 0;
    for (i = 0; i < K; i++)
    {
      printf("%d,", mat[i][j]);
      if (mat[j][i] > 0)
        flg = 1;
    }
    printf("\n");
    if (flg == 0)
    {
      printf("0 is %d\n", j);
      //exit(1);
      return -1;
    }
  }
  printf("end2\n");
  // exit(1);
  return 0;
}

unsigned short *base;

//パリティチェック行列を生成する
void det(unsigned short g[])
{
  OP f, h = {0}, w, u;
  unsigned short cc[K + 1] = {0}, d[2] = {0}, pp[20][K] = {0};
  int i, j, a, b, k, t1, l = 0, flg = 0, count = 0;
  oterm t = {0};
  vec e;

  memcpy(cc, g, sizeof(cc));
  /*
     for (i = 0; i < K + 1; i++)
     {
     cc[i] = g[i];
     printf ("%d,", g[i]);
     }
   */
  //printf ("\n");
  //  exit(1);
  //    cc[i]=g[i];
  k = cc[K];
  w = setpol(g, K + 1);

  OP ww = {0};

  h.t[0].n = 0;
  h.t[1].a = 1;
  h.t[1].n = 1;
  t.n = 0;
  t1 = 2 * T;
  // #pragma omp parallel for
  /*
     unsigned short tr[N];
     unsigned short ta[N];
     for(i=0;i<N;i++){
     ta[i] = trace (w, i);
     if(ta[i]==0){
     printf("%d %d\n",i,ta[i]);
     exit(1);
     }   
     tr[i] = oinv (ta[i]);    
     }
   */

  //
  f = setpol(cc, K + 1);

  for (i = 0; i < D; i++)
  {

    a = trace(w, i);
    // cc[K] = k;

    cc[K] = k ^ a;
    //tr[i];
    f = setpol(cc, K + 1);

    //f.t[0].a=k^ta[i]; //cc[K];
    h.t[0].a = i;

    ww = odiv(f, h);

    b = oinv(a);
    t.a = gf[b];

    u = oterml(ww, t);
    e = o2v(u);

    // #pragma omp parallel for
    //for (j = 0; j < K; j++)
    //mat[i][j]= e.x[j];
    memcpy(mat[i], e.x, sizeof(mat[i]));
  }

  for (j = 0; j < D; j++)
  {
    flg = 0;
    for (i = 0; i < K; i++)
    {
      printf("%d,", mat[i][j]);
      if (mat[j][i] > 0)
        flg = 1;
    }
    printf("\n");
    if (flg == 0)
    {
      printf("0 is %d\n", j);
      //exit(1);
    }
  }
  //exit(1);
}
