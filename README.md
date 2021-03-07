# GoppaDecorder(万年素人の労作ｗ)

１．プログラム実行に当たって(op.c)　20200304,20200817,20210103

実行しようとすると異常終了するので（スタックオーバーフロー）、

ulimit -s unlimited

を必ず実行してください。

キーロガーが不安な方は、シングルタスクでネットに接続できないパソコンでビルドしてください。


https://apt.llvm.org/

https://openmp.llvm.org/

これらを読んで実行環境を作ってください。

clang-10をインストールするようにしてください。

clangのバージョンに応じてMakefileを書き換えてください。

cd src/

make

とやれば出来ます。

llvmのclangを使って並列処理をします。（環境を整えるのが難しいですが）

op.c内のmain関数の中のdetをdetaに書き換えました。

gccを使いたい場合は、make gccとすること。
実行環境はgcc-9.2.0。
AMD用の最適化オプションznver2を使用。
gccの場合、パリティチェック生成の並列化に失敗することがあります。

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

gccだと並列化に失敗しますが、原因はわかりません。

# 20210307

op2.cのbibun関数を並列化し、更に公開鍵も行列の掛け算で並列化することにより、Ryzen7 2700Xで、鍵生成から暗号化復号化一回に付き5秒位になった。
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


