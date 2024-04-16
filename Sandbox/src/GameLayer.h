#pragma once

#include "Fountainhead.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Fountainhead::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Fountainhead::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Fountainhead::Event& e) override;
	bool OnMouseButtonPressed(Fountainhead::MouseButtonPressedEvent& e);
	bool OnWindowResize(Fountainhead::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Fountainhead::Scope<Fountainhead::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};