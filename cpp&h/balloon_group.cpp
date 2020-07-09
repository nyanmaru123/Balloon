// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 風船グループ処理の説明[balloon_group.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "balloon_group.h"
#include "p_thunder.h"
#include "3Dparticle.h"
#include "selectcharacter.h"
#include "spherecollision.h"
#include "circleshadow.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define BALLOON_GROUP_SPEED (10.0f)
#define BALLOON_GROUP_Y (50.0f)
#define BALLOON_GROUP_RADIUS (50.0f)

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::CBalloon_group() : CScene::CScene()
{
	// 初期化
	m_nPopBalloon_group = 2;
	m_nBringBalloon_group = 0;
	m_mtx = NULL;
	m_fAngleBalloon_group = 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::~CBalloon_group()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Init(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Uninit(void)
{
	// 終了処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Update(void)
{
	// 風船の更新処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// 更新
		m_apBalloon[nCntBalloon_group]->Update();
		// 風船グループが割れる処理
		BreakBalloon_group(nCntBalloon_group);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Draw(void)
{
	// 風船の更新処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// 描画
		m_apBalloon[nCntBalloon_group]->Draw();
	}
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Debug(void)
{
	/*
	CDebugproc::Print("所持している風船グループの数[%d]\n", m_nBringBalloon_group);
	CDebugproc::Print("出現している風船グループの数[%d]\n", m_nPopBalloon_group);
	*/
}
#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 行列情報設定処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetMatrix(D3DXMATRIX * mtx)
{
	// 行列情報のポインターをコピーする
	m_mtx = mtx;
	// 風船の親行列情報設定処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// 親行列の設定
		m_apBalloon[nCntBalloon_group]->SetParentMtx(m_mtx);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 外に出して置ける風船グループの最大個数を設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetPopMaxBalloom(
	int const & nPopMaxBaloon,
	CScene * pParent
)
{
	// 最大出現数を代入
	m_nMaxPopBalloon_group = nPopMaxBaloon;
	// 角度
	m_fAngleBalloon_group = D3DX_PI / m_nMaxPopBalloon_group * 2;
	// 初期設定
	for (int nCntBalloon_group = 0; nCntBalloon_group < m_nMaxPopBalloon_group; nCntBalloon_group++)
	{
		//風船グループ生成
		m_apBalloon.push_back(CBalloon::Create_Self(
			D3DXVECTOR3(
				sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
				BALLOON_GROUP_Y,
				cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS),
				D3DVECTOR3_ZERO,
				0
			));
		// 当たり判定設定(球)
		m_apBalloon[nCntBalloon_group]->SetCollision(
			CShape::SHAPETYPE_SPHERE,
			CCollision::OBJTYPE_BALLOON,
			false,
			pParent
		);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船グループを生成処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CreateBalloon_group(
	CScene * pParent
)
{
	// 風船グループ生成処理
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// 風船のNULLチェック
		// ->ループスキップ
		if (m_apBalloon[nCntBalloon_group] != NULL) continue;
		// プレイヤー(雷)生成
		m_apBalloon[nCntBalloon_group] = CBalloon::Create_Self(
			D3DXVECTOR3(
				sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
				BALLOON_GROUP_Y,
				cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS),
			D3DVECTOR3_ZERO,
			0
		);
		// 当たり判定設定(球)
		m_apBalloon[nCntBalloon_group]->SetCollision(
			CShape::SHAPETYPE_SPHERE,
			CCollision::OBJTYPE_BALLOON,
			false,
			pParent
		);
		// 親行列の設定
		m_apBalloon[nCntBalloon_group]->SetParentMtx(m_mtx);
		// 持っている風船グループの個数を減らす
		m_nBringBalloon_group--;
		// 出現している風船グループの個数を増やす
		m_nPopBalloon_group++;
		// エフェクトを用意するならここ




		// 生成処理が終了したら
		// ->関数を抜ける
		break;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船情報取得処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon * CBalloon_group::GetBalloon(int const & nBalloon_group)
{
	// 0 < nBalloon_group <= BALLOON_GROUP_MAXなら
	// ->関数を抜ける
	if (nBalloon_group < 0 || nBalloon_group >= (signed)m_apBalloon.size())
	{
#ifdef _DEBUG
		CCalculation::Messanger("CBalloon_group::GetSceneX->上限越え");
#endif // _DEBUG
		return NULL;
	}
	// 風船の情報を返す
	return m_apBalloon[nBalloon_group];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group * CBalloon_group::Create(
	D3DXMATRIX *mtx,			// 行列
	int const &nPopMaxBalloon_group,	// 最大風船グループ数
	CScene * pParent			// 親情報
)
{
	// 変数宣言
	CBalloon_group * pBalloon_group;		// シーン3Dクラス
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pBalloon_group = new CBalloon_group();
	// シーン管理設定
	pBalloon_group->ManageSetting(CScene::LAYER_3DOBJECT);
	// 初期化処理
	pBalloon_group->Init();
	// 外に出して置ける風船グループの最大個数を設定
	pBalloon_group->SetPopMaxBalloom(
		nPopMaxBalloon_group,
		pParent
	);
	// 出現している風船グループの個数に代入する
	pBalloon_group->m_nPopBalloon_group = nPopMaxBalloon_group;
	// 行列情報設定
	pBalloon_group->SetMatrix(mtx);
	// 生成したオブジェクトを返す
	return pBalloon_group;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// リソース情報読み込む設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CBalloon_group::Load(void)
{
	return S_OK;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだリソース情報を開放する
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::UnLoad(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 風船グループが割れる処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::BreakBalloon_group(int const &nCntBalloon_group)
{
	// 当たり判定状態がtrueなら
	// ->開放
	if (m_apBalloon[nCntBalloon_group]->GetbCollision())
	{
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
		// 出現している風船グループの個数を増やす
		m_nPopBalloon_group--;
	}
}