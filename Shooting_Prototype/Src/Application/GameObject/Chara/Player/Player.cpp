#include "Player.h"

#include"PlayerConfig.h"

#include"Application/GameObject/Bullet/BulletBase.h"
#include"Application/GameObject/Bullet/StraightBullet/StraightBullet.h"

using namespace PlayerConst;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化処理
//+++++++++++++++++++++++++++++++++++++++++
void Player::Init()
{
	//=== 判定情報 ========================

	hitbox.radius = kRadius;

	//=== 画像情報取得 ====================

	tex = ASSET.GetTexture("Player");
	rect = ASSET.GetRectangle("Player");

	//=== 情報初期化 ======================

	pos = { kPosX,kPosY };
	scale = { kScaleX,kScaleY };
	rotate = 90.0f;
	move = { 0.0f,0.0f };

	//=== 初期化した情報で行列更新 ========

	UpdateMatrix();

}

//+++++++++++++++++++++++++++++++++++++++++
// 更新処理
//+++++++++++++++++++++++++++++++++++++++++
void Player::Update()
{
	// 座標確定
	UpdatePos();

	// 弾更新
	for (auto& b : mp_bulletList)
	{
		b->Update();
	}

	// いらない弾を削除
	for (auto it = mp_bulletList.begin(); it != mp_bulletList.end();)
	{
		if ((*it)->IsDead())
		{
			delete* it;
			it = mp_bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}

	// 行列更新
	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動確定
//+++++++++++++++++++++++++++++++++++++++++
void Player::Action()
{
	// リキャストを減らす
	if (m_shotRecast >= 0.0f)--m_shotRecast;

	// 毎フレーム初期化
	move = { 0.0f,0.0f };

	// 入力されてるキーによって移動量決定
	if (KEY.IsPress('W'))move.y += kWalkPow;
	else if (KEY.IsPress('A'))move.x -= kWalkPow;
	else if (KEY.IsPress('S'))move.y -= kWalkPow;
	else if (KEY.IsPress('D'))move.x += kWalkPow;

	// 玉発射
	if (KEY.IsPress(VK_RETURN) && m_shotRecast <= 0.0f)
	{
		BulletBase* straightBullet = new StraightBullet("Bullet", pos, { kShotPow, 0.0f });
		mp_bulletList.push_back(straightBullet);
		mp_bulletList.back()->Init();
		m_shotRecast = 30.0f;
	}


}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理
//+++++++++++++++++++++++++++++++++++++++++
void Player::Draw2D()
{
	// 弾描画
	for (auto& b : mp_bulletList)
	{
		b->Draw2D();
	}

	// 自機描画
	DrawChara();
}
