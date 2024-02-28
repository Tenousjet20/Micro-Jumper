#pragma once

#include <raylib.h>

#include "Entity.h"

namespace Engine
{
	class Floor : public Entity
	{
	public:
		Floor(float x, float y);
	};
}