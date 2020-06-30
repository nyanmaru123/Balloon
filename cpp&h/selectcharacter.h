// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// キャラクター選択処理 [selectcharacter.h]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _SELECTCHARACTER_H_
#define _SELECTCHARACTER_H_

#define _CRT_SECURE_NO_WARNINGS

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 前方宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CP_thunder;			// ポーズ
class CP_zombie;			// スコア
class CScene_TWO;			// シーン2D

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CSelectCharacter : public CScene
{
public:
	/* 列挙型 */
	// 状態
	/* 関数 */
	CSelectCharacter();
	~CSelectCharacter();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void) {};
#endif // _DEBUG
	// 当たった後の処理
	// 引数1:オブジェクトタイプ
	// 引数2:相手のシーン情報
	virtual void Scene_Collision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	)
	{};
	// ポインター位置情報を取得
	D3DXVECTOR3 * Scene_GetPPos(void) { return &m_pos; };
	// ポインター過去の位置情報を取得
	D3DXVECTOR3 * Scene_GetPPosold(void) { return NULL; };
	// ポインター移動量情報の取得
	D3DXVECTOR3 * Scene_GetPMove(void) { return NULL; };
	// 生成
	static CSelectCharacter * Create(
		int const &nPlayerId,	// プレイヤーID
		D3DXVECTOR3 const &pos	// 位置
	);
	// 静的変数の初期化
	// (選択画面の初期化時に関数を呼ぶ)
	static void InitStatic(void);
	// プレイヤーが選んだキャラクタータイプを取得
	static int GetSaveCharaType(int const &nPlayerID) { return m_SaveCharaType[nPlayerID]; };
protected:
private:
	/* 関数 */
	/* 変数 */
	static int m_SaveCharaType[CONTROLPLAYER_MAX];					// プレイヤーが選んだキャラクタータイプを保存
	CP_thunder * m_pThunder;										// プレイヤー(雷)
	CP_zombie * m_pZombie;											// プレイヤー(ゾンビ)
	CScene_TWO * m_pSelectUi;										// 選択UI
	CScene_TWO * m_pSelectIcon[CCharacter::CHARACTER_PLAYERMAX];	// キャラクター選択アイコン
	int m_CharacterType;											// キャラクタータイプ
	int m_PlayerID;													// プレイヤー番号
	D3DXVECTOR3 m_pos;												// 位置
};
#endif
