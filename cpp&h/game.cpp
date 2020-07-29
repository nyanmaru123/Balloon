// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ゲーム処理 [game.cpp]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "game.h"
/* 描画 */
#include "number.h"
#include "fade.h"
#include "floor.h"
#include "meshobit.h"
#include "meshdome.h"
#include "meshsphere.h"
#include "meshwall.h"
#include "3Deffect.h"
#include "bgdome.h"
#include "time.h"
#include "collision.h"
#include "camera.h"
#include "3Dparticle.h"
#include "keyboard.h"
#include "ui_group.h"
#include "Extrusion.h"
#include "3Dmap.h"
#include "score.h"
#include "network.h"
#include "item.h"
#include "thunder.h"
#include "selectcharacter.h"
#include "character_fish.h"
#include "invisible.h"
#include "revival.h"
#include "speedUP.h"
#include "attackUP.h"
#include "rank.h"

/* ポーズ */
#include "pause.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::STATE CGame::m_state = CGame::STATE_NORMAL;		// 状態
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::CGame()
{
	m_pause = NULL;
	m_state = CGame::STATE_NORMAL;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CGame::~CGame()
{
	// やること
	// プレイヤー以外が出現しない





}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Init(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	// カメラのタイプ設定
	CManager::GetRenderer()->GetCamera()->SetType(CCamera::TYPE_FOLLOW);
	/* 初期化 */
	// 状態
	m_state = STATE_NORMAL;
	// キャラクターの総人数
	CCharacter::InitStatic();
	/* 作成 */
	// 3Dエフェクトの生成
	C3DEffect::Create();
	// 球の設定
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),
		10000.0f);
	// 3Dマップ生成
	C3DMap::LoadScript("data/LOAD/MAPPING/rand.csv");
	//C3DMap::LoadCreate(C3DMap::MAP_STAGE_1);
	//CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 7);

	// プレイヤー生成
	PlayerCreate();
	// キャラクター魚生成
	// CCharacter_Fish::Create();
	// アイテム生成
	CItem::Create(D3DXVECTOR3(0.0f, 500.0f, -500.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	// スコア生成
	m_pScore = CScore::Create();
	// ポーズの生成
	m_pause = new CPause();
	// ポーズの初期化
	m_pause->Init();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Uninit(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();

	if (pNetwork != NULL)
	{// ネットワークが存在していたとき
		pNetwork->StopUpdate();				// 更新停止予約
	}

	// ポーズ
	if (m_pause != NULL)
	{
		m_pause->Uninit();
		delete m_pause;
		m_pause = NULL;
	}
	// スコア
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}
	// ゲーム状態の初期化
	m_state = STATE_NORMAL;
	// シーンの開放
	CScene::ReleaseAll();
	// シーンストップ解除
	CScene::UpdateStop(false);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Update(void)
{
	// ポーズ状態ならば
	if (m_state == STATE_PAUSE)
	{
		if (m_pause != NULL)
		{
			m_pause->Update();
		}
	}
	// ポーズ状態ではないとき
	else
	{
		// ポーズへ
		if (CManager::GetKeyConfig()->GetKeyConfigTrigger(CKeyConfig::CONFIG_POUSE))
		{
			PauseState();
		}
	}

#ifdef _DEBUG
	// 情報取得
	CFade *pFade = CManager::GetFade();	// フェード情報

	// フェードしていないとき
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardPress(TESTPLAY_NUMBER1))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// リザルトへ
				pFade->SetFade(CManager::MODE_TUTORIAL);
			}
		}
	}
	// テスト用
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ゲームへ遷移
		if (CManager::GetKeyboard()->GetKeyboardPress(TESTPLAY_NUMBER2))
		{

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// リザルトへ
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
	}

	// テスト
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_T))
	{
		// 雷生成
		CThunder::Create(D3DXVECTOR3(0.0f, 500.0f, 500.0f), D3DXVECTOR3(100.0f, 500.0f, 0.0f));
	}

#endif // _DEBUG
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::Draw(void)
{
	if (m_state == STATE_PAUSE)
	{
		if (m_pause != NULL)
		{
			m_pause->Draw();
		}
	}
	if (m_pScore != NULL)
	{
		m_pScore->Draw();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ポーズ状態
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::PauseState(void)
{
	// ゲーム状態をポーズに
	if (m_state != STATE_PAUSE)
	{
		m_state = STATE_PAUSE;
		// 更新を止める
		CScene::UpdateStop(true);
		// メニュー音
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTEDSOUND2);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// プレイヤー生成
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CGame::PlayerCreate(void)
{
	CNetwork *pNetwork = CManager::GetNetwork();
	char aAns[256];
	int aData[MAX_PLAYER];
	char cDie[64];

	memset(&cDie, 0, sizeof(cDie));

	pNetwork->SendTCP("CHARACTER_LOAD", sizeof("CHARACTER_LOAD"));
	pNetwork->DataRecv(SOCKETTYPE_CLIENT, (char*)&aAns, sizeof(aAns));
	sscanf(aAns, "%s %d %d %d %d", &cDie, &aData[0], &aData[1], &aData[2], &aData[3]);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		switch (aData[nCntPlayer])
		{
		case CPlayer::CHARATYPE_SPEED_UP:
			m_pPlayer[nCntPlayer] = CSpeedUP::Create(nCntPlayer, D3DXVECTOR3(200.0f * nCntPlayer + 500.0f, 0.0f, -200.0f * nCntPlayer));
			break;

		case CPlayer::CHARATYPE_REVIVAL:
			m_pPlayer[nCntPlayer] = CRevival::Create(nCntPlayer, D3DXVECTOR3(200.0f * nCntPlayer + 500.0f, 0.0f, -200.0f * nCntPlayer));
			break;
		case CPlayer::CHARATYPE_INVISIBLE:
			m_pPlayer[nCntPlayer] = CInvisible::Create(nCntPlayer, D3DXVECTOR3(200.0f * nCntPlayer + 500.0f, 0.0f, -200.0f * nCntPlayer));
			break;
		case CPlayer::CHARATYPE_ATTACK_UP:
			m_pPlayer[nCntPlayer] = CAttackUP::Create(nCntPlayer, D3DXVECTOR3(200.0f * nCntPlayer + 500.0f, 0.0f, -200.0f * nCntPlayer));
			break;
		}
	}
}
