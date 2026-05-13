#include "TitleScene.h"

#include"Application/Scene/SceneManager.h"

#include"Application/Scene/GameMain/GameScene.h"

#include"Application/UI/UIManager.h"

#include"Application/UI/Button/Button.h"

//+++++++++++++++++++++++++++++++++++++++++
// シーンができたときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void TitleScene::OnEnter()
{
	mp_uiManager = new UIManager();

	mp_startBtn = new Button("STARTButton", { 0.0f,-110.0f }, { 0.45f,0.45f }, { 138,32 });
	mp_startBtn->onClick = []()
		{
			SCENE_MANAGER.RequestChange(std::make_unique<GameScene>());
		};

	mp_exitBtn = new Button("EXITButton", { 0.0f,-210.0f }, { 0.45f,0.45f }, { 125,32 });
	mp_exitBtn->onClick = []()
		{
			SCENE_MANAGER.RequestChange(std::make_unique<GameScene>());
		};
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが終わるときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void TitleScene::OnExit()
{
	if (mp_uiManager)
	{
		delete mp_uiManager;
		mp_uiManager = nullptr;
	}
	if (mp_startBtn)
	{
		delete mp_startBtn;
		mp_startBtn = nullptr;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが最上位じゃなくなるときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void TitleScene::OnPause()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが最上位に戻るときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void TitleScene::OnResume()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// 更新処理（毎フレーム）
//+++++++++++++++++++++++++++++++++++++++++
void TitleScene::Update()
{
	if (KEY.IsTrigger(VK_RETURN))
	{
		SCENE_MANAGER.RequestChange(std::make_unique<GameScene>());
	}

	mp_uiManager->Update();

	mp_startBtn->Update();
	mp_exitBtn->Update();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理（毎フレーム）
//+++++++++++++++++++++++++++++++++++++++++
void TitleScene::Draw2D()
{
	//=== 背景 ===========================================================================================
	/*static float x = 0;

	x -= 5;

	if (x <= -2560) x += 2560;

	Math::Matrix S = Math::Matrix::CreateScale(5.0f, 5.5f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(x, 0, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("BackGround1"), ASSET.GetRectangle("BackGround1"));

	T = Math::Matrix::CreateTranslation(x + 1280, 0, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("BackGround2"), ASSET.GetRectangle("BackGround2"));

	T = Math::Matrix::CreateTranslation(x + 2560, 0, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("BackGround1"), ASSET.GetRectangle("BackGround1"));*/

	const float TexWidth = 1635;
	const float TexHeight = 962;

	const float ScreenWidth = 1280;
	const float ScreenHeight = 520;

	float scaleX = ScreenWidth / TexWidth;
	float scaleY = ScreenHeight / TexHeight;

	Math::Matrix S = Math::Matrix::CreateScale(scaleX, scaleY, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(0, 0, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("TitleBack"), ASSET.GetRectangle("TitleBack"));


	//===================================================================================================

	//=== タイトルロゴ ==================================================================================
	{
		float x = RandomRangeF(-0.0f, 0.0f);
		float y = RandomRangeF(-0.0f, 0.0f);

		S = Math::Matrix::CreateScale(0.75f, 0.75f, 1.0f);
		T = Math::Matrix::CreateTranslation(50.0f + x, 30.0f + y, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		Math::Color color = RandomChance(0.01f) ? RandomColor() : Math::Color{ 1,1,1,1 };
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("TitleLogo"), 0, 0, &ASSET.GetRectangle("TitleLogo"), &color);
	}
	//===================================================================================================



	mp_uiManager->DrawTitleUI();

	mp_startBtn->Draw();
	mp_exitBtn->Draw();
}

//+++++++++++++++++++++++++++++++++++++++++
// デバッグ画面更新関数
//+++++++++++++++++++++++++++++++++++++++++
void TitleScene::ImGuiUpdate()
{

}
