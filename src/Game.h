#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <memory>
#include <string>
#include <time.h>

#include "Player.h"
#include "Floor.h"
#include "Bullet.h"
#include "Lava.h"

namespace Engine
{
	enum Screen
	{
		TITLE = 0,
		GAMEPLAY
	};

	class Game
	{
	private:
		std::unique_ptr<Player> m_player;
		std::unique_ptr<Lava> m_lava;
		std::unique_ptr<Entity> m_trophy;
		std::vector<std::unique_ptr<Floor>> m_floors;
		Camera2D m_camera;
		Screen m_currentScreen;
		Texture2D m_bulletTexture;

		Sound m_blipSound;
		Sound m_loseSound;
		Sound m_winSound;

		bool m_hasWin;
		float m_winTimer;
		bool m_hasLose;
		float m_loseTimer;

		float m_delayTimer;
		float m_seconds;
		float m_minutes;
	public:
		Game(float width, float height, const char* title);

		void Run();
	private:
		void LoadStage();
		void Reset();
		void Win();
		void Lose();
		void UpdateLoop();
		void DrawLoop();
	};
}