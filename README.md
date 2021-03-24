# GoppaDecorder(万年素人の労作ｗ)

１．プログラム実行に当たって(op.c)　20200304,20200817,20210103

実行しようとすると異常終了するので（スタックオーバーフロー）、

ulimit -s unlimited

を必ず実行してください。

キーロガーが不安な方は、シングルタスクでネットに接続できないパソコンでビルドしてください。


https://apt.llvm.org/

https://openmp.llvm.org/

これらを読んで実行環境を作ってください。

clang-10推奨。
gccでも動くようになりました。(20210319)

cd src/

make

とやれば出来ます。

AMD用の最適化オプションznver2を使用。

参考文献：

https://arxiv.org/pdf/1907.12754.pdf
ホワイトペーパー

https://www.hyperelliptic.org/tanja/students/m_marcus/whitepaper.pdf

https://surface.syr.edu/cgi/viewcontent.cgi?article=1846&context=honors_capstone

https://klevas.mif.vu.lt/~skersys/vsd/crypto_on_codes/goppamceliece.pdf

出力の第一段目はエラーの位置と値をユークリッドアルゴリズムで計算したもの、(decode関数)
第二は復号法であるパターソンアルゴリズムでバイナリエラーの位置を出力したものになります。(pattarson関数)

実装に関する参考資料

HOW SAGE HELPS TO IMPLEMENT　GOPPA CODES AND THE　McELIECE PUBLIC KEY CRYPTO SYSTEM

Coding Theory-Based Cryptography:McEliece Cryptosystems in Sage

Testing Irreducibility of Trinomials over GF(2) 
https://digitalcommons.iwu.edu/cgi/viewcontent.cgi?article=1013&context=math_honproj

# 20210324

Niederreiterのバイナリ公開鍵を生成し、それをさらにshort int型にパッキングすることに成功した。

あとはこの鍵で暗号化復号化できれば完成！

# 20210323

なんだかシステムを再起動したら、勝手にブートイメージが書き換わってカーネルが合わなくてXが起動しないのでUbuntuから起動してる。
陰謀？

sagemath用のコードにバグがあった。
いろいろいじっているから気づかなかったけど、どうしてsagemath用のコードジェネレータだけバグっていたのか謎。

# 20210322

取り敢えず10,000回とか回しても止まらないんで安定してるのかなとは思うけどどうなんでしょう？
１０００回回すように出来ているので、ベンチマークの代わりに使ってみてくださいｗ。

ちなみに私の環境ではgcc-10が一番早くて３分１１秒位でした。（clangは４分３３秒。本当にllvmを使っているのだろうかｗ）
  
 time ./a.out |grep irreducible
 
で実行。
中身は、完全にランダムではない（予めふるいにかけてある）ものの、任意の多項式を生成して、
それが既約かどうかを判定して出力するという動作を１０００回計算します。
こうして部分的に出力するだけでも、止まってないのがわかりやすいのでそうしてます。

すべてを出力すると、Ubuntu20.04が不安定になること（バグ？）があるので出力は控えめに。
ちなみにDebianでも画面がフリーズしたようになります。
でも出力を制限するときちんと動いているので、アルゴリズムのバグではなさそうなんですがどうなんでしょう・・・。

# 20210321

まだきちんと検証してませんが一応バグ修正に対応して動いているように見えます。
途中でシステムが壊れるなど、時間の空費がありましたがすべて公開したあとなので困ってません。
こういう場合、結局開発環境がLinuxしかないということなのでLinux以外で動かせないという事になります。
この辺なんとか改善したいです。

仕様なのか、gccでコンパイルするのは死ぬほど遅いのでclangでコンパイルすることを強くおすすめする。
それとclangはプログラムの記述とかメモリがタイトなのか、ちょっとでも使わない配列操作とか書いてるだけでも全然動作が変わってしまう。
原因は復号に使うdecode関数だった。
いつの間にか書き換えてしまったようで、動いているように見えて動いてないｗ。
０の位置にエラーがあっても正しく復号できるようになった。

# 20210320

clang-11で動かないバグを修正中。
gcc-10で動作を確認。

# 20210319

GF(8192)上で、既約多項式を生成できるようになった。

拡大帯でも同じアルゴリズムが使えるというのは驚きだった。

