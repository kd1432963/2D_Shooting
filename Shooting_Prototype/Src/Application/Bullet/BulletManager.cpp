#include"BulletManager.h"

#include"BulletBase.h"

//+++++++++++++++++++++++++++++++++++++++++
// í«â¡ä÷êî
//+++++++++++++++++++++++++++++++++++++++++
void BulletManager::Add(std::unique_ptr<BulletBase> bullet)
{
	m_bullets.emplace_back(std::move(bullet));
}

//+++++++++++++++++++++++++++++++++++++++++
// çXêVèàóù
//+++++++++++++++++++++++++++++++++++++++++
void BulletManager::Update()
{
	for (auto& b : m_bullets)
	{
		b->Update();
	}

	m_bullets.erase
	(
		std::remove_if
		(
			m_bullets.begin(),
			m_bullets.end(),
			[](const std::unique_ptr<BulletBase>& b)
			{return b->IsDead(); }
		),
		m_bullets.end()
	);
}

//+++++++++++++++++++++++++++++++++++++++++
// ï`âÊèàóù
//+++++++++++++++++++++++++++++++++++++++++
void BulletManager::Draw2D()
{
	for (auto& b : m_bullets)
	{
		b->Draw2D();
	}
}
