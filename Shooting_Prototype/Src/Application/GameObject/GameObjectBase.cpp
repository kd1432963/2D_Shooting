#include "GameObjectBase.h"

//+++++++++++++++++++++++++++++++++++++++++
// 行列更新
//+++++++++++++++++++++++++++++++++++++++++
void GameObjectBase::UpdateMatrix()
{
	Math::Matrix S = Math::Matrix::CreateScale(scale.x, scale.y, 1);
	Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotate));
	Math::Matrix T = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

	mat = S * R * T;
}

//+++++++++++++++++++++++++++++++++++++++++
// 行列更新（カメラ考慮）
//+++++++++++++++++++++++++++++++++++++++++
void GameObjectBase::UpdateMatrix(Math::Vector2 cameraPos)
{
	Math::Matrix S = Math::Matrix::CreateScale(scale.x, scale.y, 1);
	Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotate));
	Math::Matrix T = Math::Matrix::CreateTranslation
	(
		pos.x - cameraPos.x,
		pos.y - cameraPos.y,
		0
	);

	mat = S * R * T;
}

//+++++++++++++++++++++++++++++++++++++++++
// 座標更新
//+++++++++++++++++++++++++++++++++++++++++
void GameObjectBase::UpdatePos()
{
	pos += move;
	hitbox.pos = pos;
}