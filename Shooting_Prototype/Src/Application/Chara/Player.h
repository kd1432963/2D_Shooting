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


	void TakeDamage(int damage)override;


	void GetItem(ItemType type);
	float GetItemRecast() const{ return m_itemRecast; }

	bool IsInvincible()const { return m_isInvincible; }

	const ItemStockManager& GetItemStockManager()const { return *m_itemManager; }

private:

	//**********************************
	// 入力処理
	//**********************************
	void MoveInput();

	// 発射入力
	void ShotInput();

	// アイテム消費による効果
	void UseItemEffect(ItemType type);

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

	//=== アイテム系 ===================
	float m_homingTime = 0.0f;
	float m_piercingTime = 0.0f;
	float m_itemRecast = 0.0f;

	//=== 無敵管理 =====================
	bool m_isInvincible = false;
	float m_invincibleTimer = 0.0f;

	//=== 点滅用 =======================
	float m_blinkTimer = 0.0f;
};