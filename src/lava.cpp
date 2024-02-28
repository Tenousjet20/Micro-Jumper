#include "Lava.h"

namespace Engine
{
	const float LAVA_SPEED = 65;

	Lava::Lava(float width, float height)
		: Entity{0, 1200, width + 100, height, "res/img/square.png"}
	{
		m_stopMoving = false;

		m_color = {255, 77, 0, 255};
	}

	void Lava::StopMoving()
	{
		m_stopMoving = true;
	}

	void Lava::Reset()
	{
		m_position.y = 1200;
		m_stopMoving = false;
		m_particles.clear();
	}

	void Lava::Update(float playerX)
	{
		m_position.x = playerX;

		if (!m_stopMoving)
			m_position.y -= LAVA_SPEED * GetFrameTime();

		m_particleTimer += GetFrameTime();

		if (m_particleTimer >= 0.4)
		{
			m_particles.push_back({{(float)GetRandomValue(m_position.x - m_dst.width / 2, m_position.x + m_dst.width / 2), m_position.y - m_dst.height / 2}, {5, 5}, -400});
			
			m_particleTimer = 0;
		}
	}

	void Lava::RenderParticles()
	{
		for (auto& particle : m_particles)
		{
			particle.AddGravity();
			DrawRectangleV(particle.position, particle.size, ORANGE);
		}
	}
}