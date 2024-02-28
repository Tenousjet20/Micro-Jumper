#include "Player.h"

namespace Engine
{
	const float PLAYER_SPEED = 205;
	const float PLAYER_ACCELERATION = 1200;
	const float PLAYER_GRAVITY_FORCE = 500;
	const float PLAYER_ADDITIONAL_GRAVITY_FORCE = 50;
	const float PLAYER_MAX_AMMO = 3;

	Player::Player(float x, float y)
		: Entity{x, y, 25, 25, "res/img/player.png"}
	{
		m_velocity = Vector2Zero();

		m_gravity = 0;

		m_shootSound = LoadSound("res/sound/shoot.wav");

		m_bulletTimer = 0;
		m_reloadTimer = 0;

		ammo = PLAYER_MAX_AMMO;
	}

	void Player::MoveUp(float y)
	{
		m_position.y = Lerp(m_position.y, y - m_dst.height + 5, 9 * GetFrameTime());
		m_gravity = 0;
		m_canJump = true;
		m_src.x = 0;
	}

	void Player::Reset()
	{
		m_src.x = 0;
		m_position.x = 400;
		m_position.y = 425;
		m_gravity = 0;
		m_src.width = 25;
		m_velocity = Vector2Zero();
		m_bulletTimer = 0;
		m_reloadTimer = 0;
		ammo = PLAYER_MAX_AMMO;
	}

	void Player::Update()
	{
		m_gravity += PLAYER_GRAVITY_FORCE * GetFrameTime();
		m_gravity = Clamp(m_gravity, -1000, 1000);

		if (m_gravity > 0)
		{
			m_gravity += PLAYER_ADDITIONAL_GRAVITY_FORCE * GetFrameTime();
		}

		if (IsKeyDown(KEY_D))
		{
			m_velocity = Vector2MoveTowards(m_velocity, {PLAYER_SPEED, 0}, PLAYER_ACCELERATION * GetFrameTime());
			m_src.width = 25;
		}
		else if (IsKeyDown(KEY_A))
		{
			m_velocity = Vector2MoveTowards(m_velocity, {-PLAYER_SPEED, 0}, PLAYER_ACCELERATION * GetFrameTime());
			m_src.width = -25;
		}
		else
		{
			m_velocity = Vector2MoveTowards(m_velocity, Vector2Zero(), PLAYER_ACCELERATION * GetFrameTime());
		}

		if (IsKeyDown(KEY_SPACE) && m_canJump && m_gravity < 170)
		{
			m_gravity = -300;
			m_canJump = false;
		}

		m_bulletTimer += GetFrameTime();

		if (ammo < PLAYER_MAX_AMMO)
		{
			m_reloadTimer += GetFrameTime();

			if (m_reloadTimer > 1)
			{
				ammo++;
				m_reloadTimer = 0;
			}
		}

		if (IsMouseButtonPressed(0) && ammo > 0 && m_bulletTimer > 0.4)
		{
			m_gravity = -300;
			m_src.x = 25;

			bullets.push_back(std::make_unique<Bullet>(m_position.x, m_position.y, 90));
			m_reloadTimer = 0;

			ammo--;
			m_bulletTimer = 0;
			PlaySound(m_shootSound);
		}

		m_position.x += m_velocity.x * GetFrameTime();
		m_position.y += m_gravity * GetFrameTime();
	}
}