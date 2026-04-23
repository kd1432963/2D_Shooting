#pragma once

#include"Application/Chara/CharaBase.h"

class BulletBase;

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

private:

	struct BulletDeleter
	{
		void operator()(BulletBase* p);
	};

public:

	//**********************************
	// ゲッター
	//**********************************
	const std::vector<std::unique_ptr<BulletBase,BulletDeleter>>& GetBullets()const { return mp_bulletList; }



private:

	//**********************************
	// メンバ変数
	//**********************************
	
	std::vector < std::unique_ptr <BulletBase, BulletDeleter >> mp_bulletList;

	float m_shotRecast = 0.0f;
};