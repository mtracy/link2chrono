#include "Engine.h"
#include <sstream>
#include <iostream>


Engine::Engine()
	:m_Thomas(this)
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Thomas was late",
		Style::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_MainView.zoom(.5);
	m_HudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));
	

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}
	else
	{
		// Load two shaders (1 vertex, 1 fragment)
		m_RippleShader.loadFromFile("shaders/vertShader.vert",
			"shaders/rippleShader.frag");
	}

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/sky1.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");

	m_ObjectTiles = TextureHolder::GetTexture(
		"graphics/smallchest.png");

	// Initialize the particle system
	m_PS.init(1000);

	


}// End Engine constructor

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();

		const float time = 1.f / clock.getElapsedTime().asSeconds();
		//std::stringstream stream;
		//std::cout << "Current fps: " << time << std::endl;
		//m_Window.setTitle(stream.str());
	}
}

