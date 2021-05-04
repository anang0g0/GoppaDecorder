# GoppaDecorder(万年素人の労作ｗ)

１．プログラム実行に当たって(op.c)　20191218（開始），20200304,20200817,20210103,20210419（機能が揃う）

実行しようとすると異常終了するので（スタックオーバーフロー）、

ulimit -s unlimited

を必ず実行してください。

開発日記はこちらに移動しました。

https://anang0g0.github.io/

依存関係のあるライブラリとかは一切ありません。
単体で動きます。

コードのメンテナンス作業に移行します。（20210419）  


たくさんのアドバイスをいただいた産業技術総合研究所の古原和邦様には、特別な感謝の気持とお礼を申し上げる。

---


# マニュアル作成中

~~今の所、EEA(拡張ユークリッドアルゴリズム)で安全でないという証拠はないそうなので,取り敢えずEEAで復号できるようになっています。~~  
patterson復号にはエラーロケーターの計算に対するタイミング攻撃などの攻撃があるので使わないほうがいいです。  
EEAにもXGCDを計算するときの電力解析があるようなので、BMが実装の主流になっているらしいです。  

暗号化においてOAEP実装など細かい修正点は残っていますが、取り敢えずバイナリ公開鍵から復号までワンセットで揃っているので、以下のコードを参考に使ってみてください。  
一応BMAなんかも実装中なのですが、多項式ライブラリの出来が悪くてシンドロームだけで計算できるBMAのほうがEEAに比べて２倍くらい早いです。  
まだバグが取り切れてませんが、サンプルコードを挙げておきます。

サンプルコード（berlekamp.c）

```c

int main(void)
{
    int i;
    unsigned short zz[N] = {0};
    OP f = {0}, r = {0}, w = {0};
    vec v, x = {0};
    MTX R = {0};
    unsigned short s[K + 1] = {0};

    if (K > N)
        printf("configuration error! K is bigger than N\n");

    // （謎）
    memset(mat, 0, sizeof(mat));

    // 公開鍵を生成する(Niederreiterとは異なる)
      R=pk_gen();
    // エラーベクトルの初期化
      memset(zz, 0, sizeof(zz));
    //重みTのエラーベクトルを生成する
      mkerr(zz, T);
    // 暗号文の生成(s=eH)
      x=sin2(zz,R);
    // 復号化１(m'=sS^{-1})
      r=dec(x.x);
      v=o2v(r);
    for (i = 0; i < K; i++)
      s[i + 1] = v.x[i];

    // Berlekamp-Massey Algorithm
      f = bma(s, K);
      x=chen(f);
    // 平文の表示(m=m'P^{-1})
      ero2(x);

retuen 0;
}

```

# 設定ファイルと定義体の設定  
global.h：符号のパラメータを決めます。  
chash.c ：定義体を指定します。  
ecole.c ：定義体の中身を作ります。(ecole normal basis lol)  

[参考サイト] (https://www.cayrel.net/?Implementation-of-Goppa-codes&fbclid=IwAR2XMRqZwjkULDQNH9Ij6pZP64lWI_rdgduiaP63u8M_O9rCuDlIC-I9ncU
)

今のままだとまだ暗号とは言えなくて、単に暗号に使える機能が全部揃ったという段階なので、まだまだ手を加えることがある。
それ以前にプログラムとしてダメ。
グローバル変数を公衆便所のように使っているｗ．
でも必要な機能はほとんど実装してあるので、完成の目途はたったと言える。
パターソンで奇数列を抜き出して公開鍵にするという方法を試したら鍵が小さくなる気がする。
パターソンで使っている検査行列と、BMで使う検査行列は若干の違いがあって、BMのほうが単純だ。
何が違うかというと、パターソンではGoppa多項式の係数行列が作用しているけど、BMではそれが単位行列になっているところだ。
でも論文にはそう書いてあるんだし、それが正しいのだと思うしかない。
オリジナリティが何もないなｗ。
次何しようかな。

# 20210504

アナウンスしなかったけど今日も一日プログラムをいじってました。
逆行列の計算や掛け算を任意次元の製法行列でできるようにした。
もともｔMTXには行と列の値を指定できるようにしてあるので、それを参照すればかなり汎用的な行列演算ができる。
バグ取りとかも。  
is_reg関数はバイナリ行列の正則性を判定して、正則ならその行列の逆行列を返すというのをMTX型のポインタ渡しとして実現しています。  
ここで生まれて初めてアロー演算子を使ったという快挙を達成ｗ  
ポインタは苦手だしまさかここで使う必要が出てくるとは思わなかった。
作りたいものがあるうちは実力なんか関係ない！ｗ

できれば多項式や行列の計算にFFTを入れたいけど、要素数８０００くらいで果たして効果があるのかどうか。
難しそうだし・・・。

# 20210503

バイナリ行列が正則かどうかを判定し、正則ならその逆行列を返す関数を追加した。  
分割コンパイルしようとして気づいたんですが、Pattersonだけ暗号化に対応してません。  
ファイルは使えるように分割し始めましたがまだまだ完成は先です。  
ようやくメンテナンスっぽくなってきた。  

取り敢えず今日の作業は終わり。
まだclangのバグ取りが出来ないまま。
あとはmakeS関数をまともな関数に置き換えること。

Ubuntuの悪口を言ったけど、原因はカーネルとグラフィックドライバの相性だった。  
nvidia-smiが実行できないので、nvidia-driverをインストールしたら嘘のようにフリーズしなくなった。  
これでようやく開発機になれる。

