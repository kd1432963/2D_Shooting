#pragma once

#include"Application/Chara/CharaBase.h"

class BulletManager;

class Player :public CharaBase
{
public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Init()override;	// 初期化
	void Update()override;	// 更新
	void Action()override;	// 行動決定
	void Draw2D()override;	// 描画

public:

	//**********************************
	// 弾関係
	//**********************************
	void Shot(BulletManager& b);

private:

	

private:

	//**********************************
	// メンバ変数
	//**********************************
	float m_shotRecast = 0.0f;
};