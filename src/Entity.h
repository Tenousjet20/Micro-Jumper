#pragma once

#include <raylib.h>

namespace Engine
{
	class Entity
	{
	protected:
		Texture2D m_texture;
		Vector2 m_position;
		Rectangle m_src;
		Rectangle m_dst;
		Rectangle m_collider;
		float m_angle;
		Color m_color;
	public:
		Entity(float x, float y, float w, float h, const char* file);
		
		void SetPosition(float x, float y);

		Vector2 GetPosition();
		Rectangle GetCollider();

		void Render();
	};
}