#pragma once
#include "Scaffold.h"
#include "Activatable.h"
#include <SFML/Graphics.hpp>

class Environment {
public:
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	void clearLevel();
	Scaffold** m_Scaffolding;
	VertexArray m_VScaff;
	Activatable*** m_Activatables;	
	VertexArray m_VActiv;
	Vector2i getLevelSize();
	Vector2i m_LevelSize;
	Vector2f getStartPosition();
	Vector2f m_StartPosition;
	void loadLevel();
	void setObjectVertexTexture(Vector2u, IntRect);

private:
	void loadScaffold();
	void loadOjects();
};