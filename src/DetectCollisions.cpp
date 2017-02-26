#include "Engine.h"
#include <iostream>

bool Engine::detectCollisions(Character& character, float dtAsSeconds)
{
	bool reachedGoal = false;
	// Make a rect for all his parts
	auto charOrigin = character.getOrigin();
	FloatRect detectionZone = character.getPosition();


	// Make a FloatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = (int)((detectionZone.left - charOrigin.x) / TILE_SIZE) - 1;
	int startY = (int)((detectionZone.top - charOrigin.y) / TILE_SIZE) - 1;
	int endX = (int)((detectionZone.left - charOrigin.x) / TILE_SIZE) + (int)(detectionZone.width / TILE_SIZE) + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = (int)((detectionZone.top - charOrigin.y) / TILE_SIZE) + (int)(detectionZone.height / TILE_SIZE) + 2;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	auto levelsize = m_Env.getLevelSize();
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= levelsize.x)
		endX = levelsize.x;
	if (endY >= levelsize.y)
		endY = levelsize.y;

	// Has the character fallen out of the map?
	FloatRect level(0, 0, levelsize.x * TILE_SIZE, levelsize.y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		// respawn the character
		//character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	int tiletype;
	bool solidtile;

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;
			tiletype = m_Env.m_Scaffolding[y][x].getTextureOffset();
			solidtile = m_Env.m_Scaffolding[y][x].getIsSolid();

			if (solidtile == 1)
			{

				auto trajectory = character.getTrajectory();
				if (character.getRight().intersects(block))
				{
					//std::cout << "right is hitting" << std::endl;
					character.stopDir(Character::Dir::Right, dtAsSeconds);
					/*
					if (1 * 3.1415 / 8 < trajectory && trajectory < 3 * 3.1415 / 8) {
						character.m_Position.y -= .5 * character.m_Speed * dtAsSeconds;
					} else if (13 * 3.1415 / 8 < trajectory && trajectory < 15 * 3.1415 / 8) {
						character.m_Position.y += .5 * character.m_Speed * dtAsSeconds;
					}*/
				}
				if (character.getLeft().intersects(block))
				{
					//std::cout << "left is hitting" << std::endl;
					character.stopDir(Character::Dir::Left, dtAsSeconds);
					/*
					if (5 * 3.1415 / 8 < trajectory && trajectory < 7 * 3.1415 / 8) {
						character.m_Position.y -= .5 * character.m_Speed * dtAsSeconds;
					}
					else if (9 * 3.1415 / 8 < trajectory && trajectory < 11 * 3.1415 / 8) {
						character.m_Position.y += .5 * character.m_Speed * dtAsSeconds;
					}*/
				}
				if (character.getHead().intersects(block))
				{
					//std::cout << "head is hitting" << std::endl;
					character.stopDir(Character::Dir::Up, dtAsSeconds);
					/*
					if (1 * 3.1415 / 8 < trajectory && trajectory < 3 * 3.1415 / 8) {
						character.m_Position.x += .5 * character.m_Speed * dtAsSeconds;
					}
					else if (5 * 3.1415 / 8 < trajectory && trajectory < 7 * 3.1415 / 8) {
						character.m_Position.x -= .5 * character.m_Speed * dtAsSeconds;
					}*/
				}
				if (character.getFeet().intersects(block))
				{
					character.stopDir(Character::Dir::Down, dtAsSeconds);
					/*
					if (9 * 3.1415 / 8 < trajectory && trajectory < 11 * 3.1415 / 8) {
						character.m_Position.x -= .5 * character.m_Speed * dtAsSeconds;
					}
					else if (13 * 3.1415 / 8 < trajectory && trajectory < 15 * 3.1415 / 8) {
						character.m_Position.x += .5 * character.m_Speed * dtAsSeconds;
					}*/
				}

			}


			// Is character colliding with a regular block

			
			// More collision detection here once we have learned about particle effects
			// Has the characters' feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this
			// by seeing if an effect is already running	
			/*
			if (!m_PS.running()) {
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block))
					{
						// position and start the particle system
						m_PS.emitParticles(character.getCenter());

					}
				}
			}

			// Has the character reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				// Character has reached the goal
				reachedGoal = true;
			}
			*/

		}

	}

	// All done, return, wheteher or not a new level might be required
	return reachedGoal;
}