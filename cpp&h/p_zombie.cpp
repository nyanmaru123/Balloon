// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// プレイヤー(ゾンビ)処理 [p_zombie.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "p_zombie.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define P_ZOMBIE_FRONTFORCE (10)
#define P_ZOMBIE_G (0.5f)			// 重力
#define P_ZOMBIE_RESISTANCE (0.5f)// 抵抗力

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CP_zombie::CP_zombie() : CPlayer::CPlayer(CHARACTER_P_ZOMBIE)
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CP_zombie::~CP_zombie()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CP_zombie::Init(void)
{
	CPlayer::Init();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CP_zombie::Uninit(void)
{
	CPlayer::Uninit();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CP_zombie::Update(void)
{
	CPlayer::Update();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CP_zombie::Draw(void)
{
	CPlayer::Draw();
}

//-------------------------------------------------------------------------------------------------------------
// 死んだときの処理
//-------------------------------------------------------------------------------------------------------------
void CP_zombie::Die(void)
{
	CPlayer::Die();
}

#ifdef _DEBUG
//-------------------------------------------------------------------------------------------------------------
// デバッグ表示
//-------------------------------------------------------------------------------------------------------------
void CP_zombie::Debug(void)
{
	CPlayer::Debug();
}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// シーン継承の当たり判定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CP_zombie::Scene_Collision(int const & nObjType, CScene * pScene)
{
	CPlayer::Scene_Collision(nObjType, pScene);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成処理(シーン管理)
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CP_zombie * CP_zombie::Create(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CP_zombie * pP_zombie;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pP_zombie = new CP_zombie();
	// シーン管理設定
	pP_zombie->ManageSetting(CScene::LAYER_CHARACTER);
	// 設定
	pP_zombie->SetPlayerID(nPlayerID);
	pP_zombie->SetPos(pos);
	pP_zombie->SetRot(rot);
	pP_zombie->SetRotDest(rot);
	// 初期化処理
	pP_zombie->Init();
	// 生成したオブジェクトを返す
	return pP_zombie;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成処理(個人管理)
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CP_zombie * CP_zombie::Create_Self(
	int const &nPlayerID,
	D3DXVECTOR3 const & pos,
	D3DXVECTOR3 const & rot
)
{
	// 変数宣言
	CP_zombie * pP_zombie;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pP_zombie = new CP_zombie();
	// 設定
	pP_zombie->SetPlayerID(nPlayerID);
	pP_zombie->SetPos(pos);
	pP_zombie->SetRot(rot);
	pP_zombie->SetRotDest(rot);
	// 初期化処理
	pP_zombie->Init();
	// 生成したオブジェクトを返す
	return pP_zombie;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// リソース情報読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CP_zombie::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだリソース情報を破棄処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CP_zombie::UnLoad(void)
{
}
