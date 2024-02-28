#pragma once

#include <raylib.h>
#include <raymath.h>
#include <memory>
#include <vector>

#include "Entity.h"
#include "Bullet.h"

namespace Engine
{
	class Player : public Entity
	{
	private:
		Vector2 m_velocity;
		float m_gravity;

		Sound m_shootSound;

		bool m_canJump;
		float m_bulletTimer;
		float m_reloadTimer;
	public:
		int ammo;
		std::vector<std::unique_ptr<Bullet>> bullets;
	public:
		Player(float x, float y);

		void MoveUp(float y);

		void Reset();

		void Update();
	};
}