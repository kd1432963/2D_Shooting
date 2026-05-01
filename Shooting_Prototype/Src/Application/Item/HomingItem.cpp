#include "HomingItem.h"

#include"Application/GameObject/RectHitBox.h"

HomingItem::HomingItem(const Math::Vector2& p)
	:ItemBase(ItemType::Homing)
{
	//=== ”»’è ==============================

	hitbox = std::make_unique<RectHitBox>(12, 14);
	if (hitbox)
	{
		hitbox->pos = p;
	}

	//=== ‰æ‘œî•ñæ“¾ ======================

	tex = ASSET.GetTexture("HomingItem");
	rect = ASSET.GetRectangle("HomingItem");

	//=== î•ñ‰Šú‰» ========================

	pos = p;

	//=== ‰Šú‰»‚µ‚½î•ñ‚Ås—ñ‚ğ‰Šú‰» ======

	UpdateMatrix();
}
