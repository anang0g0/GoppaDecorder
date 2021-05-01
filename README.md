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
今の所、EEA(拡張ユークリッドアルゴリズム)で安全でないという証拠はないそうなので,取り敢えずEEAで復号できるようになっています。  
（ただし、patterson復号にはタイミング攻撃などの攻撃があるので使わないほうがいいです。）  
暗号化においてOAEP実装など細かい修正点は残っていますが、取り敢えずバイナリ公開鍵から復号までワンセットで揃っているので、以下のコードを参考に使ってみてください。  
一応BMAなんかも実装中なのですが、多項式ライブラリの出来が悪くてシンドロームだけで計算できるBMAのほうがEEAに比べて２倍くらい早いです。  
このような利点があるものの、まだバグが取りきれてないのでまずこちらのバージョンをどうぞ。  

コードサンプル(Niederreiter.c)

```c

main(){
OP w={0},f={0},r={0};
unsigned short z1[N];
vec v={0};
int  j = 0,count=0,k=0;


//公開鍵を生成する(G=SHP)
 w = pubkeygen();
 
//decode開始
    while (1)
    {
        memset(z1, 0, sizeof(z1));
        //T重みエラーベクトルの生成
        mkerr(z1, T);
        //公開鍵を使ったシンドロームの計算(s=eG)
        v = sin2(z1);
        //シンドロームの復号(s'=sS^{-1})
        f=dec(v.x);
        //復号(m'=D(s'))
        r = decode(w, f);
        //エラー（平文）の表示(m=m'P^{-1})
        count = elo2(r);
        for (int i = 0; i < N; i++)
        {
            //検算
            if (z1[i] > 0)
            printf("error position= %d %d\n", i, z1[i]);
        }
        if (count < T)
        {
             printpol(o2v(w));
             printf(" == Goppa polynomial\n");
             exit(1);
        }
        j++;
        if(count == T)
        printf("err=%dっ！！\n", count);

        if (j == 10000)
            exit(1);
    }


```

# 設定ファイルと定義体の設定  
global.h：符号のパラメータを決めます。  
chash.c ：定義体を指定します。  
ecole.c ：定義体の中身を作ります。(ecole normal basis lol)  

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

この開発を発展させたオリジナルのテーマを思いついた。（１変数多項式を使った符号の一種）

符号の多重線形写像の続きをやるか、Wild McElieceをやるか、リスト復号をやるかいろいろと迷う。符号ばっかりｗ

# 20210501

追記：おかしくもなさそうなことがわかりました。  
シンドロームを計算するのは送信者なので、エラーがどの位置にあるかを確認できます。
K/2サイズの公開鍵から2倍の大きさのシンドロームが計算できる。
とりあえず動いているのでこのままで良しとします。(fals.c)  

ちょっとおかしなことに気づきました。（気の所為ｗ）
~~シンドロームを2倍にするなんてことはできるのだろうか？
そもそも受信者はどこでエラーが発生したかを知ることができないのに、エラー位置でいちいち2倍する必要のある今の方法は現実的じゃない。
そんなわけでセンドリエのトリックは机上の空論になりそうな予感です。
今の方法では不可能だということがわかりました。  
つまりトリックじゃなくてセンドリエのフェイクですｗ  ~~
そんなわけでファイルを古いバージョンに戻します。 （早まったけどすべての履歴が残っているのでとても安心）
行列を扱うときのデータ型を準備しておいたMTXに統一。
今までものすごい量のスタックを消費していたけど、MAT型をなくすことで使用するメモリの量が減ったはず。

~~鍵サイズを半分にできる例外？として、ちょっと考えたら別の方法があることに気が付きました。
まずパリティ検査行列から1/g(x)を取り除いて、Vandermonde行列に直します。  
こうすることで、検査行列を単純化して奇数次の列から偶数次の列を作ることができ、シンドロームを二倍しても正しくエラー訂正できるようになりました。~~

