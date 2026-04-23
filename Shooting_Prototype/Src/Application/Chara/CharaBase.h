#pragma once

#include"Src/Application/GameObject/GameObjectBase.h"

class CharaBase :public GameObjectBase
{
public:

	//**********************************
	// 仮想デストラクタ
	//**********************************
	virtual ~CharaBase() = default;

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	virtual void Update()override = 0;	// 更新
	virtual void Draw2D()override = 0;	// 描画
	virtual void Action() = 0;			// 行動決定
	virtual void Init() = 0;			// 初期化


	void TakeDamage(int damage) { status.hp -= damage; }

protected:

	//**********************************
	// 短縮のための関数
	//**********************************
	void DrawChara();

protected:

	//**********************************
	// ステータス構造体
	//**********************************
	struct Status
	{
		int hp = 0;		// 体力
		int maxHp = 0;	// 最大体力
		int atk = 0;	// 攻撃力
		int def = 0;	// 防御力
	};

protected:

	//**********************************
	// 共通変数
	//**********************************
	Status status;
	Math::Rectangle rect;
};