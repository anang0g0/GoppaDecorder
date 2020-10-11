# GoppaDecorder(Goppie)

１．プログラム実行に当たって(op.c)　20200304,20200817

https://clang.llvm.org/get_started.html

https://openmp.llvm.org/

これらを読んで実行環境を作ってください。

あるいは、./llvm.sh

https://qiita.com/kojiohta/items/fb6c307365d1db388acc
（正しくはこう）

を実行してclang-10をインストールするようにしてください。
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

出力の第一段目はエラーの位置と値をユークリッドアルゴリズムで計算したもの、(decode関数)
第二は復号法であるパターソンアルゴリズムでバイナリエラーの位置を出力したものになります。(pattarson関数)

20201011

エラーの数のカウント方法を修正しました。

まあ一個でも間違ってたら動かないプログラムなので、全部悪いとは思いませんでしたが。

20201009

実装が悪いので遅いですが、本来はRSAより復号速度が速いです。 高速化と最適化が今後の課題ですが、ここにあるのは適当に書いたものなので、そのうち書き直します。

https://hal.inria.fr/file/index/docid/607772/filename/69.pdf

実装が終わったと言えばそれまでなんですが、上の論文が面白そうなのでまたやってみたくなりました。

とりあえずグローバル変数は使わないようにしたいと思います。

20200903

https://anang0g0.github.io/GoppaDecorder/

プロジェクトのホームページを作りました。
