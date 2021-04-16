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

# 20210416

2倍のシンドロームの作り方がわからない。
翻訳しても具体例がないからわからない。
少なくとも次元を増やす前のシンドロームから2倍にしたときのシンドロームでは情報量が違っているので計算できないはず。
2つの符号が等価であることは、実際小さい符号から大きな符号を構成できることで確かめられる。
でもシンドロームはどう考えても等価じゃない。
シンドロームはどの位置にエラーがあるかわからない限り再構成できない。
パターソンも最初は何のことかわからなかった。
とりあえずセンドリエは放置。

BMおよびtエラー訂正分離可能なバイナリゴッパコードの最小距離は少なくともdmin = 2t 1であるため、パターソンアルゴリズムは、次数tのゴッパ多項式を持つゴッパコードのtエラーを訂正できます。 Berlekamp-Masseyアルゴリズムを使用して同じエラー訂正機能を実現する方法。これは、デフォルトでは、tエラー訂正を可能にするバイナリゴッパコードのプロパティを利用しません。

よく知られている等価性[MS78] Goppa（L、g（z））≡Goppa（L、g（z）2）（3.19）を使用すると、平方自由多項式g（z）に当てはまります。 Goppa（L、g（z）2）の2倍のサイズのパリティチェック行列に基づく次数2tのシンドローム多項式。 Berlekamp-Masseyアルゴリズムが一連のシンドローム方程式を設定することを思い出してください。そのうち、S1、。 。 。 、Stはデコーダーに認識されています。 g（z）2を法とするBMを使用すると、2tの既知のシンドローム方程式が生成されます。これにより、アルゴリズムはg（z）によって提供されるすべての固有情報を使用できます。 これにより、Berlekamp-Masseyアルゴリズムでtエラーを修正できます。これは、エラーロケーター多項式をPattersonアルゴリズムで奇数部分と偶数部分に分割することと本質的に同等であり、「新しい」キー方程式も生成されます。 

バイナリNiederreiterへの適用残りの問題は、バイナリの場合にBMとNiederreiterを使用してtエラーをデコードすることです。 Niederreiter暗号システムは、コードワードではなく暗号文としてシンドロームを使用するため、GMモジュロg（z）2を使用して2倍のサイズのシンドロームを計算するアプローチは使用できません。 パターソンアルゴリズムはg（z）を超える標準コードサイズを使用してすべてのエラーを修正できることがわかっているため、暗号化プロセスでもg（z）2を超えるコードに完全に切り替えると、コードサイズが2倍になります。

代わりに、Heyseが[HG13]で説明しているアプローチを使用できます。誤ったコードワードˆcに対応する長さn − kのシンドロームsは、方程式s = Scˆ = eHTを満たすことに注意してください。ここで、eはsをデコードして取得したいエラーベクトルです。ここで、sを標準サイズの計算されたmodolu g（z）のシンドロームとします。 sの前にk個のゼロを付けることにより、長さnの（0 | s）を取得します。次に、式を使用します。 3.19 g（z）2を法とするパリティチェック行列H2を計算します。 deg（g（z）2）= 2tであるため、結果のパリティチェック行列の次元は2（n-k）×nになります。 （0 | s）・H2 = s2を計算すると、長さ2（n − k）の新しいシンドロームが生成され、非バイナリの場合と同様に、次数2t −1のシンドローム多項式が生成されます。
g（z）とg（z）2に対するゴッパ符号の同等性、および（0 | s）とeが同じ剰余類に属するという事実により、s2は依然としてˆcに対応し、同じ解eを持つシンドロームです。 。ただし、s2はキー方程式に適切な長さを持ち、Berlekamp-Masseyが完全なエラーベクトルeをデコードできるようにします。

シンドロームであるニーダーライター暗号文を目的の長さのシンドロームに変換して、BMデコーダーを使用してバイナリコードのtエラー訂正を実現する方法については、セクション3.4.3ですでに説明しています。 2倍の長さのシンドロームs2は、暗号文sの前にゼロを付けて、ベクトル（0 | s）がゼロになるようにすることで得られます。 したがって、乗算ではsの最後の（n-k）ビットのみを考慮する必要があり、H2の最後の（n-k）列のみが必要です。 したがって、リスト4.7に示すように、実装では、計算時間とメモリ効率を向上させるために、H2の必要な部分のみを構築します。

翻訳ソフトのおかげでございます。

# 20210415

