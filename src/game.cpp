#include "Game.h"

namespace Engine
{
	Game::Game(float width, float height, const char* title)
	{
		InitWindow(width, height, title);
		SetWindowState(FLAG_VSYNC_HINT);

		InitAudioDevice();

		SetRandomSeed(time(0));

		m_player = std::make_unique<Player>(400, 425);

		m_lava = std::make_unique<Lava>(width, height);

		m_trophy = std::make_unique<Entity>(2200, -870, 20, 20, "res/img/trophy.png");

		m_camera.target = {m_player->GetPosition().x, m_player->GetPosition().y};
		m_camera.offset = {width / 2, height / 2 + 10};
		m_camera.rotation = 0;
		m_camera.zoom = 1;

		m_blipSound = LoadSound("res/sound/blip.wav");
		m_loseSound = LoadSound("res/sound/lose.wav");
		m_winSound = LoadSound("res/sound/win.wav");

		Reset();

		m_delayTimer = 1.5;

		m_bulletTexture = LoadTexture("res/img/bullet.png");
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			UpdateLoop();

			BeginDrawing();

				DrawLoop();

			EndDrawing();
		}

		CloseAudioDevice();
		CloseWindow();
	}

	void Game::LoadStage()
	{
		m_player->SetPosition(400, 425);
		m_floors.push_back(std::make_unique<Floor>(400,   450));
		m_floors.push_back(std::make_unique<Floor>(700,   450));
		m_floors.push_back(std::make_unique<Floor>(1100,  300));
		m_floors.push_back(std::make_unique<Floor>(800,   150));
		m_floors.push_back(std::make_unique<Floor>(1150, -50));
		m_floors.push_back(std::make_unique<Floor>(1400, -50));
		m_floors.push_back(std::make_unique<Floor>(1650, -200));
		m_floors.push_back(std::make_unique<Floor>(1400, -400));
		m_floors.push_back(std::make_unique<Floor>(1100, -650));
		m_floors.push_back(std::make_unique<Floor>(1600, -800));
		m_floors.push_back(std::make_unique<Floor>(1900, -700));
		m_floors.push_back(std::make_unique<Floor>(2200, -800));
		m_floors.push_back(std::make_unique<Floor>(2400, -950));
		m_floors.push_back(std::make_unique<Floor>(2250, -1100));
		m_floors.push_back(std::make_unique<Floor>(2450, -1250));
		m_floors.push_back(std::make_unique<Floor>(2750, -1250));
		m_floors.push_back(std::make_unique<Floor>(3000, -1400));
		m_floors.push_back(std::make_unique<Floor>(2700, -1550));
		m_floors.push_back(std::make_unique<Floor>(2500, -1700));
		m_floors.push_back(std::make_unique<Floor>(2300, -1850));
		m_floors.push_back(std::make_unique<Floor>(2100, -2000));
		m_floors.push_back(std::make_unique<Floor>(1800, -2200));
		m_floors.push_back(std::make_unique<Floor>(1300, -2400));
		m_trophy->SetPosition(1300, -2450);
	}

	void Game::Reset()
	{
		m_delayTimer = 0;
		m_hasWin = false;
		m_hasLose = false;
		m_seconds = 0;
		m_lava->StopMoving();
		m_player->Reset();
		m_lava->Reset();
		m_floors.clear();
		m_player->bullets.clear();
		m_currentScreen = TITLE;
		m_floors.push_back(std::make_unique<Floor>(210, 423));
		m_floors.push_back(std::make_unique<Floor>(480, 440));
	}

	void Game::Win()
	{
		m_winTimer += GetFrameTime();

		m_lava->StopMoving();
		m_player->SetPosition(Lerp(m_player->GetPosition().x, m_trophy->GetPosition().x, 50 * GetFrameTime()), Lerp(m_player->GetPosition().y, m_trophy->GetPosition().y, 50 * GetFrameTime()));
		m_hasWin = true;

		if (m_winTimer > 5)
		{
			m_winTimer = 0;
			PlaySound(m_blipSound);
			Reset();
		}
	}

	void Game::Lose()
	{
		m_loseTimer += GetFrameTime();

		m_lava->StopMoving();
		m_player->SetPosition(Lerp(m_player->GetPosition().x, m_lava->GetPosition().x, 50 * GetFrameTime()), Lerp(m_player->GetPosition().y, m_lava->GetPosition().y - 300, 50 * GetFrameTime()));
		m_hasLose = true;

		if (m_loseTimer > 5)
		{
			m_loseTimer = 0;
			PlaySound(m_blipSound);
			Reset();
		}
	}

	void Game::UpdateLoop()
	{
		switch (m_currentScreen)
		{
		case TITLE:
		{
			m_delayTimer += GetFrameTime();

			if (IsMouseButtonPressed(0) && m_delayTimer >= 1.5)
			{
				m_floors.clear();
				LoadStage();
				m_camera.target = {m_player->GetPosition().x, m_player->GetPosition().y};
				
				PlaySound(m_blipSound);
				m_currentScreen = GAMEPLAY;
				m_delayTimer = 0;
			}
		} break;
		case GAMEPLAY:
		{
			if (!m_hasWin && !m_hasLose)
				m_seconds += GetFrameTime();

			m_camera.target = Vector2Lerp(m_camera.target, m_player->GetPosition(), 10 * GetFrameTime());

			if (!m_hasWin && !m_hasLose)
			{
				m_player->Update();
			}

			m_lava->Update(m_player->GetPosition().x);

			if (CheckCollisionRecs(m_player->GetCollider(), m_lava->GetCollider()))
			{
				if (!m_hasLose)
				{
					PlaySound(m_loseSound);
				}

				Lose();
			}

			if (CheckCollisionRecs(m_player->GetCollider(), m_trophy->GetCollider()))
			{
				if (!m_hasWin)
				{
					PlaySound(m_winSound);
				}

				Win();
			}

			for (auto& bullet : m_player->bullets)
			{
				bullet->Update();
			}

			for (auto& floor : m_floors)
			{
				if (CheckCollisionRecs(m_player->GetCollider(), floor->GetCollider()))
				{
					m_player->MoveUp(floor->GetPosition().y);
				}
			}
		} break;
		}
	}

	void Game::DrawLoop()
	{
		ClearBackground(BLACK);

		switch (m_currentScreen)
		{
		case TITLE:
		{
			DrawText("Micro Jumper", 250, 140, 64, WHITE);
			DrawText("Click To Start!", 360, 400, 32, WHITE);

			m_player->Render();
			m_player->SetPosition(210, 405);

			for (auto& floor : m_floors)
			{
				floor->Render();
			}
		} break;
		case GAMEPLAY:
		{
			BeginMode2D(m_camera);

				m_player->Render();

				m_trophy->Render();

				for (auto& bullet : m_player->bullets)
				{
					bullet->Render();
				}

				for (auto& floor : m_floors)
				{
					floor->Render();
				}

				m_lava->RenderParticles();
				m_lava->Render();

			EndMode2D();

			if (m_hasWin)
			{
				DrawRectangle(GetScreenWidth() / 4, GetScreenHeight() / 4, GetScreenWidth() / 2, GetScreenHeight() / 2, WHITE);
				DrawText("You Win!", 320, 240, 64, BLACK);
			}
			else if (m_hasLose)
			{
				DrawRectangle(GetScreenWidth() / 4, GetScreenHeight() / 4, GetScreenWidth() / 2, GetScreenHeight() / 2, WHITE);
				DrawText("You Lose!", 300, 240, 64, BLACK);
			}
			
			std::string ammoText = std::to_string(m_player->ammo) + "/3";
			DrawText(ammoText.c_str(), 8, GetScreenHeight() - 32, 32, WHITE);
			DrawTexture(m_bulletTexture, 8 + 32 * 2, GetScreenHeight() - 34, WHITE);

			std::string stopwatch = "Time: " + std::to_string((int)m_seconds);
			DrawText(stopwatch.c_str(), 8, 10, 32, WHITE);
		} break;
		}
	}
}