#include "SceneManager.h"

#include"Title/TitleScene.h"

SceneManager::SceneManager()
{
	PushScene(std::move(std::make_unique<TitleScene>()));
}

SceneManager::~SceneManager()
{
	while (!mp_sceneStack.empty())PopScene();
}

//+++++++++++++++++++++++++++++++++++++++++
// シーン変更リクエスト
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::RequestChange(std::unique_ptr<SceneBase> newScene, float feadTime)
{
	//=== 遷移中は受け付けない ============
	if (m_transition.IsActive()) return;

	m_reservedScene = std::move(newScene);
	m_transition.Start(feadTime);
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンを積むリクエスト
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::RequestPush(std::unique_ptr<SceneBase> newScene)
{
	//=== 遷移中は受け付けない ============
	if (m_transition.IsActive()) return;

	m_cmdQue.push({ CommandType::Push,std::move(newScene) });
}

//+++++++++++++++++++++++++++++++++++++++++
// 最上位シーンを消すリクエスト
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::RequestPop()
{
	//=== 遷移中は受け付けない ============
	if (m_transition.IsActive()) return;

	m_cmdQue.push({ CommandType::Pop,nullptr });
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新処理（最上位シーンから基本はそれのみ）
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::Update()
{
	//=== トランジション更新 =========================
    m_transition.Update(1.0f / 60.0f);	// 60FPS 前提

    //=== 切り替えタイミング =========================
    if (m_transition.IsSwitchTiming())
    {
        ChangeScene(std::move(m_reservedScene));
        m_transition.StartFadeIn();
    }

    //=== 最上位から更新処理 =========================
    for (int i = mp_sceneStack.size() - 1; i >= 0; --i)
    {
        mp_sceneStack[i]->Update();

        if (mp_sceneStack[i]->BlocksBelowUpdate()) break;
    }

    //=== コマンド実行 ===============================
    ProcessCommand();
}

//+++++++++++++++++++++++++++++++++++++++++
// コマンド実行
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::ProcessCommand()
{
	//=== コマンドがあれば実行 =============================
	while (!m_cmdQue.empty())
	{
		auto data = std::move(m_cmdQue.front());
		m_cmdQue.pop();

		switch (data.cmd)
		{
		case CommandType::Change: ChangeScene(std::move(data.scene)); break;
		case CommandType::Push: PushScene(std::move(data.scene)); break;
		case CommandType::Pop: PopScene(); break;
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理（最下位シーンから基本はすべて）
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::Draw2D()
{
	for (int i = 0; i < mp_sceneStack.size(); ++i)
	{
		mp_sceneStack[i]->Draw2D();

		if (mp_sceneStack[i]->BlocksBelowDraw())break;
	}

	//=== フェード描画 =====================
	m_transition.Draw();
}

//+++++++++++++++++++++++++++++++++++++++++
// デバック画面更新処理（最上位シーンのみ）
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::ImGuiUpdate()
{
	//=== ウィンドウの初期位置・サイズを設定 ===========================

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(250, 725), ImGuiSetCond_Always);

	//=== 動きを止めて、サイズも変更しない =============================

	ImGuiWindowFlags flag = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	//=== 画面生成 =================================================

	ImGui::Begin("Debug Window", nullptr, flag);

	//=== ライン ===================================================

	ImGui::Separator();

	if (!mp_sceneStack.empty())
	{
		mp_sceneStack.back()->ImGuiUpdate();
	}

	//=== 画面終了 ==================================================

	ImGui::End();
}

//+++++++++++++++++++++++++++++++++++++++++
// 実際にシーンを変更する関数
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::ChangeScene(std::unique_ptr<SceneBase> newScene)
{
	//=== 残っているシーン全部を削除 =====================
	while (!mp_sceneStack.empty())PopScene();

	//=== 新しいシーン一つだけにする =====================
	PushScene(std::move(newScene));
}

//+++++++++++++++++++++++++++++++++++++++++
// 実際にシーンを積む関数
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::PushScene(std::unique_ptr<SceneBase> newScene)
{
	//=== 既にシーンがあればポーズ処理を呼ぶ ==========================
	if (!mp_sceneStack.empty())mp_sceneStack.back()->OnPause();

	//=== ここでシーンを積む =======================================
	mp_sceneStack.push_back(std::move(newScene));

	//=== シーンに入った時の処理を呼ぶ ===============================
	mp_sceneStack.back()->OnEnter();
}

//+++++++++++++++++++++++++++++++++++++++++
// 実際にシーンを消す関数
//+++++++++++++++++++++++++++++++++++++++++
void SceneManager::PopScene()
{
	//=== シーンがなければ何もしない ==========
	if (mp_sceneStack.empty()) return;

	//=== 消す前に解放処理など行う ============
	mp_sceneStack.back()->OnExit();

	//=== 要素を消す ========================
	mp_sceneStack.pop_back();

	//=== まだシーンがあれば戻る歳の処理を呼ぶ ==
	if (!mp_sceneStack.empty())mp_sceneStack.back()->OnResume();
}
