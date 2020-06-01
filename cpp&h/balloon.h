// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 風船処理の説明[balloon.h]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _BALLOON_H_
#define _BALLOON_H_	 // ファイル名を基準を決める

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene_X.h"
#include "model_info.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 前方宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCircleshadow;
class CScene_X;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CBalloon : public CScene
{
public:
	/* 関数 */
	CBalloon();
	~CBalloon();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// 行列情報設定
	void SetMatrix(D3DXMATRIX * mtx);			// 行列情報設定
	// 風船の初期個数を代入
	void SetBiginBalloon(int const &nBringBalloon) { m_nBringBalloon = nBringBalloon; };
	// 風船を持てる個数を変化させる(上昇・現状)
	void SetBringBalloon(int const &nBringBalloon) { m_nBringBalloon += nBringBalloon; };
	// 出現している風船の個数を変化させる(上昇・減少)
	void SetPopBalloon(int const &nPopBalloon = 1) { m_nPopBalloon += nPopBalloon; };
	// 外に出して置ける風船の最大個数を設定
	void SetPopMaxBalloom(int const &nPopMaxBaloon = 2);
	// 風船を生成
	void CreateBalloon(void);
	// シーンX情報取得
	CScene_X * GetSceneX(int const &nBalloon);	// シーンXの情報取得
	// 風船を持っている個数を取得
	int const &GetBringBalloon(void) { return m_nBringBalloon; };
	// 風船を出現している個数を取得
	int const &GetPopBalloon(void) { return m_nPopBalloon; };
	// 現在の風船の最大出現数の取得
	int const &GetPopMaxBalloon(void) { return m_nMaxPopBalloon; };
	// 生成
	static CBalloon * Create(
		D3DXMATRIX *mtx,							// 行列
		int const &nPopMaxBalloon					// 風船の最大出現数
	);
	// リソース情報読み込む設定
	static HRESULT Load(void);					// リソース情報読み込む設定
	// 読み込んだリソース情報を開放する
	static void UnLoad(void);					// 読み込んだリソース情報を開放する
protected:
private:
	/* 関数 */
	void BreakBalloon(int const &nCntBalloon);	// 風船が割れる処理
	/* 変数 */
	vector<CScene_X *> m_apSceneX;				// シーンXモデル情報
	D3DXMATRIX *m_mtx;							// 行列情報
	int m_nPopBalloon;							// 現在出現している風船の個数
	int m_nBringBalloon;						// 現在持っている風船の個数
	int m_nMaxPopBalloon;						// 最大出現数の個数
	float m_fAngleBalloon;						// 風船の出現する角度(円周率 * 2 / 最大出現数)
};		

#endif