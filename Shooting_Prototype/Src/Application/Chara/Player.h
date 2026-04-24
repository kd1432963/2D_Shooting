#pragma once

#include "Application/Chara/CharaBase.h"
#include "Application/Bullet/BulletType.h"

class BulletManager;

class Player : public CharaBase
{
public:

	//**********************************
	// コンストラクタ
	//**********************************
	Player();

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Update() override;
	void Action() override;
	void Draw2D() override;

public:

	//**********************************
	// 攻撃処理
	//**********************************
	void Shot(BulletManager& b);

private:

	//**********************************
	// 入力処理
	//**********************************
	void MoveInput();

	// 弾モード変更
	void ChangeShotMode();

	// 発射入力
	void ShotInput();

private:

	//**********************************
	// 弾設定
	//**********************************
	BulletType m_shotMode = BulletType::Straight;

	//**********************************
	// クールダウン
	//**********************************
	float m_shotRecast = 0.0f;
};