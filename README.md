# GoppaDecorder
耐量子計算機暗号のコアは、古典的Goppa符号の復号法にかかっているので、ここではその実装に役立つものを作ろうと思っています。
現在のところ、2の拡大体に関する復号は例外処理以外の実装で、バグがあります。
このコードを実装するのに使った書籍は、Oliver PrezelのError-Correcting Codes and Finite Fieldsです。
実際に暗号を作るとなると、バイナリバージョンが必要なのですが、まだアルゴリズムを理解してないのでパターソンアルゴリズムを勉強中です。
このコードの最終目的は軍事レベルの暗号を作ることで、Niederreiter暗号を目指しています。鍵はでかいです。
毎月たくさんの新型が生まれている中で、なぜ改良版を使わないのかという人もいるかもしれませんが、
一番古いオーソドックスな技術が一番安全だし使えると思ってやっています。動かすときはLinuxでどうぞ。
コアダンプしないように作ってあるつもりです。（何らかの標準出力がある）
またブロックチェーン技術のためにネット上にあった自作でないSHA3を使い、電子署名モジュールは作るつもりです。
暗号だったらopensslがあるからいらないという人もいるかもしれないですが、Niederreiterは入ってません。GitHubも探しましたが誰も作ってないようです。
だったら私が、と重い腰をあげました。

実装は汚いコードですが、ポインタやオブジェクト指向を知らないので初心者レベルのコードです。
JavaScriptなんかにも直接移植できるのではないでしょうか。


20191218

GF(4096)上定義されたバイナリGoppa符号を生成できるようになった。この計算には14分もかかるので今後何か別の計算方法を考えないといけない。(oplib.cpp)
因みに、QC-MDPCなんで邪道だと思っているので、オリジナルの古典的Goppa符号を使っている。

同時に、LU分解法にヒントを得た可逆スクランブル行列を生成できるようになった。(lu.c)

公開鍵のパラメーターは、[n,k,t]=[4096,2040,170]である。

20191221

GF4096において、型をunsigned shortにして、バイナリ生成行列を出力させる鍵生成まで完成。(oplib.cpp)

20191226

開発メモ。誤りロケータだけは実装完了。バイナリバージョンの場合は誤りの位置を決定するだけで済むのでこれで完成。

既知のバグ：誤りの値を計算するときに、0になる場合がある。これは誤りロケータと、誤り値関数にまだ最小公倍数、つまり
1次式が残されている証拠で、この点を解決するためにユークリッドアルゴリズムに多少の改良を加える必要がある。この点については
来年に目標にしたい。
