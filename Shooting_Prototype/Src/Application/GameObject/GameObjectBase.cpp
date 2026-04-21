#include "GameObjectBase.h"

//+++++++++++++++++++++++++++++++++++++++++
// 行列更新
//+++++++++++++++++++++++++++++++++++++++++
void GameObjectBase::UpdateMatrix()
{
	// 各行列作成
	Math::Matrix S = Math::Matrix::CreateScale(scale.x, scale.y, 1);
	Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotate));
	Math::Matrix T = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

	// 行列合成
	mat = S * R * T;
}

//+++++++++++++++++++++++++++++++++++++++++
// 行列更新（カメラ）
//+++++++++++++++++++++++++++++++++++++++++
void GameObjectBase::UpdateMatrix(Math::Vector2 cameraPos)
{
	// 各行列作成
	Math::Matrix S = Math::Matrix::CreateScale(scale.x, scale.y, 1);
	Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotate));
	Math::Matrix T = Math::Matrix::CreateTranslation(pos.x - cameraPos.x, pos.y - cameraPos.y, 0);

	// 行列合成
	mat = S * R * T;
}
