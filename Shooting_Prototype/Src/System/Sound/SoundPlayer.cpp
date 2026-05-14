#include "SoundPlayer.h"

//+++++++++++++++++++++++++++++++++++++++++
// 更新関数
//+++++++++++++++++++++++++++++++++++++++++
void c_SoundPlayer::Update()
{
	//=== BGM 音量更新 ======================================================
	if (mp_bgmInstance)
	{
		mp_bgmInstance->SetVolume(m_masterVol * m_BGMVol * m_bgmDefaultVol);
	}

	//=== 効果音音量更新・削除 ================================================
	for (auto it = m_seList.begin();it != m_seList.end();)
	{
		if (it->instance->IsPlay())
		{
			it->instance->SetVolume(m_masterVol * m_SEVol * it->defaultVol);
			++it;
		}
		else
		{
			it = m_seList.erase(it);
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// BGM 再生関数
//+++++++++++++++++++++++++++++++++++++++++
void c_SoundPlayer::PlayBGM(const std::string& tag)
{
	//=== 念のため止める処理を書く =============
	StopBGM();

	//=== 個別音量取得 =========================
	m_bgmDefaultVol = ASSET.GetDefaltVol(tag);

	//=== サウンドインスタンス作成 =========================
	auto inst = ASSET.GetBGM(tag)->CreateInstance(true);

	if (inst)
	{
		//=== 音量をセットし再生 ====================================
		inst->SetVolume(m_masterVol * m_BGMVol * m_bgmDefaultVol);
		inst->Play(true);

		//=== 再生中のインスタンスを保存 =============================
		mp_bgmInstance = inst;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// SE 再生関数
//+++++++++++++++++++++++++++++++++++++++++
void c_SoundPlayer::PlaySE(const std::string& tag)
{
	//=== 上限チェック：20個を超えたら古いSEを削除 ============================
	const size_t kMaxSE = 20;
	if (m_seList.size() >= kMaxSE)
	{
		// 先頭（最も古い SE）を削除
		m_seList.pop_front();
	}

	SEInstance data;

	//=== 個別音量取得 =========================
	data.defaultVol = ASSET.GetDefaltVol(tag);

	//=== サウンドインスタンス作成 ============================
	data.instance = ASSET.GetSE(tag)->CreateInstance(false);

	if (data.instance)
	{
		//=== 音量をセットし再生 ============================================
		data.instance->SetVolume(m_masterVol * m_SEVol * data.defaultVol);
		data.instance->Play(false);

		//=== 再生中のデータを保存 ===========================================
		m_seList.push_back(data);
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// BGM を停止する関数
//+++++++++++++++++++++++++++++++++++++++++
void c_SoundPlayer::StopBGM()
{
	if (mp_bgmInstance)
	{
		if (mp_bgmInstance->IsPlay())
		{
			mp_bgmInstance->Stop();
			mp_bgmInstance = nullptr;
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// BGM を中断する関数
//+++++++++++++++++++++++++++++++++++++++++
void c_SoundPlayer::PauseBGM()
{
	if (mp_bgmInstance)
	{
		if (mp_bgmInstance->IsPlay())
		{
			mp_bgmInstance->Pause();
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// BGM を再開する関数
//+++++++++++++++++++++++++++++++++++++++++
void c_SoundPlayer::ResumeBGM()
{
	if (mp_bgmInstance)
	{
		if (mp_bgmInstance->IsPause())
		{
			mp_bgmInstance->Resume();
		}
	}
}


void c_SoundPlayer::Shutdown()
{
	StopBGM();
	m_seList.clear();
	mp_bgmInstance.reset();
}