# 20210502

RS符号以外にも偶数列を削除できるとのことなので、頑張ってその方法を考えています。  
先に暗号化を実装したほうがいい感じがするので、2倍サイズのシンドロームは当面凍結。  
あと、暗号化してコードが複雑になったので、暗号化する前の普通のデコーダを偲ぶためにop_old.cを追加しました。  
そんなにいっぱいファイルを使わなくても、GitHubに今までの履歴が全部あるのだから気にする必要もないのにそうしないと安心できない。
GitHubの履歴はまさにプログラムの成長の記録だ。

上のレポートに攻撃について説明があった。
パターソンの何が問題かというとロケーターを計算するときの時間らしい。
今のままで考えればchien探索で一定時間だから特に問題がないように見えるけどどうなんだろう。  
全体的に実装の論文を見ると何故かBM法が主流なので、それぞれの復号法に合わせて3つのファイルに分割。  
分割コンパイル必要性を感じる。  
berlekamp.cはclangでコンパイルするとエラーになる。
なにかバグがあると思うのでそのうち直す。  
リヨン大学のレポートにあるように、BMの場合は2倍サイズの検査行列を使うことにして我慢することにする。  
公開の方法はリヨン大学のマネ。  
自分の実装はランダムエラーを内部で発生させて、符号もその都度生成して符号化、復号化している。  
~~出力を見ればなんだかわかると思う。~~  
リヨン大のコードはきれいだなー。
実装のレベルもすごく高いし、警告も殆どないし。  
有限体の計算は好みによると思う。
自分の場合は　static const　かなんかでテーブル参照するナイーブな方法。
メモリ無駄に使ってる。

よくわからないのは同じ符号でも異なるフォーマットがあるということだ。
少なくとも2つのフォーマットがある。
この形式にどんな意味があるのかわからないけど、実装する上では復号アルゴリズムに影響を与えるので大きな問題だ。
パターソンとEEAでは同じ符号が使えるけど、BMAでは使えない。
どんな関係があるのかはこれから調べることにする。
リヨン大のレポートを見ながらやったのでそういう証拠はある。

プログラムの設計で迷いがある。
システムパラメータで全体の性能を決定するか、ユーザに自由度を持たせるために関数に値を渡すべきかどうか。
前者は間違いが少ないけど、後者は使い方が複雑になる。

それにしてもウブンツは駄目なOSだ。
ちょっと負荷がかかるとすぐフリーズするので、安心して計算ができない。
これは実験用途で使う上で致命的な欠陥だ。
こんなに不安定なLinuxでも開発に使っている人はいるのだろうか？  
Debianのほうがいくらかマシ。
実績あるし。

# 20210501

追記：センドリエは使えるようにならない。  
シンドロームを計算するのは送信者なので、エラーがどの位置にあるかを確認できます。
しかし、K/2サイズの公開鍵から2倍の大きさのシンドロームを計算するためには、
公開鍵から生成される暗号化されたシンドロームを一旦復号してから2倍にしないといけないため、同じくらい不自然です。
とりあえず動いているのでこのまま残しておきます。(fals.c)  
つまり送信者と受信者のやることがごっちゃになっている（頭を整理しないと）  
RS符号にしないとだめというおかしな感じが残っている。  
RSバージョンならバイナリレベルで暗号化されているにもかかわらず、なぜか2倍サイズのシンドロームを生成復号できます。(op.c)
それでも2倍化しなければ、暗号化されたシンドロームをもとに戻して訂正ができる。

行列を扱うときのデータ型を準備しておいたMTXに統一。  
今までものすごい量のスタックを消費していたけど、MAT型をなくすことで使用するメモリの量が減ったはず。  


ちょっとおかしなことに気づきました。  
そんなわけでファイルを古いバージョンに戻します。  
シンドロームを2倍にするなんてことはできるのだろうか？
そんなわけでシンドローム2倍のトリックは、今の方法では不可能だということがわかりました。
つまりトリックじゃなくてフェイクですｗ  
鍵サイズを半分にできる例外？として、ちょっと考えたら別の方法があることに気が付きました。
まずパリティ検査行列から1/g(x)を取り除いて、Vandermonde行列に直します。
こうすることで、検査行列を単純化して奇数次の列から偶数次の列を作ることができ、シンドロームを二倍しても正しくエラー訂正できるようになりました。
あまり期待してなかったけどうまく行ってよかった。
シンドローム2倍の方法がフェイクでないかどうかはもう少し考えてみます。
おとなしく最初から普通のサイズの符号を使っていれば、こんなに苦労はしなかったのに。('A`)

専門家さんのアドバイスによると、仮に検査行列がRS符号だったとしてそれで解読できるとしたら面白い論文になるということです。
つまりバイナリ符号にすれば無敵らしいです。（まだ信じてないｗ）  
とりあえず公開鍵にも暗号化かけて訂正できることを確認しました。  

> >  SHPのHがRS符号になると思うのですが、公開鍵SHPからSとPを見つけられる可能性はないのでしょうか？

可能性は無いわけではなく、実際に発見できれば非常に面白い論文になります。

>ただ、より正確にはHはRSというよりGeneralized RSや Alternant Code やさらに正確には当然ながらGoppa Code のHで、皆さんそのことは織り込み済みで解読を試みられているので容易ではないと思います。だからこそ、発見できれば非常に面白い論文になります。

「偶数列を省略するのはこの分野の常識」とまで言われてしまいましたが、一体その常識が書かれてある論文は存在するのでしょうか？


