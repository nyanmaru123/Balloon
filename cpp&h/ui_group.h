// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// UIグループ処理の説明[ui_group.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _UI_GROUP_H_
#define _UI_GROUP_H_	 // ファイル名を基準を決める

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ui.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 前方宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CUi_group : public CScene
{
public:
	/* 関数 */
	CUi_group();
	~CUi_group();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// 当たった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	) {};
	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return NULL; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };

	static HRESULT Load(void);		// 読み込み
	static void UnLoad(void);		// UnLoadする
	// 作成(個人管理)
	static std::unique_ptr<CUi_group> Create_Self(CUi::UITYPE const &uitype);
	// 作成(シーン管理)
	static CUi_group * Create(CUi::UITYPE const &uitype);
	// UI全体の状態情報取得
	int GetUiGroup_FadeType(void);
	// フェードアウトスタート
	// 引数なし:UI全部
	// 引数あり:UIの番号だけ
	void Start_FadeOut(int const &ID = -1);
	// フェードインスタート
	// 引数なし:UI全部
	// 引数あり:UIの番号だけ
	void Start_FadeIn(int const & ID);

protected:

private:
	/* 関数 */
// ゲームオーバー
	void Update_GameOver(void);
	/* 変数 */
	CUi::UITYPE m_Uitype;
	/* 各UIクラス */
	CUi::VEC_UNI_UI m_Ui;							// UI情報
	// 処理に必要な変数
	// int型
	std::vector<int> m_vec_nNumber;							// int情報
														// bool型
	std::vector<bool> m_vec_Bool;							// bool情報

};

#endif