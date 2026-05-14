#pragma once

class c_SoundPlayer
{
public:
	//+++++++++++++++++++++++++++++++++++++++++
	// シングルトン生成
	//+++++++++++++++++++++++++++++++++++++++++
	static c_SoundPlayer& GetInstance()
	{
		static c_SoundPlayer instance;
		return instance;
	}

private:
	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ・デストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	c_SoundPlayer() = default;
	~c_SoundPlayer() = default;

public:
	//+++++++++++++++++++++++++++++++++++++++++
	// 更新関数
	//+++++++++++++++++++++++++++++++++++++++++
	void Update();

public:
	//+++++++++++++++++++++++++++++++++++++++++
	// 再生関数
	//+++++++++++++++++++++++++++++++++++++++++
	void PlayBGM(const std::string& tag);
	void PlaySE(const std::string& tag);

	//+++++++++++++++++++++++++++++++++++++++++
	// BGM 用関数
	//+++++++++++++++++++++++++++++++++++++++++
	void StopBGM();		// 止める
	void PauseBGM();	// 中断する
	void ResumeBGM();	// 再開する

	//+++++++++++++++++++++++++++++++++++++++++
	// 音量セット
	//+++++++++++++++++++++++++++++++++++++++++
	void SetMasterVol(float vol) { m_masterVol = vol; }
	void SetBGMVol(float vol) { m_BGMVol = vol; }
	void SetSEVol(float vol) { m_SEVol = vol; }

public:

	void Shutdown();

private:
	//+++++++++++++++++++++++++++++++++++++++++
	// メンバ型
	//+++++++++++++++++++++++++++++++++++++++++
	//---------------------
	// 各ボリューム
	//---------------------
	float m_masterVol = 1.0f;	// 主音量
	float m_BGMVol = 0.5f;	// BGM 音量
	float m_SEVol = 0.5f;	// SE  音量

private:
	//+++++++++++++++++++++++++++++++++++++++++
	// メンバ型
	//+++++++++++++++++++++++++++++++++++++++++
	//---------------------
	// 再生中のサウンド
	//---------------------
	std::shared_ptr<KdSoundInstance>mp_bgmInstance;
	float m_bgmDefaultVol = 1.0f;

	struct SEInstance
	{
		std::shared_ptr<KdSoundInstance> instance;
		float defaultVol = 1.0f;
	};

	std::list<SEInstance> m_seList;
};

#define SOUND c_SoundPlayer::GetInstance()