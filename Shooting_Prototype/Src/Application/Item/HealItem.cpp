#include "HealItem.h"

#include"Application/GameObject/RectHitBox.h"

HealItem::HealItem(const Math::Vector2& p)
	:ItemBase(ItemType::Heal)
{
	//=== ”»’è ==============================

	hitbox = std::make_unique<RectHitBox>(12, 15);
	if (hitbox)
	{
		hitbox->pos = p;
	}

	//=== ‰æ‘œî•ñæ“¾ ======================

	tex = ASSET.GetTexture("HPIcon");
	rect = ASSET.GetRectangle("HPIcon");

	//=== î•ñ‰Šú‰» ========================

	pos = p;
	scale.x = 0.75f*0.5f;
	scale.y = 1.0f*0.5f;

	//=== ‰Šú‰»‚µ‚½î•ñ‚Ås—ñ‚ğ‰Šú‰» ======

	UpdateMatrix();
}
