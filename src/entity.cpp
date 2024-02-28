#include "Entity.h"

namespace Engine
{
	Entity::Entity(float x, float y, float w, float h, const char* file)
	{
		m_texture = LoadTexture(file);

		m_position = {x, y};

		m_src = {0, 0, w, h};
		m_dst = {m_position.x, m_position.y, w, h};
		m_collider = {m_position.x - w / 2, m_position.y - h / 2, w, h};

		m_angle = 0;

		m_color = {255, 255, 255, 255};
	}

	void Entity::SetPosition(float x, float y)
	{
		m_position = {x, y};
	}

	Vector2 Entity::GetPosition()
	{
		return m_position;
	}

	Rectangle Entity::GetCollider()
	{
		return m_collider;
	}

	void Entity::Render()
	{
		m_dst.x = m_position.x;
		m_dst.y = m_position.y;
		m_collider = {m_position.x - m_dst.width / 2, m_position.y - m_dst.height / 2, m_dst.width, m_dst.height};

		DrawTexturePro(m_texture, m_src, m_dst, {m_dst.width / 2, m_dst.height / 2}, m_angle, m_color);
	}
}