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

https://klevas.mif.vu.lt/~skersys/vsd/crypto_on_codes/goppamceliece.pdf

出力の第一段目はエラーの位置と値をユークリッドアルゴリズムで計算したもの、(decode関数)
第二は復号法であるパターソンアルゴリズムでバイナリエラーの位置を出力したものになります。(pattarson関数)

実装に関する参考資料（打倒ペアリング！ｗ）

HOW SAGE HELPS TO IMPLEMENT　GOPPA CODES AND THE　McELIECE PUBLIC KEY CRYPTO SYSTEM

Coding Theor Coding Theory-Based Cr y-Based Cryptopraphy: McEliece Cr aphy: McEliece Cryptosystems in osystems in
Sage 

Development and Evaluation of a Code-based　Cryptography Library for Constrained Devices

Fast Construction of Irreducible Polynomials over Finite Fields

An Application Specific Instruction Set Processor　(ASIP) for the Niederreiter Cryptosystem

PROBABILISTIC ALGORITII4S IN F INITE FIELDS

# 20201110

Rustなんかに手を出していたので何もしてません
osqrtにバグがあります。直すのは明日以降です。

バグの取り方のメモ（実装は明日）：すべての項の次数が偶数の時は無条件ですべての項の次数を半分にした多項式を返す。

追加の資料が大量に見つかったので、それを総動員して実装します。

# 20201109

バグが取れた。
今までずっと数のチェックしかしてなくて、出力される値のチェックをしていなかった。
そのために数だけ合ってて値がメチャクチャなものが含まれていることに今日気がついた。
つまり答え合わせの方法のバグだ。

で、真犯人を探すためにgcdを返す関数を追求するも、どちらも欠陥があり大騒ぎ。
終了条件を知らずに盲滅法関数を探して、最もシンプルな方法に正解が合った。
わずか5,6行のシンプルなコード。

これで漸く安心して眠れる。
私って正社員並みに働いてますよねｗ

# 20201108

kuboonさんの指示通りに、ompを外してみたら今まで2000回計算するのに50秒かかっていた計算がわずか6秒になった。
頻繁に呼び出す関数の中でompは使うなといういい教訓になりました。
今までo2vが悪者だと言われてきたけど、o2vの中でompを使っていたからそう見えただけであって、真犯人はompだったという落ちです

さすがプロのアドバイスは効果があるなあ。
これで実用レベルに躍進しました。

# 20201107

kuboon氏の手直しを受けていたほうがmainブランチであることを忘れて、古いファイルをアップロードしていたことに気づいたので直しました。

mainは主に品質重視の設計で行く方針ですが、同時に最新のブランチでもあります。
安定版が欲しい人は、masterブランチを指定してクローンしてください。

Goppa符号の訂正より、多項式の確率的多項式時間既約性判定アルゴリズムに使えるのではないかと期待しています。

# 20201021

バグだと思っていたのが仕様だった。
goppa多項式はバイナリ符号の場合は既約多項式でないと完全には動作しないのだという制限があるらしい。
ということで多項式の既約性判定アルゴリズムを実装しなければならない。
実を言うと以前にben-orのアルゴリズムを実装しようとしたことがあったのだが、次数が二重指数関数的に増えるので実用的でなかった。

# 20201011

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
