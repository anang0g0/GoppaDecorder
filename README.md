# GoppaDecorder(Goppie)

１．プログラム実行に当たって(oplib.c)　20200304

make

とやれば出来ます。
AMDの最適化コンパイラを使っている場合は、鍵生成の並列処理が可能になるので実行時間が速くなります。
その場合は

make amd

とすればコンパイルできます。

出力の第一段目はエラーの位置と値をユークリッドアルゴリズムで計算したもの、(decode関数)
第二は復号法であるパターソンアルゴリズムでバイナリエラーの位置を出力したものになります。(pattarson関数)

＃ハイライト

20200730

次世代暗号の世界標準が決定する第4ラウンドが始まりました。
効率性ではほかの候補より劣るものの、絶大な安全性を持つのがニーダーライター暗号です。
その点、他の候補はまだ作られて日も浅く、どのような安全性を持つのかはいまだ未確定です。
今後2年間をかけて、合計20候補の中から公開鍵暗号、電子署名、鍵交換などそれぞれの世界標準が決められる予定だそうです。

https://www.nist.gov/news-events/news/2020/07/nists-post-quantum-cryptography-program-enters-selection-round

20200729

ニーダーライターの兄弟である（実質的に同じ）McElieceがNISTの次世代暗号候補の最終選考に残ったようです。

https://csrc.nist.gov/projects/post-quantum-cryptography/round-3-submissions

20200726

もしPQCにこれが選ばれなかったら、いや寧ろその可能性が高いけど、これを秘密鍵にして使おうかと思う。
せめて最終候補には残って欲しい選択肢だ。
せっかく20年近くも考え続けて遂に作れたのだから、その努力を無駄にしたくない。
最悪、自分のためだけの使うことにする。
しかし本当に重要でかつ驚きなのだが、たった2週間で最後まで書くことが出来たことだ。
デバッグにも1ヶ月以上時間を費やしたし。

ところで、今回巨大整数を計算するC言語のプログラムを探していて思ったのは、誰かが使えるようにプログラムを書くということの大事さを知った気がする。
example.cのようなHowToプログラムを書くつもりだ。

20200724

このリポジトリは「GitHub Arctic Code Vault」に選ばれました。


202007123

indentで一層見やすく整形しました。


20200620（Code Based IBEが作りたい。またそれとは無関係な副産物）

１．昨日考えたのは、任意のベクトルをシンドロームとして持つような符号とエラーの対を求める計算でした。
これが何に使えるのかはまだ研究中です。
任意のシンドロームから、それに対応する複数の符号とエラーの対が計算できるなら、それはそれで面白い計算なので別に応用があるかもしれない。

仮に任意のシンドロームに対応する符号とエラーの対をP無理やり計算できたとしても、それはペアリングでもなければIBEでもないことが一晩明けて解りました。
こうしててアイデアがだめになる瞬間をいくつも経験しているので、どうってことはないですが、価値があると思ってた人には申し訳ない。

昨日はIDベースのPKIが作れるんじゃないかと勘違いしてたんですけど、結局何も理解していなかった。
PKIにどのような仕組みが必要なのか、なぜPKIが必要なのかも曖昧でした。
まだ勉強不足です。

エンジニアさんからは、解ってないことに気付くのも前進だといわれました。


２．IBEについてはまだ勉強中で理解してません。

まずペアリング写像を理解してない。
なのでここでは沈黙するしかないですが、符号を使ってできたらいいなと思っています。

３．符号に関する別の問題を考えてます。

例えば、シンドロームとそれに対応するエラーベクトルを公開して、そのシンドロームを生成できる符号を見つける問題が難しいかどうかという問題。

４．もし行列に符号を使ったとき、符号の列にランダムな列データを挿入した行列を公開鍵にする方法が考えられます。
これは符号の代数的構造を隠すための一つの方法として可能性があるのではと思っています。
（どの程度効果があるかはわかりませんが、これが一番まともなアイデアです）

この場合、シンドロームの計算は隣り合った列から干渉を受けないため、ダミーのデータとシンドロームが独立した（並列）状態で出力されます。
どの位置に符号の列があるかを識別することが難しければ、正しいシンドロームの値を取り出すことが出来ず、
復号できるのは本物の符号の列を知っている人だけという感じです。

もしかしたらこの方法でバイナリではなく、バイト誤りGoppa正符号でも安全な公開鍵暗号ができるかもしれない。
（バイト誤りGoppa符号は公開鍵から秘密鍵を計算することができてしまうので使えなかった。
ニーダーライターは当初一般化リードソロモン符号を公開鍵にしていたが、ソ連の研究者に解読されてしまったので、
バイナリ符号にしなければならなくなったという経緯がある。）


20200619（Code Based PKI）

今、一つのアルゴリズムのアイデアを試しています。
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


