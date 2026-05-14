#include "ResultScene.h"

#include"Application/Scene/SceneManager.h"

#include"Application/Scene/Title/TitleScene.h"
#include"Application/Scene/GameMain/GameScene.h"

#include"Application/UI/UIManager.h"

#include"Application/UI/Button/Button.h"

//+++++++++++++++++++++++++++++++++++++++++
// シーンができたときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void ResultScene::OnEnter()
{
	SOUND.PlaySE("DrumRollSE");

	mp_uiManager = new UIManager();

	mp_restartBtn = new Button("", { 0,600 }, { 1.1f,1.1f }, { 130,25 });
	mp_restartBtn->onClick = []()
		{
			SOUND.StopBGM();
			SOUND.PlaySE("StartSE");
			SCENE_MANAGER.RequestChange(std::make_unique<GameScene>());
		};
	
	mp_backBtn = new Button("", { 0,600 }, { 1.0f,1.0f }, { 75,22.5f });
	mp_backBtn->onClick = []()
		{
			SOUND.StopBGM();
			SOUND.PlaySE("StartSE");
			SCENE_MANAGER.RequestChange(std::make_unique<TitleScene>());
		};
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが終わるときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void ResultScene::OnExit()
{
	if (mp_uiManager)
	{
		delete mp_uiManager;
		mp_uiManager = nullptr;
	}

	if (mp_restartBtn)
	{
		delete mp_restartBtn;
		mp_restartBtn = nullptr;
	}
	if (mp_backBtn)
	{
		delete mp_backBtn;
		mp_backBtn = nullptr;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが最上位じゃなくなるときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void ResultScene::OnPause()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが最上位に戻るときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void ResultScene::OnResume()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// 更新処理（毎フレーム）
//+++++++++++++++++++++++++++++++++++++++++
void ResultScene::Update()
{
	++m_time;

	if (m_time == 250)
	{
		SOUND.PlayBGM("ResultBGM");
	}

	float t = m_time / 60.0f;
	if (t > 1.0f)
	{
		t = 1.0f;
	}

	float e = 1.0f - powf(2.0f, -3.5f * t);

	float start = Screen::Height;
	float end = GameArea::Bottom / 2;

	// 下端の位置
	m_bottomY = start + (end - start) * e;

	if (m_score >= 270000)
	{
		m_rank = "S";
		m_rect = { 0, 0,86,114 };
		m_color = Math::Color(1.0f, 0.9f, 0.0f, 1.0f);
	}
	else if (m_score >= 240000)
	{
		m_rank = "A";
		m_rect = { 89 * 1, 0,96,114 };
		m_color = Math::Color(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (m_score >= 100000)
	{
		m_rank = "B";
		m_rect = { 96 * 2, 0,92,114 };
		m_color = Math::Color(0.0f, 0.5f, 1.0f, 1.0f);
	}
	else if (m_score >= 30000)
	{
		m_rank = "C";
		m_rect = { 96 * 3, 0,80,114 };
		m_color = Math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (m_score >= 10000)
	{
		m_rank = "D";
		m_rect = { 95 * 4, 0,110,114 };
		m_color = Math::Color(1.0f, 0.5f, 0.0f, 1.0f);
	}
	else
	{
		m_rank = "E";
		m_rect = { 98 * 5, 0,78,114 };
		m_color = Math::Color(0.5f, 0.5f, 0.5f, 1.0f);
	}


	mp_restartBtn->Update({ 270.0f,m_bottomY - 30.0f });
	mp_backBtn->Update({ 262.5f,m_bottomY - 132.5f });

	// UI 更新
	mp_uiManager->Update();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理（毎フレーム）
//+++++++++++++++++++++++++++++++++++++++++
void ResultScene::Draw2D()
{
	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();

	// 幕描画
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, m_bottomY, Screen::Width / 2, Screen::Height / 2, &Math::Color(0, 0, 0, 0.7f));

	SHADER.m_spriteShader.DrawBox(0, m_bottomY, 450, 360, &Math::Color(0.33f, 0.33f, 0.33f, 0.7f));
	SHADER.m_spriteShader.DrawBox(0, m_bottomY + 150, 400, 100, &Math::Color(1.0f, 1.0f, 1.0f, 1.0f), false);
	SHADER.m_spriteShader.DrawBox(-150, m_bottomY - 80, 250, 75, &Math::Color(1.0f, 1.0f, 1.0f, 1.0f), false);

	//=== スコア描画 ==================================================================================================
	DrawScore();
	//=================================================================================================================

	//=== ランク描画 ==================================================================================================

	DrawRank();

	//=================================================================================================================

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();

	DrawButton();

	// UI 描画
	mp_uiManager->DrawResultUI(100);

	MOUSE.Draw2D();
}

//+++++++++++++++++++++++++++++++++++++++++
// デバッグ画面更新関数
//+++++++++++++++++++++++++++++++++++++++++
void ResultScene::ImGuiUpdate()
{

}

void ResultScene::DrawScore()
{
	std::string str = std::to_string(m_score);

	while (str.size() < 6)
	{
		str = "0" + str;
	}

	int fixed = 0;

	if (m_time > 40)
	{
		fixed = std::min(6, (m_time - 40) / 25);
	}

	// ラベル

	Math::Matrix S = Math::Matrix::CreateScale(0.65f, 0.65f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(-197, m_bottomY + 145, 0);

	SHADER.m_spriteShader.SetMatrix(S * T * Math::Matrix::CreateTranslation(3, -3, 0));
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("SCOREResult"), 0, 0, &ASSET.GetRectangle("SCOREResult"), &Math::Color(0, 0, 0, 1));

	SHADER.m_spriteShader.SetMatrix(S * T * Math::Matrix::CreateTranslation(168, -3, 0));
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("colon"), 0, 0, &ASSET.GetRectangle("colon"), &Math::Color(0, 0, 0, 1));

	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("SCOREResult"), ASSET.GetRectangle("SCOREResult"));

	SHADER.m_spriteShader.SetMatrix(S * T * Math::Matrix::CreateTranslation(165, -3, 0));
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("colon"), ASSET.GetRectangle("colon"));

	float startX = 25;
	float y = m_bottomY + 150;

	for (int i = 0; i < 6; i++)
	{
		char num;

		// 未確定数字
		if (i < 6 - fixed)
		{
			num = '0' + RandomRange(0, 9);
		}
		else
		{
			num = str[i];
		}

		Math::Rectangle rect = {};

		switch (num)
		{
		case '0': rect = { 0,        0,87,101 }; break;
		case '1': rect = { 87 * 1,  0,88,101 }; break;
		case '2': rect = { 87 * 2,  0,87,101 }; break;
		case '3': rect = { 87 * 3,  0,87,101 }; break;
		case '4': rect = { 87 * 4,  0,87,101 }; break;
		case '5': rect = { 87 * 5,  0,87,101 }; break;
		case '6': rect = { 88 * 6,  0,87,101 }; break;
		case '7': rect = { 88 * 7,  0,87,101 }; break;
		case '8': rect = { 88 * 8,  0,87,101 }; break;
		case '9': rect = { 88 * 9,  0,87,101 }; break;
		case '?': rect = { 88 * 10, 0,87,101 }; break;
			/*case '0': rect = { 0,        0,160,160 }; break;
			case '1': rect = { 160 * 1,  0,160,160 }; break;
			case '2': rect = { 160 * 2,  0,160,160 }; break;
			case '3': rect = { 160 * 3,  0,160,160 }; break;
			case '4': rect = { 160 * 4,  0,160,160 }; break;
			case '5': rect = { 160 * 5,  0,160,160 }; break;
			case '6': rect = { 160 * 6,  0,160,160 }; break;
			case '7': rect = { 160 * 7,  0,160,160 }; break;
			case '8': rect = { 160 * 8,  0,160,160 }; break;
			case '9': rect = { 160 * 9,  0,160,160 }; break;
			case '?': rect = { 160 * 10, 0,160,160 }; break;*/
		}

		float scale = 0.83f;

		int appearFrame = 40 + (6 - i) * 25;

		if (m_time >= appearFrame &&
			m_time < appearFrame + 8)
		{
			float t = (m_time - appearFrame) / 8.0f;

			float e = 1.0f - fabsf(t * 2.0f - 1.0f);

			scale = 0.83f + e * 1.6f;
		}

		float x = startX + i * 66;

		// 調整;;
		if (num == '1'&&i!=0)
		{
			x += 5;
		}

		Math::Matrix S = Math::Matrix::CreateScale(scale, scale, 1.0f);

		Math::Matrix T = Math::Matrix::CreateTranslation(x, y, 0);

		// 影
		SHADER.m_spriteShader.SetMatrix(S * Math::Matrix::CreateTranslation(x, y - 3, 0));
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Number"), 0, 0, &rect, &Math::Color(0.6f, 0.6f, 0.6f, 1.0f));

		SHADER.m_spriteShader.SetMatrix(S * Math::Matrix::CreateTranslation(x + 3, y, 0));
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Number"), 0, 0, &rect, &Math::Color(0.6f, 0.6f, 0.6f, 1.0f));

		SHADER.m_spriteShader.SetMatrix(S * Math::Matrix::CreateTranslation(x + 3, y - 3, 0));
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Number"), 0, 0, &rect, &Math::Color(0.6f, 0.6f, 0.6f, 1.0f));

		Math::Color col;

		// 確定している桁
		if (i >= 6 - fixed)
		{
			col = Math::Color(1.0f, 1.0f, 1.0f, 1.0f);   // 例：黄色っぽく
		}
		else
		{
			col = Math::Color(1.0f, 1.0f, 1.0f, 1.0f);   // 未確定：白
		}

		// 本体
		SHADER.m_spriteShader.SetMatrix(S * T);

		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Number"), 0, 0, &rect, &col);
	}
}

void ResultScene::DrawRank()
{
	std::string rank;
	Math::Rectangle rect = {};
	Math::Color color = {};

	if (m_time < 250)
	{
		int index = m_time % 6;

		switch (index)
		{
		case 0: rect = { 0, 0,86,114 };; break;
		case 1: rect = { 89 * 1, 0,96,114 }; break;
		case 2: rect = { 96 * 2, 0,92,114 }; break;
		case 3: rect = { 96 * 3, 0,80,114 }; break;
		case 4: rect = { 95 * 4, 0,110,114 }; break;
		case 5: rect = { 98 * 5, 0,78,114 }; break;
		}

		color = Math::Color(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		rank = m_rank;
		rect = m_rect;
		color = m_color;
	}

	float scale = 1.0f;

	int appearFrame = 250 - 30;

	if (m_time >= appearFrame &&
		m_time < appearFrame + 30)
	{
		float t = (m_time - appearFrame) / 30.0f;

		float e = 1.0f - fabsf(t * 2.0f - 1.0f);

		scale = 1.0f + e * 1.5f;
	}

	Math::Matrix S = Math::Matrix::CreateScale(scale, scale, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(20, m_bottomY - 80, 0);

	SHADER.m_spriteShader.SetMatrix(S * T * Math::Matrix::CreateTranslation(3, -3, 0));
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("R"), 0, 0, &rect, &Math::Color(0.0f, 0.0f, 0.0f, 1.0f));

	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("R"), 0, 0, &rect, &color);

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();

	S = Math::Matrix::CreateScale(0.6f, 0.6f, 1.0f);
	T = Math::Matrix::CreateTranslation(-215, m_bottomY + -80, 0);

	SHADER.m_spriteShader.SetMatrix(S * T * Math::Matrix::CreateTranslation(0, -3, 0));
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("RANK"), 0, 0, &ASSET.GetRectangle("RANK"), &Math::Color(0.6f, 0.6f, 0.6f, 1.0f));
	SHADER.m_spriteShader.SetMatrix(S * T * Math::Matrix::CreateTranslation(+3, 0, 0));
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("RANK"), 0, 0, &ASSET.GetRectangle("RANK"), &Math::Color(0.6f, 0.6f, 0.6f, 1.0f));
	SHADER.m_spriteShader.SetMatrix(S * T * Math::Matrix::CreateTranslation(+3, -3, 0));
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("RANK"), 0, 0, &ASSET.GetRectangle("RANK"), &Math::Color(0.6f, 0.6f, 0.6f, 1.0f));


	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("RANK"), 0, 0, &ASSET.GetRectangle("RANK"), &Math::Color(1.0f, 1.0f, 1.0f, 1.0f));
}

void ResultScene::DrawButton()
{
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	SHADER.m_spriteShader.DrawString(127.0f+2, m_bottomY+12.0f+-2 , "[RESTART]", Math::Color(0,0,0,1), mp_restartBtn->GetScale());
	SHADER.m_spriteShader.DrawString(127.0f, m_bottomY+12.0f , "[RESTART]", mp_restartBtn->GetColor(), mp_restartBtn->GetScale());

	SHADER.m_spriteShader.DrawString(175.0f+2, m_bottomY + -92.5f-2, "[BACK]", Math::Color(0, 0, 0, 1), mp_backBtn->GetScale());
	SHADER.m_spriteShader.DrawString(175.0f, m_bottomY + -92.5f, "[BACK]", mp_backBtn->GetColor(), mp_backBtn->GetScale());

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();
	mp_restartBtn->Draw();
	mp_backBtn->Draw();
}
