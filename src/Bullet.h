#pragma once

#include <raylib.h>
#include <raymath.h>

#include "Entity.h"

namespace Engine
{
	class Bullet : public Entity
	{
	public:
		Bullet(float x, float y, float angle);

		void Update();		
	};
}