#pragma once

#include"Core/SceneBase.h"
#include"TransitionController.h"

class SceneManager
{
public:

	//**********************************
	// シングルトン生成
	//**********************************
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

public:

	//**********************************
	// コマンドリクエスト
	//**********************************
	void RequestChange(std::unique_ptr<SceneBase>newScene, float feadTime = 1.0f);	// シーンを変更したい
	void RequestPush(std::unique_ptr<SceneBase>newScene);							// シーンを積みたい
	void RequestPop();																// シーンを戻したい

public:

	//**********************************
	// 毎フレーム実行
	//**********************************
	void Update();			// 更新処理
	void ProcessCommand();	// コマンド実行
	void Draw2D();			// 描画処理
	void ImGuiUpdate();		// デバック画面更新

private:

	//**********************************
	// コンストラクタ・デストラクタ
	//**********************************
	SceneManager();
	~SceneManager();


private:

	//**********************************
	// リクエストの種類
	//**********************************
	enum class CommandType
	{
		Change,	// 変更
		Push,	// 積む
		Pop		// 戻す
	};

	//**********************************
	// リクエストコマンドの構造体
	//**********************************
	struct CommandData
	{
		CommandType cmd;
		std::unique_ptr<SceneBase>scene;
	};

private:

	//**********************************
	// シーンやコマンドを保存しておく
	//**********************************
	std::vector<std::unique_ptr<SceneBase>>mp_sceneStack;
	std::queue<CommandData>m_cmdQue;
	std::unique_ptr<SceneBase> m_reservedScene;

private:

	//**********************************
	// シーン遷移のコントローラー
	//**********************************
	TransitionController m_transition;

private:

	//**********************************
	// 実際にシーンの操作を行う関数
	//**********************************
	void ChangeScene(std::unique_ptr<SceneBase>newScene);
	void PushScene(std::unique_ptr<SceneBase>newScene);
	void PopScene();

private:

	// 次のフェード秒数
	float m_nextFeadTime = 0.0f;

};

#define SCENE_MANAGER SceneManager::GetInstance()