代わりに、Heyseが[HG13]で説明しているアプローチを使用できます。誤ったコードワードˆcに対応する長さn − kのシンドロームsは、方程式s = Scˆ = eHTを満たすことに注意してください。ここで、eはsをデコードして取得したいエラーベクトルです。ここで、sを標準サイズの計算されたmodolu g（z）のシンドロームとします。 sにk個のゼロを付加することにより、長さnの（0 | s）を取得します。次に、式3.19を使用します。  g（z）^ 2を法とするパリティチェック行列H ^ 2を計算します。 deg（g（z）^ 2）= 2tであるため、結果のパリティチェック行列の次元は2（n-k）×nになります。 （0 | s）・H2 = s2を計算すると、長さ2（n − k）の新しいシンドロームが生成され、非バイナリの場合と同様に、次数2t −1のシンドローム多項式が生成されます。 g（z）とg（z）^ 2、および（0 | s）とeが同じ剰余類に属するという事実、s2は依然としてˆcに対応し、
同じ解決策e。ただし、s2はキー方程式に適切な長さを持ち、Berlekamp-Masseyが完全なエラーベクトルeをデコードできるようにします。

シンドロームであるニーダーライター暗号文を目的の長さのシンドロームに変換して、BMデコーダーを使用してバイナリコードのtエラー訂正を実現する方法については、セクション3.4.3ですでに説明しています。 2倍の長さのシンドロームs2は、暗号文sの前にゼロを付けて、長さのベクトル（0 | s）を作成することによって取得されます。
nは、g（z）^ 2で計算されたパリティチェック行列H2と乗算されます。

H2はシークレットサポートを使用して構築されるため、暗号文にS -1を乗算することによるスクランブリングの反転は、s2の計算中に暗黙的に実行されます。 さらに、（0 | s）の最初のkビットはゼロです。 したがって、乗算ではsの最後の（n-k）ビットのみを考慮する必要があり、H2の最後の（n-k）列のみが必要です。 したがって、リスト4.7に示すように、実装では、計算時間とメモリ効率を向上させるために、H2の必要な部分のみを構築します。

Berlekamp-Masseyアルゴリズムが一連のシンドローム方程式を設定することを思い出してください。そのうち、S1、。 。 。 、Stはデコーダーに認識されています。 g（z）2を法とするBMを使用すると、2tの既知のシンドローム方程式が生成されます。これにより、アルゴリズムはg（z）によって提供されるすべての固有情報を使用できます。 これにより、Berlekamp-Masseyアルゴリズムでtエラーを修正できます。これは、エラーロケーター多項式をPattersonアルゴリズムで奇数部分と偶数部分に分割することと本質的に同等であり、「新しい」キー方程式も生成されます。

残りの問題は、バイナリの場合にBMとNiederreiterを使用してtエラーをデコードすることです。 Niederreiter暗号システムは、コードワードではなく暗号文としてシンドロームを使用するため、GMモジュロg（z）2を使用して2倍のサイズのシンドロームを計算するアプローチは使用できません。 パターソンアルゴリズムはg（z）を超える標準コードサイズを使用してすべてのエラーを修正できることがわかっているため、暗号化プロセスでもg（z）2を超えるコードに完全に切り替えると、コードサイズが2倍になります。

センドリエのトリックがわからん。
Goppa多項式を2乗してシンドロームを再入力すると同じコセットを使っているのでそのシンドロームも元のシンドロームと同じ性質を持つとかなんとか書いてあるけど
実際に計算してみても計算が合わないのだから、具体例で説明してないので何のことだかよくわからない。

シンドロームを再入力したらシンドロームをエラーベクトルに持つシンドロームが新しくできるだけなんじゃないかとか、
実際シンドロームを2乗してみても、Goppa多項式を2乗したときにできる列を再現できないしどうにもならない。
このままt/2エラー訂正で我慢しなければならないのか。

# 20210414

BM法、いろんな符号で64エラー訂正までできるようになった。(op.c:０の位置にエラーがあるとき、正しく訂正できないバグを確認)

途中でハマって、BM法とEEAが同じ符号を使ってシンドロームを計算しているとばかり思って、色々バグを探していたけど実は符号の構造が違うのだということに気づくのに１週間かかった。
せっかく今まで１年かけて作ってきたpattersonやEEAが使えなくなるのは残念だけど、暗号のためには我慢するしかない。
BMはシンドロームだけで訂正できるので、暗号化の意味がないのではと思ったら、確かにシンドロームだけで訂正しているけど
置換とスクランブル行列がここで効き目を発揮して暗号化になっているのだと専門家から答えを教えてもらった。
ついでにOAEPの方法も資料を送ってもらって、頂いてばかりで申し訳ないと思った。

あとはセンドリエのトリックを実装して、訂正可能なエラーの数を倍増させないといけない。

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