こういう規則性は勘で簡単にわかる人もいると思うけどすごく大変だった。

# 20210318

拡大体において既約多項式を計算するben_or関数と、opowmod関数を作成して、既約なGoppa多項式のみ生成するように改良した。

次数が上がると桁溢れが起きるというopowmodのバグに気づかなかったら、この関数の実装は完成しなかっただろう。

# 20210317

バイナリ係数を持つ多項式の既約性判定テスト、Ben-Orのアルゴリズムを実装しました。
バグがないか確認中ですがとりあえず公開します。

# 20210316（変更点）

自分でも何やってるんだかわからなくなってきたのでファイルを整理した。

ギットをいじっているうちに、プルもプッシュもできなくなってセルフファック（マージ）したのをサルベージしたｗ

本体（op.c）で符号生成関数mkgで高速に公開鍵の生成を行うことができるようになった。
gccでも動きます。

符号生成の部分を関数として独立させた。
これで符号生成の関数は、det,deta,mkgと３種類になった。（遅い、早くて動かない、早いしGCCでも動く、の順）

Ryzen 7 2700Xで鍵生成から暗号文の復号まで２秒位。（符号長は8192）
最初４０秒もかかったのが嘘みたいな速さにｗ

エラー表示関数も独立させて、main関数内を短くした。（見やすくはないｗ）

そしてパターソン復号アルゴリズムに欠陥があることを思い出した。（完璧を目指すなら直したほうがよい）

それは、「偶数次の項しか持たない多項式の復号に失敗する」ということ。

（これは半分仕様のようなものだけど、具体例が解けないことで思い出した。というのも普通は既約多項式のみを鍵多項式に使うからだ。
じゃあちゃんと既約性判定してるのかと言われるとそうでもないｗ。なので、多分修正する。）

これだけやってまだ完璧でないところがあるというのは、単に根性だけではバグをなくすことは出来ないということだ。
ていうかやってるうちに忘れるんだけども。

あとバイナリ正則行列を生成する関数の欠陥が明らかになったので、ランダムな正則行列が作れるように修正。


# 20210309

LICENSEを追加しました。
GPLライセンスです。

# 20210308

69.pdfを参考に、パリティ検査行列を行列に分解できるという性質を使って今まで10秒かかっていた処理を2秒で終わらせることができるようになりました。

リスト復号を実装に取り入れることを検討しています。

# 20210307

op2.cのbibun関数を並列化し、更に公開鍵も行列の掛け算で並列化することにより、Ryzen7 2700Xで鍵生成から暗号化復号化一回に付き5秒位になった。
今まで10秒を切れなかったので2倍の高速化。

# 20210303

ネット禁止も3週間で終わり、数学の勉強がおろそかになるりスクが出ていますが、手計算で全てを確認するのは限界なので
自分で作ったソフトを使って：同じシンドロームを持つような2つの異なる符号は存在するか？：という問題を解いています。
謎がわかったらアップロードします。

実験の結果、存在するということがわかったので、それぞれがどういう関係にあるのか、これも実験で確かめます。

（ユークリッドアルゴリズムとグレブナ基底の関係とかも）

sagemathの使い方を覚えるのが面倒なので自分で作ったのですが、頭の体操になっていい感じです。

何歳になっても学ぶということは楽しいものです。

# 20210111

PentiumIIIで動作確認。
カギ生成から復号まで約6分。
遅い・・・。

# 20210105

Niederreiter暗号を作るために使うもののはず。

https://ja.wikipedia.org/wiki/%E3%83%9E%E3%83%83%E3%82%AF%E3%82%A8%E3%83%AA%E3%82%B9%E6%9A%97%E5%8F%B7
これとか。

# 20210103

2020年の開発日記をdiary2020.txtに移しました。

# 20201220

実装が悪いので遅いですが、本来はRSAより復号速度が速いです。
高速化と最適化が今後の課題ですが、ここにあるのは適当に書いたものなので、そのうち書き直します。

https://hal.inria.fr/file/index/docid/607772/filename/69.pdf

実装が終わったと言えばそれまでなんですが、上の論文が面白そうなのでまたやってみたくなりました。

とりあえずグローバル変数は使わないようにしたいと思います。


