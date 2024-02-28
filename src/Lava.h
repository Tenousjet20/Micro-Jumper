#pragma once

#include <raylib.h>
#include <vector>

#include "Entity.h"

namespace Engine
{
	struct Particle
	{
		Vector2 position;
		Vector2 size;
		float gravity;

		void AddGravity()
		{
			gravity += 600 * GetFrameTime();
			position.y += gravity * GetFrameTime();
		}
	};

	class Lava : public Entity
	{
	private:
		bool m_stopMoving;
		std::vector<Particle> m_particles;

		float m_particleTimer;
	public:
		Lava(float width, float height);

		void StopMoving();

		void Reset();

		void Update(float playerX);

		void RenderParticles();
	};
}