# GoppaDecorder(Goppie)

20200620（Code Based IBEが作りたい。またそれとは無関係な副産物）

１．昨日考えたのは、任意のベクトルをシンドロームとして持つような符号とエラーの対を求める計算でした。
これが何に使えるのかはまだ研究中です。
任意のシンドロームから、それに対応する複数の符号とエラーの対が計算できるなら、それはそれで面白い計算なので別に応用があるかもしれない。

２．IBEについてはまだ勉強中で理解してません。
なのでここでは沈黙するしかないですが、できたらいいなと思っています。

３．また別の一方向性を考えてみます。
例えば、シンドロームとそれに対応するエラーベクトルを公開して、そのシンドロームを生成できる符号を見つける問題が難しいかどうか。

４．誰も格子暗号が長方形をした行列を公開鍵に持つ暗号だと言わないだけで、これは格子暗号の一種・・・なのかもしれない。

５．また別の方法として、もし行列に符号を使ったとき、符号の列にランダムな列データを挿入してランダム化した行列を公開鍵にする方法が考えられる。
これは符号の代数的構造を崩すための一つの方法として可能性がある。

この場合、符号の計算は、隣り合った列から干渉を受けないため、どの位置に符号の列があるか識別することが難しければ、
正しいシンドロームの値を計算することが出来ず、それができるのは正しい符号の列の位置を知っている人だけだからである。

もしかしたらこの方法でバイナリではなく、バイト誤りGoppa正符号でも安全な公開鍵暗号ができるかもしれない。

（バイト誤りGoppa符号は公開鍵から秘密鍵を計算することができてしまうので使えなかった。
ニーダーライターは当初一般化リードソロモン符号を公開鍵にしていたが、ソ連の研究者に解読されてしまったので、
バイナリ符号にしなければならなくなったという経緯がある。）


20200619（Code Based PKI）

今、一つのアルゴリズムのアイデアを試しています。これができれば符号でIDベース暗号が作れるかもしれません。
こういう思い付きは往々にして無価値であることが多いので、信じないでください。

今のままだと複数の組み合わせができる（１対１でない）可能性があるのでその場合どうなるかはよくわかりません。
例えば、現行のPoWにしてもハッシュ値が衝突している場合があるので、複数のデータの候補があること自体は大して問題にならない気がします。
ビットコインの場合、マイニングの作業は特定のフォーマットに合致するハッシュ値を探すという計算をスパコンでしますが、
符号で同じようなことをする場合、

任意のシンドロームに対応するエラーと符号の対を探すという計算にマイニングが使えるのではと思っています。

鍵を見つけた人には報酬が支払われる仕組みです。PoWによってメアドなどの任意のシンドロームから、符号とエラーの対ができたので
これはそのメールアドレスに紐づけされた鍵であることをエラーに関するZKIPを使って検証することが出来ます。

そんなことを考える前に普通にペアリングを理解しろっていう話もあるんですが、楕円曲線はPQCではないので却下です。
でも勉強します！

PoWに依存しない決定性アルゴリズムが見つかればいいのですが、鍵を見つける計算にPoWを使うのは邪道というか完全に間違っている気がしますね。
まだイメージを膨らませている状態なので理解してませんｗ。
そのうちどう間違っていることに気が付くと思います。
つまりやりたいこととしては、マイニングという計算を利用して任意のシンドロームに対応するエラーと符号の対を見つけたいというものです。
ブロックチェーンが鍵に当事者自身のものであることの信用を与えるための活躍させたい・・・。
今は確率的アルゴリズムなので計算量による力づくの計算が必要になりますが、決定性アルゴリズムができればPoWは必要なくなります。
暗号理論自体が計算量によって安全性を保障するようにできているので、今の時点だとPoW以外に解決方法がないように思えます。
また力づくの計算無しでPoWのような仕組みを実現する方法も考案中です。（PoSと呼ばれる方式が存在しますが、そのままでは使えません）

あるいはこの正直な計算が一方向性を持つなら、この問題を使った新しい暗号も作れるのかもしれません。（ここまでは符号の問題に基づいている）

で、

エンジニアさんの意見では、ビットコインのマネをしてはいけないという忠告を受けている。
理由は、PoWは環境に良くない、PoS（プルーフ　オブ　ステーク）のほうがいいというのです。
これは金持ちが得をするという新自由主義みたいなアイデアなのですが、
一方ではマイニングが努力を続けた者が得をするという感じなので、環境にいいという感じでしょうか。
この方式はイーサリアムを使ったピアコインで実現されているそうです。
他にもリップルコインという仮想通貨で使われる、
プルーフオブコンセンサスなるものもあるようで、今後色んな設計思想のシステムができてきそうです。
どちらにしてもこの分野はラットイヤーなので予測不可能ですけどねｗ

暗号の研究は大企業よりベンチャーのほうが圧倒的に有利な気がするんですけどどうなんでしょう。

発明は勢いと思い付き！ｗ


20200617

https://herumi.github.io/ango/

これを見て、楕円曲線を使わないでペアリングみたいなことがやってみたいと思うようになった。（ペアリングだけなら高校生でもできる）
ちなみにここに書いてある新しい暗号というのは、ほとんど全部ペアリング関数の応用であって、
その基礎となるECDLPが量子計算機に弱いことから比較的短命に終わる可能性がある。
私のやっていることが無駄にならなければいいのだが。
この際、符号さえ使っていれば何でもいいから次世代暗号になってほしい。

あと今ブロックチェーンの勉強中です。


20200606

エンジニアさんから指摘されたodegのバグを取って、次数の計算をodegに統一した。


20200531

ゼフ対数を出力するecole.cが動かないとのことなので、動くやつをアップロードしました。

20200601

keygen関数が動かない（エラーになる）ので、detを有効にしました。


20200517

更新してないのに見に来てくれてありがとう。

数学をやるので、暫くの間更新しません。ブロックチェーンの実装をするためです。
では、またいつか。


１．プログラム実行に当たって(oplib.c)　20200304

make

とやれば出来ます。
出力の第一段目はエラーの位置と値をユークリッドアルゴリズムで計算したもの、(decode関数)
第二は復号法であるパターソンアルゴリズムでバイナリエラーの位置を出力したものになります。(pattarson関数)


