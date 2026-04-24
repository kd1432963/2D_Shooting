#pragma once

#include "Application/GameObject/GameObjectBase.h"
#include "BulletOwner.h"

class BulletBase : public GameObjectBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 仮想デストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	virtual ~BulletBase() = default;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本処理
	//+++++++++++++++++++++++++++++++++++++++++
	virtual void Update() override = 0;
	virtual void Draw2D() override = 0;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// ゲッター
	//+++++++++++++++++++++++++++++++++++++++++
	bool IsDead() const { return isDead; }
	int GetAtk() const { return atk; }
	BulletOwner GetOwner() const { return owner; }

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// セッター
	//+++++++++++++++++++++++++++++++++++++++++
	void SetDead() { isDead = true; }

protected:

	int atk = 0;
	int lifeTime = 0;
	bool isDead = false;
	float radius = 0.0f;
	BulletOwner owner = BulletOwner::Player;

	std::string tag;
};