# GoppaDecorder(万年素人の労作ｗ)

１．プログラム実行に当たって(op.c)　20200304,20200817,20210103

実行しようとすると異常終了するので（スタックオーバーフロー）、

ulimit -s unlimited

を必ず実行してください。

キーロガーが不安な方は、シングルタスクでネットに接続できないパソコンでビルドしてください。

開発日記はこちらに移動しました。

https://anang0g0.github.io/GoppaDecorder

依存関係のあるライブラリとかは一切ありません。
単体で動きます。

# 20210414

BM法、いろんな符号で３エラー訂正までできるようになった。

# 20210413

Binary Niederreiter暗号も残すところBerlekamp-Massey法の実装だけとなりました。
main関数内をきれいにしたつもり。

そのままクローンしてもmake nieでデモを動かすことができるので試してみてください。

# 20210411

もうすぐこのテーマが終わるから次の目標を物色してたんですが、あれもやろうコレもやろうと手を出して、
結局自分には同時に何かをするだけのフットワークがないんだと気がついてやはり浮気は良くないことだと反省している。

そんな中でも因数分解の方のバーレカンプマッシー法のC++で半分くらいrubyと同化されているファイルをかろうじて見つけて、これをどうするか迷っている。
cm法なんかもC++で書いたはずなのだが既に昔の環境が壊れて絶滅したらしく、　ネットにあったルビーファイルだけが生き残ったという歴史を感じさせる一日だった。

明日からは気分を入れ替えて、符号のバーレカンプマッシーをやることにします。

# 20210410

符号ばかりで飽きてきたので、ちょっと同種写像に浮気したい気分。
ていうか、こんなでかい鍵を公開できる場所って限られていると思う。

https://ja.wikipedia.org/wiki/%E8%B6%85%E7%89%B9%E7%95%B0%E5%90%8C%E7%A8%AE%E5%86%99%E5%83%8F%E3%83%87%E3%82%A3%E3%83%95%E3%82%A3%E3%83%BC%E3%83%BB%E3%83%98%E3%83%AB%E3%83%9E%E3%83%B3

# 20210408

下手に実装すると高速化は遅くなるのでやめた。

# 20210407

https://misawa.github.io/others/fast_kitamasa_method.html

https://tex2e.github.io/blog/crypto/ntt-polynomial-multiplication

高速kitamasa法なるものがあるらしいので、FFTやホーナー法などの細かいテクニックを駆使しながらバーレカンプ・マッシー法を実装する予定。

gprofで見る限り出現頻度の多いomulはFFTで高速化できるし、odivも高速化できそう。

# 20210406

http://210.47.10.86:8032/2015-3/2793.pdf

# 20210401

http://www.kurims.kyoto-u.ac.jp/~kyodo/kokyuroku/contents/pdf/1106-5.pdf

https://www.researchgate.net/publication/220538005_The_Berlekamp-Massey_Algorithm_revisited

https://www.researchgate.net/publication/285233058_Grobner_Bases_for_Decoding


# 20210331

ちょっとした思いつきだけど、バーレカンプを直接実装するのではなく、2変数のFeng−Rao復号法を1変数Goppaでやってみたらどうなるんだろう？

他にも設計距離じゃなくて最小距離復号をする方法もあるようなのでそれにしてみるとか。

https://ecse.monash.edu/staff/eviterbo/papers/elsep99.pdf

# マニュアル作成中

