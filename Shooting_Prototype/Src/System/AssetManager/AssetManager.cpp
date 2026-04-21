#include "AssetManager.h"

//===================================================================
// 「画像.pngファイル」関連の処理
//===================================================================
//+++++++++++++++++++++++++++++++++++++++++
// 読み込み処理（Scene内で一番最初のみ実行）
//+++++++++++++++++++++++++++++++++++++++++
void c_AssetManager::LoadTexture()
{
	//TexData.csv を開く
	std::ifstream file("_Texture/TexData.csv");
	if (!file.is_open())return;

	//最初の行をスキップする
	std::string line;
	std::getline(file, line);

	//1列目：タグ名 2列目：横幅 3列目：縦幅 4列目：ファイルパス をそれぞれ読み込む
	while (std::getline(file, line))
	{
		//セットアップ
		std::stringstream ss(line);
		std::string tag;
		std::string widthStr;
		std::string heightStr;
		std::string path;

		//タグ名 横幅 縦幅 ファイルパス をそれぞれ格納
		std::getline(ss, tag, ',');
		std::getline(ss, widthStr, ',');
		std::getline(ss, heightStr, ',');
		std::getline(ss, path, ',');
		if (tag.empty() || path.empty())continue;	//エラー防止

		//文字列を数値に変換
		int width = std::stoi(widthStr);
		int height = std::stoi(heightStr);

		//「KdTexture*」を読み込んで格納
		auto tex = std::make_unique<KdTexture>();
		if (tex->Load(path))
		{
			m_TexMap[tag].texture = std::move(tex);
		}
		else
		{
			continue;
		}

		//「Math::Rectangle」を読み込んで格納
		Math::Rectangle rect;
		rect.x = 0;
		rect.y = 0;
		rect.width = width;
		rect.height = height;
		m_TexMap[tag].rect = rect;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 解放処理（Scene内で一番最初のみ実行）
//+++++++++++++++++++++++++++++++++++++++++
void c_AssetManager::ReleaseTexture()
{
	m_TexMap.clear();
}

//+++++++++++++++++++++++++++++++++++++++++
// 呼び出し処理（各クラスが呼び出す）
//+++++++++++++++++++++++++++++++++++++++++
//---------------------
// 「KdTexture*」型の取得
//---------------------
KdTexture* c_AssetManager::GetTexture(const std::string& tag)
{
	//キー(string)から数値(KdTexture*)を探して値を返す
	auto it = m_TexMap.find(tag);
	if (it != m_TexMap.end())
	{
		//=== get() は生ポインタを返す関数 ==========

		return it->second.texture.get();
	}
	return (nullptr);
}

//---------------------
// 「Math::Rectangle」型の取得
//---------------------
Math::Rectangle c_AssetManager::GetRectangle(const std::string& tag)
{
	//キー(string)から数値(Math::Rectangle)を探して値を返す
	auto it = m_TexMap.find(tag);
	if (it != m_TexMap.end())
	{
		return (it->second.rect);
	}
	return (Math::Rectangle());
}

//===================================================================
// 「音源.wavファイル」関連の処理
//===================================================================
//+++++++++++++++++++++++++++++++++++++++++
// 読み込み処理（Scene内で一番最初のみ実行）
//+++++++++++++++++++++++++++++++++++++++++
void c_AssetManager::LoadSound()
{
	LoadSE();
	LoadBGM();
}
//+++++++++++++++++++++++++++++++++++++++++
// 解放処理（Scene内で一番最初のみ実行）
//+++++++++++++++++++++++++++++++++++++++++
void c_AssetManager::ReleaseSound()
{
	m_SEMap.clear();
	m_BGMMap.clear();
}
//+++++++++++++++++++++++++++++++++++++++++
// 呼び出し処理（各クラスが呼び出す）
//+++++++++++++++++++++++++++++++++++++++++
//---------------------
// 「std::shared_ptr<KdSoundEffect>」型の取得：SE音源
//---------------------
std::shared_ptr<KdSoundEffect> c_AssetManager::GetSE(const std::string& tag)
{
	//キー(string)から数値(KdSoundEffect)を探して値を返す
	auto it = m_SEMap.find(tag);
	if (it != m_SEMap.end())
	{
		return (it->second.sound);
	}
	return (nullptr);
}
//---------------------
// 「std::shared_ptr<KdSoundEffect>」型の取得：BGM音源
//---------------------
std::shared_ptr<KdSoundEffect> c_AssetManager::GetBGM(const std::string& tag)
{
	//キー(string)から数値(KdSoundEffect)を探して値を返す
	auto it = m_BGMMap.find(tag);
	if (it != m_BGMMap.end())
	{
		return (it->second.sound);
	}
	return (nullptr);
}

//---------------------
// 「float」型の取得：個別音量
//---------------------
float c_AssetManager::GetDefaltVol(const std::string& tag)
{
	//キー(string)から数値を探して値を返す
	auto it = m_BGMMap.find(tag);
	if (it != m_BGMMap.end())
	{
		return (it->second.defaultVol);
	}
	return 1.0f;
}

//+++++++++++++++++++++++++++++++++++++++++
// 「音源.wavファイル」の読み込み処理：SE音源
//+++++++++++++++++++++++++++++++++++++++++
void c_AssetManager::LoadSE()
{
	//SEData.csv を開く
	std::ifstream file("_Sound/SEData.csv");
	if (!file.is_open())return;

	//最初の行をスキップする
	std::string line;
	std::getline(file, line);

	//1列目：タグ名 2列目：ファイルパス をそれぞれ読み込む
	while (std::getline(file, line))
	{
		//セットアップ
		std::stringstream ss(line);
		std::string tag, path, volstr;

		//タグ名 ファイルパス をそれぞれ格納
		std::getline(ss, tag, ',');
		std::getline(ss, path, ',');
		std::getline(ss, volstr, ',');
		if (tag.empty() || path.empty())continue;	//エラー防止
		 
		//文字列を数値に変換
		float vol = std::stof(volstr);

		//「std::shared_ptr<KdSoundEffect>」を読み込んで格納
		auto se = std::make_shared<KdSoundEffect>();
		if (se->Load(path))
		{
			m_SEMap[tag].sound = se;
			m_SEMap[tag].defaultVol = vol;
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++
// 「音源.wavファイル」の読み込み処理：BGM音源
//+++++++++++++++++++++++++++++++++++++++++
void c_AssetManager::LoadBGM()
{
	//BGMData.csv を開く
	std::ifstream file("_Sound/BGMData.csv");
	if (!file.is_open())return;

	//最初の行をスキップする
	std::string line;
	std::getline(file, line);

	//1列目：タグ名 2列目：ファイルパス をそれぞれ読み込む
	while (std::getline(file, line))
	{
		//セットアップ
		std::stringstream ss(line);
		std::string tag, path, volstr;

		//タグ名 ファイルパス をそれぞれ格納
		std::getline(ss, tag, ',');
		std::getline(ss, path, ',');
		std::getline(ss, volstr, ',');
		if (tag.empty() || path.empty())continue;	//エラー防止

		//文字列を数値に変換
		float vol = std::stof(volstr);

		//「std::shared_ptr<KdSoundEffect>」を読み込んで格納
		auto bgm = std::make_shared<KdSoundEffect>();
		if (bgm->Load(path))
		{
			m_BGMMap[tag].sound = bgm;
			m_BGMMap[tag].defaultVol = vol;
		}
	}
}