あまり期待してなかったけどうまく行ってよかった。
センドリエの方法がフェイクでないかどうかはもう少し考えてみます。  
おとなしく最初からフルランクの符号を使ってればこんなに苦労はしなかったのに。('A`)  

専門家さんのアドバイスによると、仮に検査行列がRS符号だったとしてそれで解読できるとしたら面白い論文になるということです。
つまりバイナリ符号にすれば無敵らしいです。（まだ信じてないｗ）  
とりあえず公開鍵にも暗号化かけて訂正できることを確認しました。  

> >  SHPのHがRS符号になると思うのですが、公開鍵SHPからSとPを見つけられる可能性はないのでしょうか？

可能性は無いわけではなく、実際に発見できれば非常に面白い論文になります。

>ただ、より正確にはHはRSというよりGeneralized RSや Alternant Code やさらに正確には当然ながらGoppa Code のHで、皆さんそのことは織り込み済みで解読を試みられているので容易ではないと思います。だからこそ、発見できれば非常に面白い論文になります。

# 20210430

根性でバグをとった。  
途中まで闇雲にいじっていて、4時過ぎに同じデータで正解と誤解で途中計算を比較をすればいい（トレース）という事に気づいてそれから一気に片付けた。  
3重とか4重くらいのバグをかいくぐって正解にたどり着くのは、まるで登山でもしているかのようだ。  
3日がかりだったけどなんとかなった。
これでセンドリエが使えるようになる。  
公開鍵は半分のサイズ。(op.c)

# 20210429

Berlekamp-Masseyでも復号できるようになった。(op.c)
sentrierを使っていないので、パリティ検査行列は通常サイズ。

# 20210428

EEAとBMの両方でスピードを比較した。  

EEA:1min23s  
BM :1min35s  

というわけで実用サイズで(n,k,t)=(8192,256 * 13,128)の鍵生成から復号までの時間は両方とも大して変わらず遅かった。  
今の所どちらを選択すべきかはっきりと言えない。  
ただ、BMの方が符号の構造が単純なので公開鍵のサイズを小さくできる利点がある。  

既約Goppa符号からseparable Goppa符号に変更。
特にこだわりがなければ、鍵計算の速度が早くなりました。

Niederreiter暗号はそのままだと致命的な攻撃が存在するので安全ではない。  
これを安全な暗号のクラスであるIND-CCA2にするためには暗号文に加工しなければならない。  
ここではその一つの案を述べる。  
  
暗号化  
c1=eH  
c2=Gen(Hash(e))⊕m  
c3=Hash(c1‖c2‖e‖m)  
  
c=(c1,c2,c3)  
  
ここでGenは疑似乱数生成器、  
Hashはハッシュ関数  
mは平文  
cは暗号文  
eはエラーベクトル  
rはシード  
Hは公開鍵とする。  
  
Berlekamp-Massey法（BM法）はop.cにありますが、パリティ検査行列の構造が違うらしくEEAと互換性がありません。  
BM法では検査行列の半分を公開すればよく、多項式を使わないでシンドロームの値だけからエラー位置を計算するのでEEAの２倍以上高速です。  
終了条件をよく理解しないまま実装しているので、バグがあるかもしれません。
なので当面BM法については改良を進める方針です。  
どんな攻撃画があるかについてはまだ未調査なんですが、調べてみるとTiming Attackとかにパターソンアルゴリズムが弱いとか
いろいろ暗号文以外にも気をつけないといけないらしくそこまで実装が追いつかないというのが現状です。
つまり素のままの実装が今なのでいろいろ付け足していこうかと思います。
それにしても論文が多すぎる。


# 20210426

符号ベースの認証方式を作ってみたけど誰も見に来ないので寂しいｗ

# 20210424

速度比較。
５エラー訂正で１００００回ループして４秒ちょっと。
バグがまだ生きていたので潰した。
この先はこんな感じでやりたい。

# 20210423

バグにとどめを刺した。
そして急にやることがなくなったｗ．
本当はあるんだけど、暗号化は人任せって言うわけじゃだめですかね？
https://www.ipa.go.jp/security/fy12/report/ninsyou.pdf

急にやることがなくなったので、数学と英語の勉強をします。

# 20210420

シンドローム２倍関数を一般化した。
t=128まで訂正可能。
０の位置以外訂正できている。（これは修正する必要がある）

でも先生の言ってることじゃなくて、独自解釈して論文に書いてある通りHからH2を作ってそれで訂正している。

私の解釈はこれ。
https://qiita.com/fumumue/items/1da3219099c8d1679cce

私が見たのはこれ。
https://eprint.iacr.org/2017/1180.pdf

今日になってこんなのも見つかった。
https://www.iacr.org/archive/ches2017/10529219/10529219.pdf

うまく行っているのはまぐれだった可能性が高い。
というのも、復号する時２倍してしまったら、それはirreducible Goppaではなく、separable Goppaになってしまうのではないか？という不安だ。
論文にはちゃんとg(x)をg(x)^2するって書いてある。
そしてそれでうまく訂正できているのだから一見して何も問題がないように見える。

先生はg(x)で作っているものとg(x)^2の違いがわかっていないと言っていた。

これがセンドリエのトリックと言われているものかどうかはわからないが、公開鍵を半分のサイズにしていることは確かだと思う。
だって奇数列だけ取り出してそれだけで符号化しているのだから。
そしてそのシンドロームを２倍して復号できるのだ。
そしてHはH^2と等価であると書いてある。（これはどういう意味？）

よくわからないのは、奇数列の２乗で偶数列が作れるという主張だ。
確かにリードソロモンだったら、a,a^2,a^3...となるからその主張は正しい。
でもGoppa符号では 1/g(x) がついてくるから、その奇数列を２乗して計算すると復号できなくなってしまう。
そのへんがよくわからない。(泣)

自分にとっては奇数列を２乗してできる符号はg(x)^2で作ったものを連想させる。
理解できないから独自解釈したら偶然それでうまく行ってしまったという感じ。

でも私にとっては奇数列だけ取り出すというアイデアは斬新なものだった。
偶数列から奇数列は作れないから。

ちょっと残念だけど、あれだけ質問しておいて私の頭では理解できないのかもしれない。

勉強しないと。

# 2021/04/19

2エラーしか訂正できなかったバグを修正。
global.hにあるKの値を変えれば4エラーまで訂正できます。（偶数列を復元する関数が８個決め打ちなので）

センドリエじゃないけど、奇数列だけからフルランクの検査行列を再構成して、シンドロームも正しく計算できるように改良した。
これでこのプロジェクトは完成する。
奇数行だけしか使わないことで公開鍵のサイズは、8192 * 129 * 13 ≒ 13737984bitになる。（パターソンの場合とほぼ同じサイズ）

シンドロームを一行ずつなら正しく計算できるのに、2行以上だとシンドロームの計算に失敗するという問題があった。
しかし1行づつなら計算できるので、少し掘り下げて考えてみた。
すると、行を足してから２倍にするのではなく、２倍にしてから足すように順番を入れ替えたら成功した。

このプログラムの裏には専門家の献身がある。

産業技術総合研究所の古原和邦様には、特別な感謝の気持とお礼を申し上げる。

彼の多大なアドバイスと、私の１００通以上にものぼるしつこい質問に真摯に向きあってくれた忍耐がなかったら、このプログラムは完成し得なかったか、大幅に遅れていただろう。
私の乏しい理解力では、検査行列を全て計算してから、奇数列だけを抜き出すのだというトリックをなかなか理解できなかった。
特に添え字の意味が理解できず、説明が大変だったと思う。（先生の言うことを正しく理解してなくて独自解釈の結果うまくいってるだけかもしれないがｗ）

古原先生のおかげで私のやる気は最後まで衰えなかった。
あんなにメールをして申し訳なかったと思う。

この場を借りて謝罪したい。

# 20210418

やっぱり間違えていた。
多分プログラムが悪いか、私が理解してない可能性が高い。
なので紙に書いて、論文に書いてあることを自分なりに整理した。
センドリエのトリックはそんなに単純なものではないと思うし、偶数業を削除するなんて言う話は聞いたことがない。

勉強不足を感じた。

https://qiita.com/fumumue/items/1da3219099c8d1679cce

とりあえず今日勉強したことをQiitaに掲載した。
奇数の列だけから2倍の符号が構成できることがわかった。
これがそのままシンドロームにも適用できるなら、正しいことがわかるのだがなかなか理解できない。
シンドロームの合成については、あながち間違っていたとも言えない内容なので明日に希望をつなごう。

# 20210416

2倍のシンドロームの作り方がわからない。
翻訳しても具体例がないからわからない。
少なくとも次元を増やす前のシンドロームから2倍にしたときのシンドロームでは情報量が違っているので計算できないはず。
2つの符号が等価であることは、実際小さい符号から大きな符号を構成できることで確かめられる。
でもシンドロームはどう考えても等価じゃない。
シンドロームはどの位置にエラーがあるかわからない限り再構成できない。
次元の小さなパリティ検査行列に、訂正限界以上のエラーを入れても、2倍にすることができれば訂正できるようになるというのが誤解なのだろうか？
それならなぜわざわざ倍の大きさのシンドロームを計算するのか？
たしかに最初のシンドロームの各要素を2乗すれば、同じエラーを訂正できるシンドロームはできる。
でも訂正数が上がらなければ意味がない。
書いてあるとおりに最初ののシンドロームを拡大した検査行列に再入力すると、
今度は入力したシンドロームをエラーとして計算するシンドロームができてしまって意味がない。
最初は符号の代数的な構造を使って最初のシンドロームだけから構成できると思っていた。
しかし計算してみると0になる列が出てきて、掛け算じゃ出てこない値だったので諦めた。
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

