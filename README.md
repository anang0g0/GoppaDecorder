# GoppaDecorder(万年素人の労作ｗ)

１．プログラム実行に当たって(op.c)　20200304,20200817,20210103

実行しようとすると異常終了するので（スタックオーバーフロー）、

ulimit -s unlimited

を必ず実行してください。

キーロガーが不安な方は、シングルタスクでネットに接続できないパソコンでビルドしてください。

開発日記はこちらに移動しました。

https://anang0g0.github.io/GoppaDecorder

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

