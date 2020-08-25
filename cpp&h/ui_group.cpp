// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// UIグループ処理の説明[ui_group.cpp]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 描画 */
#include "ui_group.h"
#include "fade.h"
#include "game.h"
#include "camera.h"
#include "time.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// グローバル変数
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 選択

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CUi_group::CUi_group()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CUi_group::~CUi_group()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Init(void)
{
	// UIの生成
	m_Ui = std::move(CUi::LoadCreate_Self(
		m_Uitype
	));
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Uninit(void)
{
	// PauseUIの終了処理
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Uninit();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Update(void)
{
	switch (m_Uitype)
	{
	case CUi::UITYPE_DIE:
	Update_GameOver();
		break;
	default:
		break;
	}
	// UIの更新処理
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Update();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Draw(void)
{
	// UIの描画処理
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		m_Ui[nCntUi]->Draw();
	}
}

#ifdef _DEBUG
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Debug(void)
{
}
#endif // _DEBUG

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CUi_group::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::UnLoad(void)
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理(個人管理)
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::unique_ptr<CUi_group> CUi_group::Create_Self(CUi::UITYPE const &uitype)
{
	// 変数宣言
	std::unique_ptr<CUi_group> pUi_group(new CUi_group);
	// UITypeの設定
	pUi_group->m_Uitype = uitype;
	// 初期化処理
	pUi_group->Init();
	// 生成したオブジェクトを返す
	return pUi_group;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理(シーン管理)
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CUi_group * CUi_group::Create(CUi::UITYPE const &uitype)
{
	// 変数宣言
	CUi_group * pUi_group = new CUi_group;
	// UITypeの設定
	pUi_group->m_Uitype = uitype;
	// 初期化処理
	pUi_group->Init();
	// シーン管理
	pUi_group->ManageSetting(CScene::LAYER_UI);
	// 生成したオブジェクトを返す
	return pUi_group;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// UI全体の状態情報取得
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CUi_group::GetUiGroup_FadeType(void)
{
	C2DPresents::FADETYPE FadeType = C2DPresents::FADETYPE_NONE;
	for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
	{
		// フェードタイプがNONEなら
		// ->必ずFadeTypeが代入される
		if (FadeType == C2DPresents::FADETYPE_NONE)
		{
			// プレゼン情報があれば
			// ->そのまま代入
			if (m_Ui[nCntUi]->GetPresents() != NULL)
			{
				FadeType = m_Ui[nCntUi]->GetPresents()->GetFadetype();
			}
			// なければ
			// ->FADETYPE_ENDを代入
			else
			{
				FadeType = C2DPresents::FADETYPE_END;
			}
		}
		// それ以外なら
		else
		{
			// プレゼン情報があれば
			if (m_Ui[nCntUi]->GetPresents() != NULL)
			{
				// フェードタイプがUIのフェードタイプの情報より超過だと
				// ->UIのフェードタイプの情報を代入する
				if (FadeType > m_Ui[nCntUi]->GetPresents()->GetFadetype())
				{
					FadeType = m_Ui[nCntUi]->GetPresents()->GetFadetype();
				}
			}
		}

	}
	return (int)FadeType;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// フェードアウトを開始する
// 引数なし:UI全部
// 引数あり:UIの番号だけ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Start_FadeOut(int const & ID)
{
	// -1の場合
	// ->UI全部のフェードアウトを開始する
	if (ID == -1)
	{
		for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
		{
			if (m_Ui[nCntUi]->GetPresents() == NULL)
			{
				continue;
			}
			// フェードアウト開始
			m_Ui[nCntUi]->GetPresents()->Start_FadeOut();
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// フェードイン開始する
// 引数なし:UI全部
// 引数あり:UIの番号だけ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Start_FadeIn(int const & ID)
{
	// -1の場合
	// ->UI全部のフェードアウトを開始する
	if (ID == -1)
	{
		for (int nCntUi = 0; nCntUi < (signed)m_Ui.size(); nCntUi++)
		{
			if (m_Ui[nCntUi]->GetPresents() == NULL)
			{
				continue;
			}
			// フェードアウト開始
			m_Ui[nCntUi]->GetPresents()->Start_FadeIn();
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ゲームオーバーUI用更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CUi_group::Update_GameOver(void)
{
	if (GetUiGroup_FadeType() == C2DPresents::FADETYPE_COOPERATION)
	{
		Start_FadeOut();
	}
	if (GetUiGroup_FadeType() == C2DPresents::FADETYPE_END)
	{
		Release();
	}
}