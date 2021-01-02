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

Coding Theory-Based Cryptography:McEliece Cryptosystems in Sage

Development and Evaluation of a Code-based　Cryptography Library for Constrained Devices

Fast Construction of Irreducible Polynomials over Finite Fields

An Application Specific Instruction Set Processor　(ASIP) for the Niederreiter Cryptosystem

PROBABILISTIC ALGORITII4S IN F INITE FIELDS

https://eprint.iacr.org/2015/1050.pdf

# 20201220

ちょっと遅かったですが、参考文献をアップロードしました。


