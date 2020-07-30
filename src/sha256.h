#ifndef SHA256_H
#define SHA256_H
/** @file sha256sumのプロトタイプが宣言されています
	
	@date 2005-11-20
	@auther Naoki_I
 */

typedef unsigned int u_32;

//64bit長整数関係

//long long も LONG LONGも使えない環境では
//NON_SUPPORT_64のコメントアウトを外してください
//#define NON_SUPPORT_64

#ifndef NON_SUPPORT_64
	
	#ifdef WIN_32
	typedef unsigned long long u_64;
	#else
	typedef unsigned long long u_64;
	#endif
	#define U64_HIGH(a) ((u_32)(m_MesLen>>32))
	#define U64_LOW(a) ((u_32)a&0xFFFFFFFF)

#else

/**
	足し算のみに対応する64bit整数
	+, =, +=, <<(ストリーム出力) 演算子をオーバーロード済み
 */
#define U64_HIGH(a) ((u_32)a.High)
#define U64_LOW(a) ((u_32)a.Low)
struct u_64
{
	u_32 High, Low;	
	u_64()
	{
		High=0;
		Low=0;
	}
	u_64(u_32 h, u_32 l)
	{
		High=h;
		Low=l;
	}
	const u_64& operator =(const u_32&n)
	{
		High=0;
		Low=n;
		return *this;
	}
	const u_64 operator +(const u_32&n)
	{
		u_64 t(High, Low);
		t+=n;
		return t;
	}
	const u_64& operator +=(const u_32&n)
	{
		if(Low>0xFFFFFFFF-n)
			High++;
		Low+=n;
		return *this;
	}
};
#endif //#ifndef NON_SUPPORT_64

/**
	SHA256Hashを求めるクラス
	
	Pushメソッドで処理するメッセージを指定する．
	長いメッセージのハッシュを求める場合等は，
	複数回に分けてPushメソッドを読んでもよい．

	最後にFinalメソッドを呼ぶとハッシュ値を返します．
	@date 2005-11-21
	@auther Naoki_I
 */
class SHA256
{
	u_32 H[8];

	u_32 W[64];
	u_32 m_WIndex;///現在計算中のWのインデックス(ただし，単位はバイト)
	u_64 m_MesLen;

	/**
		intermdediate hash valueを求める．
		結果はH[?]に代入される．
	 */
	void CalcIntermediateHash();
public:
	SHA256();

	/**
		メッセージを追加する

		@param pMes 追加するメッセージの先頭のポインタ
		@param Len	追加するメッセージの長さ
	 */
	void Push(unsigned char*pMes, u_32 Len);

	/**
		Pushされたメッセージからハッシュ値を求める

		@param pHash 結果を代入する配列へのポインタ(256bit必要です)
	 */
	void Final(unsigned char* pHash);
};

#endif
