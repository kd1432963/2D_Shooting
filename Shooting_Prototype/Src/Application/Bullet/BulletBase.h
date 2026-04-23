#pragma once

#include"Application/GameObject/GameObjectBase.h"

class BulletBase :public GameObjectBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 仮想デストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	virtual ~BulletBase() = default;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本ライフサイクル 
	//+++++++++++++++++++++++++++++++++++++++++
	virtual void Update()override = 0;
	virtual void Draw2D()override = 0;
	virtual void Init() = 0;
	virtual void Action() = 0;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// ゲッター
	//+++++++++++++++++++++++++++++++++++++++++
	bool IsDead()const { return isDead; }

	//+++++++++++++++++++++++++++++++++++++++++
	// セッター
	//+++++++++++++++++++++++++++++++++++++++++
	void SetDead() { isDead = true; }

protected:

	//+++++++++++++++++++++++++++++++++++++++++
	// 共通変数
	//+++++++++++++++++++++++++++++++++++++++++
	int atk = 0;		// 攻撃力
	int lifeTime = 0;	// 生存時間
	bool isDead = false;// 死んでいるか
	float radius = 0.0f;// 半径

	std::string tag;	// 画像のタグ

};