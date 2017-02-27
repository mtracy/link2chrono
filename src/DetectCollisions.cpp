#include "Engine.h"
#include <iostream>

bool Engine::detectCollisions(Character& character, float dtAsSeconds)
{
	bool reachedGoal = false;
	FloatRect feetZone = character.getFeet();
	FloatRect headZone = character.getHead();
	FloatRect leftZone = character.getLeft();
	FloatRect rightZone = character.getRight();
	auto mos = m_Env.getIntersects(character.getPosition());
	std::unique_ptr<sf::FloatRect> fr;
	//std::cout <<  << std::endl;

	for(auto mo : mos)
	{	
    	if(mo->GetParent() == "collision")
    	{    		
    		fr = m_Env.convertToFloatRect(mo);
    		if (fr->intersects(feetZone)) {
        		character.stopDir(Character::Dir::Down, dtAsSeconds);
        	}
        	if (fr->intersects(headZone)) {
        		character.stopDir(Character::Dir::Up, dtAsSeconds);
        	}
        	if (fr->intersects(leftZone)) {
        		character.stopDir(Character::Dir::Left, dtAsSeconds);
        	}
        	if (fr->intersects(rightZone)) {
        		character.stopDir(Character::Dir::Right, dtAsSeconds);
        	}
	    }
	}
	

	/*
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;
			tiletype = 0; //m_Env.m_Scaffolding[y][x].getTextureOffset();
			solidtile = false; //m_Env.m_Scaffolding[y][x].getIsSolid();

			if (solidtile == 1)
			{

				auto trajectory = character.getTrajectory();
				if (character.getRight().intersects(block))
				{
					character.stopDir(Character::Dir::Right, dtAsSeconds);
				}
				if (character.getLeft().intersects(block))
				{
					character.stopDir(Character::Dir::Left, dtAsSeconds);
				}
				if (character.getHead().intersects(block))
				{
					character.stopDir(Character::Dir::Up, dtAsSeconds);
				}
				if (character.getFeet().intersects(block))
				{
					character.stopDir(Character::Dir::Down, dtAsSeconds);

				}

			}

		}

	}
	*/

	// All done, return, wheteher or not a new level might be required
	return reachedGoal;
}