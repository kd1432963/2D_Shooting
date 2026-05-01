#include "PiercingItem.h"

#include"Application/GameObject/RectHitBox.h"

PiercingItem::PiercingItem(const Math::Vector2& p)
	:ItemBase(ItemType::Piercing)
{
	//=== ”»’è ==============================

	hitbox = std::make_unique<RectHitBox>(10, 10);
	if (hitbox)
	{
		hitbox->pos = p;
	}

	//=== ‰æ‘œî•ñæ“¾ ======================

	tex = ASSET.GetTexture("PiercingItem");
	rect = ASSET.GetRectangle("PiercingItem");

	//=== î•ñ‰Šú‰» ========================

	pos = p;

	//=== ‰Šú‰»‚µ‚½î•ñ‚Ås—ñ‚ğ‰Šú‰» ======

	UpdateMatrix();
}