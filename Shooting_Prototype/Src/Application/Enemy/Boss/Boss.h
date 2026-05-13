#pragma once

#include "Application/Enemy/EnemyBase.h"

class EffectManager;

class BulletManager;

class Player;

class Boss : public EnemyBase
{
public:

	Boss(const Math::Vector2& p,Player*player);

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Update() override;
	void Action() override;
	void Draw2D() override;

public:

	void DebugDraw()override;

	void BossAI();

public:

	//**********************************
	// 攻撃処理
	//**********************************
	void Shot(BulletManager& b) override;

public:

	void SetEffectManager(EffectManager* e) { effect = e; }

	bool IsDeathAnim()const { return m_deathAnimStart; }
	bool IsDead()const override;


	const std::vector<std::unique_ptr<HitBoxBase>>& GetHitBoxes() const
	{
		return m_hitboxes;
	}

private:

	enum class State
	{
		Enter,     // 登場
		Battle,    // 戦闘
		Dead       // 撃破
	};

	State m_state = State::Enter;

private:

	enum class BossShotType
	{
		Circle,
		FiveWay,
		AimFiveWay
	};

	BossShotType m_shotType = BossShotType::FiveWay;

	void ShotCircle(BulletManager&b);
	void ShotFiveWay(BulletManager& b);
	void ShotAimFiveWay(BulletManager& b, const Math::Vector2& playerPos);

private:

	std::vector<std::unique_ptr<HitBoxBase>> m_hitboxes;

	Player* mp_player = nullptr;
	EffectManager* effect = nullptr;

	int m_shotWait = 0;
	int m_aliveTime = 0;

	int m_deathAnimTime = 0;
	float m_alpha = 1.0f;
	bool m_deathAnimStart = false;
	bool m_endDeathAnim = false;

	float m_rotShotAngle = 0.0f;

	int m_timer = 0;
};