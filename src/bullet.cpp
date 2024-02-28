#include "Bullet.h"

namespace Engine
{
	const float BULLET_SPEED = 700;

	Bullet::Bullet(float x, float y, float angle)
		: Entity{x, y, 7, 7, "res/img/square.png"}
	{
		m_color = {255, 255, 85, 255};
	}

	void Bullet::Update()
	{
		m_position.y += BULLET_SPEED * GetFrameTime();
	}
}