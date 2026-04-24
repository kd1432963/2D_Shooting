#pragma once

#include"Application/Chara/CharaBase.h"

#include"Application/Bullet/BulletType.h"

class BulletManager;


class Player :public CharaBase
{
public:

	Player();

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Update()override;	// 更新
	void Action()override;	// 行動決定
	void Draw2D()override;	// 描画

public:

	//**********************************
	// 弾関係
	//**********************************
	void Shot(BulletManager& b);

private:

	//**********************************
	// 打つ種類
	//**********************************
	BulletType m_shotMode = BulletType::Straight;

private:

	//**********************************
	// メンバ変数
	//**********************************
	float m_shotRecast = 0.0f;
};