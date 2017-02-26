#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

bool checkHit(Projectile& proj, Character& charac)
{

	bool hit = proj.getDrawable().getGlobalBounds().intersects(charac.getHitBox());

	if (hit && (&charac != &(proj.getOwner()) || proj.getCanDmgSelf()))
	{

		auto charachealth = charac.setHealth(charac.getHealth() - proj.getImpactDmg());
		if (charachealth <= 0)
		{
			charac.setAlive(false);
		}


	}
	else
	{
		hit = false;
	}
	return hit;
}

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		loadLevel();
		
	}

	// if playing and not in menu then process game elements
	if (m_Playing && !m_InMenu)
	{
		// get the mouse position
		mouseScreenPosition = Mouse::getPosition();

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = m_Window.mapPixelToCoords(
			Mouse::getPosition(), m_MainView);

		// update the main player
		m_Thomas.update(dtAsSeconds);
		
		int count = 0;

		// update all the other characters
		for (auto chariter = m_Chars.begin(); chariter != m_Chars.end(); chariter++)
		{
			(*chariter)->update(dtAsSeconds);
		}

		bool singlehit = true;
		bool hit = false;

		// process all the active projectiles
		for (auto projiter = m_Projectiles.begin(); projiter != m_Projectiles.end(); count++)
		{

			// the current projectile has not hit anything
			hit = false; 
			// check all of the other characters first
			for (auto chariter = m_Chars.begin(); !hit && chariter != m_Chars.end(); chariter++)
			{
				// checkHit will modify the health of the hit player and return true on a legit hit
				hit = checkHit(**projiter, **chariter);
			}
			// if the current projectile hasn't hit anything yet
			if (!hit)
			{
				// see if it hit the main character
				hit = checkHit(**projiter, m_Thomas);
			}

			// if the projectile hit something or reached its max range then remove it.
			if (hit || (*projiter)->update(dtAsSeconds))
			{
				//std::cout << "deleting potion " << count << std::endl;
				projiter = m_Projectiles.erase(projiter);
			}
			else
			{
				projiter++;
			}

		}

		// check if the main player ran in to anything
		detectCollisions(m_Thomas, dtAsSeconds);

		// check all of the other characters
		for (auto chariter = m_Chars.begin(); chariter != m_Chars.end(); chariter++)
		{
			detectCollisions(**chariter, dtAsSeconds);
		}
		

	} // End if playing

	

	// Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}
		
	m_MainView.setCenter(m_Thomas.getCenter());

	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		m_Hud.updateHUD(m_TimeRemaining, m_Thomas);
		m_Menu.update(m_Thomas);
		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}// End of update function
