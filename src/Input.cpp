#include "Engine.h"

void Engine::input()
{
	Event event;
	if (!m_InMenu) {
		while (m_Window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:
					m_Window.close();
					break;
				case Keyboard::Return:
					m_Playing = true;
					break;
				case Keyboard::Q:
					m_InMenu = true;
					break;
				}
			}
		}
	}
	else {
		m_InMenu = m_Menu.handleInput(m_Window);
	}

	// Handle input specific to Thomas
	if (m_Thomas.handleInput())
	{
		// Play a jump sound
		m_SM.playJump();
	}

}