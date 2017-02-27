#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);
	
	// Update the shader parameters
	//m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

	if (m_Playing)
	{
		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Draw the background, complete with shader effect
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		// Switch to m_MainView
		m_Window.setView(m_MainView);		

		// Draw the Level
		m_Window.draw(m_Env);
		//m_Window.draw(m_Env.m_VActiv, &m_ObjectTiles);

		// Draw thomas
		m_Window.draw(m_Thomas.getSprite());
		for (auto chariter = m_Chars.begin(); chariter != m_Chars.end(); chariter++)
		{
			m_Window.draw((*chariter)->getSprite());
		}

		for (auto i = m_Projectiles.begin(); i != m_Projectiles.end(); i++)
		{
			m_Window.draw((*i)->getDrawable());
		}

		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}

		if (m_InMenu)
		{
			m_Window.draw(m_Menu);
		}
		else {
			m_Window.setView(m_HudView);
			m_Window.draw(m_Hud.getLevel());
			m_Window.draw(m_Hud.getTime());
		}

	}

	// Draw the HUD
	// Switch to m_HudView
	
	if (!m_Playing)
	{
		m_Window.draw(m_Hud.getMessage());
	}
	
	
	// Show everything we have just drawn
	m_Window.display();
}