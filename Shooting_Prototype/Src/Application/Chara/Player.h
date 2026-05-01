#pragma once

#include "Application/Chara/CharaBase.h"
#include "Application/Bullet/BulletType.h"
#include"Application/Item/ItemType.h"

class BulletManager;
class ItemStockManager;

class Player : public CharaBase
{
public:

	//**********************************
	// コンストラクタ
	//**********************************
	Player();
	~Player();

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




	void GetItem(ItemType type);

	const ItemStockManager& GetItemStockManager()const { return *m_itemManager; }

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
	// アイテムストック
	//**********************************
	ItemStockManager* m_itemManager = nullptr;

	//**********************************
	// 弾設定
	//**********************************
	BulletType m_shotMode = BulletType::Straight;

	//**********************************
	// クールダウン
	//**********************************
	float m_shotRecast = 0.0f;
};