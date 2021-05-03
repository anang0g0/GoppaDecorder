#include "oplib.c"

int main(void)
{
  int i,j=0,count=0;
  unsigned short zz[N] = {0},z1[N]={0};
  OP f = {0}, r = {0}, w = {0};
  vec v, x = {0};
  MTX R = {0},O={0};
  unsigned short s[K + 1] = {0};

  if (K > N)
    printf("configuration error! K is bigger than N\n");

  // （謎）
  memset(mat, 0, sizeof(mat));

  // 公開鍵を生成する(Berlekamp-Massey用)
  R = pk_gen();
  // エラーベクトルの初期化
  memset(zz, 0, sizeof(zz));
  //重みTのエラーベクトルを生成する
  mkerr(zz, T);
  // 暗号文の生成(s=eH)
  x = sin2(zz, R);
  // 復号化１(m'=sS^{-1})
  r = dec(x.x);
  v = o2v(r);
  for (i = 0; i < K; i++)
    s[i + 1] = v.x[i];

  // Berlekamp-Massey Algorithm
  f = bma(s, K);
  x = chen(f);
  // 平文の表示(m=m'P^{-1})
  ero2(x);
  wait();


  //公開鍵を生成する(G=SHP : Niederreiter , Patterson共用)
  O = pubkeygen(w);


  //decode開始
  while (1)
  {
    memset(z1, 0, sizeof(z1));
    //T重みエラーベクトルの生成
    mkerr(z1, T);
    //公開鍵を使ったシンドロームの計算(s=eG)
    v = sin2(z1,O);
    //シンドロームの復号(s'=sS^{-1})
    f = dec(v.x);
    //復号(m'=D(s'))
    r = decode(O.f, f);
    //エラー（平文）の表示(m=m'P^{-1})
    count = elo2(r);
    for (int i = 0; i < N; i++)
    {
      //検算
      if (z1[i] > 0)
        printf("error position= %d %d\n", i, z1[i]);
    }
    if (count < T)
    {
      printpol(o2v(w));
      printf(" == Goppa polynomial\n");
      exit(1);
    }
    j++;
    if (j == T)
      printf("err=%dっ！！\n", count);

    //if (j == 10000)
      break;
  }
  wait();
  
  O = pubkeygen(w);
  while (1)
  {

    //エラーベクトルを生成する
    memset(z1, 0, sizeof(z1));
    mkerr(z1, T * 2);
    //exit(1);

    //encryotion
    test(O.f, z1);

    //シンドロームを計算する
    f = synd(z1,K);
    //f=v2o(x);
    printpol(o2v(f));
    printf(" ==syndrome\n");

    //復号化の本体
    v = patterson(O.f, f);
    //エラー表示
    ero2(v);

    break;
  }

  return 0;
}