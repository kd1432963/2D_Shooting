#pragma once

class c_AssetManager
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// シングルトン生成
	//+++++++++++++++++++++++++++++++++++++++++
	static c_AssetManager& GetInstance()
	{
		static c_AssetManager instance;
		return instance;
	}

private:
	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ・デストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	c_AssetManager() = default;
	~c_AssetManager() = default;

public:
	//+++++++++++++++++++++++++++++++++++++++++
	// 読み込み処理（Scene内で一番最初のみ実行）
	//+++++++++++++++++++++++++++++++++++++++++
	void LoadTexture();
	//+++++++++++++++++++++++++++++++++++++++++
	// 解放処理（Scene内で一番最初のみ実行）
	//+++++++++++++++++++++++++++++++++++++++++
	void ReleaseTexture();
	//+++++++++++++++++++++++++++++++++++++++++
	// 呼び出し処理（各クラスが呼び出す）
	//+++++++++++++++++++++++++++++++++++++++++
	//---------------------
	// 「KdTexture*」型の取得
	//---------------------
	KdTexture* GetTexture(const std::string& tag);
	//---------------------
	// 「Math::Rectangle」型の取得
	//---------------------
	Math::Rectangle GetRectangle(const std::string& tag);

private:

	//=== Texture のデータの構造体 ===============

	struct TextureData
	{
		std::unique_ptr<KdTexture> texture;
		Math::Rectangle rect;

		TextureData() = default;
		TextureData(std::unique_ptr<KdTexture> tex, const Math::Rectangle& r)
			: texture(std::move(tex)), rect(r) {
		}
	};

	//+++++++++++++++++++++++++++++++++++++++++
	// メンバ型
	//+++++++++++++++++++++++++++++++++++++++++
	//---------------------
	// 「TextureData」型のマップクラス
	//---------------------
	std::unordered_map<std::string, TextureData> m_TexMap;

public:
	//+++++++++++++++++++++++++++++++++++++++++
	// 読み込み処理（Scene内で一番最初のみ実行）
	//+++++++++++++++++++++++++++++++++++++++++
	void LoadSound();
	//+++++++++++++++++++++++++++++++++++++++++
	// 解放処理（Scene内で一番最初のみ実行）
	//+++++++++++++++++++++++++++++++++++++++++
	void ReleaseSound();
	//+++++++++++++++++++++++++++++++++++++++++
	// 呼び出し処理（各クラスが呼び出す）
	//+++++++++++++++++++++++++++++++++++++++++
	//---------------------
	// 「std::shared_ptr<KdSoundEffect>」型の取得
	//---------------------
	std::shared_ptr<KdSoundEffect> GetSE(const std::string& tag);	//SE音源
	std::shared_ptr<KdSoundEffect> GetBGM(const std::string& tag);	//BGM音源
	//---------------------
	// 「float」型の取得
	//---------------------
	float GetDefaltVol(const std::string& tag);	// 音量

private:

	//=== Sound のデータの構造体 ==================

	struct SoundData
	{
		std::shared_ptr<KdSoundEffect>sound;
		float defaultVol;
	};

	//+++++++++++++++++++++++++++++++++++++++++
	// メンバ型
	//+++++++++++++++++++++++++++++++++++++++++
	//---------------------
	// 「std::shared_ptr<KdSoundEffect>」型のマップクラス
	//---------------------
	std::unordered_map<std::string, SoundData> m_SEMap;	//SE音源
	std::unordered_map<std::string, SoundData> m_BGMMap;	//BGM音源
	//+++++++++++++++++++++++++++++++++++++++++
	// メンバ関数
	//+++++++++++++++++++++++++++++++++++++++++
	//---------------------
	// 「音源.wavファイル」の読み込み処理
	//---------------------
	void LoadSE();	//SE音源
	void LoadBGM();	//BGM音源

};

#define ASSET c_AssetManager::GetInstance()