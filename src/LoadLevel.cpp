#include "stdafx.h"
#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	m_Env.clearLevel();

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_Env.loadLevel();

	// Prepare the sound emitters
	//populateEmitters(m_FireEmitters, m_ArrayLevel);

	// How long is this new time limit
	// Spawn Thomas and Bob
	m_Thomas.spawn(m_Env.getStartPosition());
	auto baddie = std::unique_ptr<Baddie>(new Baddie(this));
	baddie->spawn(Vector2f(200, 110));
	m_Chars.push_back(std::move(baddie));
	

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}