#pragma once

//**********************************
// ゲーム内オブジェクトの基底クラス
//**********************************
class GameObjectBase
{
public:

	//**********************************
	// 仮想デストラクタ
	//**********************************
	~GameObjectBase() = default;


public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	virtual void Update() = 0;	// 更新
	virtual void Draw2D() = 0;	// 描画

public:

	//**********************************
	// 便利関数
	//**********************************
	void UpdateMatrix();						// 行列更新
	void UpdateMatrix(Math::Vector2 cameraPos);	// 行列更新（カメラ）

protected:

	//**********************************
	// 共通変数
	//**********************************
	Math::Vector2 pos = { 0.0f,0.0f };			// 座標
	Math::Vector2 scale = { 1.0f,1.0f };		// 拡大率
	float rotate = 0.0f;						// 回転
	Math::Vector2 move = { 0.0f,0.0f };			// 移動量
	Math::Matrix mat = Math::Matrix::Identity;	// 行列
	KdTexture* tex;								// 画像
};