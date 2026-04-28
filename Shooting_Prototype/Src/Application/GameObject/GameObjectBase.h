#pragma once

#include "HitBoxBase.h"

//**********************************
// ゲーム内オブジェクトの基底クラス
//**********************************
class GameObjectBase
{
public:

	//**********************************
	// 仮想デストラクタ
	//**********************************
	virtual ~GameObjectBase() = default;

public:

	//**********************************
	// 基本処理
	//**********************************
	virtual void Update() = 0;
	virtual void Draw2D() = 0;

public:

	//**********************************
	// アクセサ
	//**********************************
	HitBoxBase* GetHitBox() const { return hitbox.get(); }
	Math::Vector2 GetPos() const { return pos; }

public:

	//**********************************
	// 行列更新
	//**********************************
	void UpdateMatrix();
	void UpdateMatrix(Math::Vector2 cameraPos);

protected:

	//**********************************
	// 内部処理
	//**********************************
	void UpdatePos();

protected:

	//**********************************
	// ステート
	//**********************************
	Math::Vector2	pos		= {};
	Math::Vector2	scale	= { 1.0f, 1.0f };
	float			rotate	= 0.0f;
	Math::Vector2	move	= { 0.0f, 0.0f };

	Math::Matrix	mat		= Math::Matrix::Identity;

	KdTexture*		tex		= nullptr;
	std::unique_ptr<HitBoxBase>	hitbox	= {};
};