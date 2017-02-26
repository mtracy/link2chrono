#include "stdafx.h"
#include "Environment.h"
#include <sstream>
#include <fstream>
#include <iostream>
//#include <string>

Vector2i Environment::getLevelSize()
{
	return m_LevelSize;
}

void Environment::clearLevel() {
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		delete[] m_Scaffolding[i];
		delete[] m_Activatables[i];

	}
	delete[] m_Scaffolding;
	delete[] m_Activatables;
}

Scaffold intToScaffold(int i) {
	switch (i)
	{
	case 0:
		return Scaffold(false, 0);
		break;
	case 1:
		return Scaffold(true, 1);
		break;
	case 2:
		return Scaffold(false, 2);
		break;
	case 3:
		return Scaffold(false, 3);
		break;
	default:
		return Scaffold(false, 0);
		break;
	}
}

Activatable *intToObject(int i, size_t x, size_t y) {
	if (i == 1) {
		return new Chest(std::unique_ptr<Potion>(new Potion()), Vector2u(x, y));
		//chest->setContents(std::move(potion));
		//return chest;
	}
	else {
		return nullptr;
	}
}


Vector2f Environment::getStartPosition()
{
	return m_StartPosition;
}

void Environment::loadScaffold() {
	auto& rVaLevel = m_VScaff;
	using namespace std;

	m_LevelSize.x = 0;
	m_LevelSize.y = 0;


	// Load the appropriate level from a text file
	string levelToLoad("levels/1/scaffold.txt");
	m_StartPosition.x = 100;
	m_StartPosition.y = 100;

	ifstream inputFile(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	Scaffold** arrayLevel = new Scaffold*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new Scaffold[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (size_t x = 0; x < row.length(); x++) {
			const char val = row[x];
			arrayLevel[y][x] = intToScaffold(atoi(&val));
		}

		y++;
	}

	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position =
				Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 1].position =
				Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 2].position =
				Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 3].position =
				Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x].getTextureOffset() * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords =
				Vector2f(0, 0 + verticalOffset);

			rVaLevel[currentVertex + 1].texCoords =
				Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVaLevel[currentVertex + 2].texCoords =
				Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVaLevel[currentVertex + 3].texCoords =
				Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	m_Scaffolding = arrayLevel;
}

void Environment::loadOjects(){
	using namespace std;
	string levelToLoad("levels/1/objects.txt");
	m_Activatables = new Activatable**[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		m_Activatables[i] = new Activatable*[m_LevelSize.x];
	}

	ifstream inputFile(levelToLoad);
	string row;
	size_t y = 0;
	while (inputFile >> row)
	{
		for (size_t x = 0; x < row.length(); x++) {
			const char val = row[x];
			m_Activatables[y][x] = intToObject(atoi(&val), x, y);
		}

		y++;
	}
	inputFile.close();

	// What type of primitive are we using?
	m_VActiv.setPrimitiveType(Quads);

	// Set the size of the vertex array
	m_VActiv.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			if (m_Activatables[y][x] != nullptr) {
				std::cout << currentVertex << std::endl;
				// Position each vertex in the current quad
				m_VActiv[currentVertex + 0].position =
					Vector2f(x * TILE_SIZE, y * TILE_SIZE);

				m_VActiv[currentVertex + 1].position =
					Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

				m_VActiv[currentVertex + 2].position =
					Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

				m_VActiv[currentVertex + 3].position =
					Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

				// Which tile from the sprite sheet should we use
				// int verticalOffset = arrayLevel[y][x].getTextureOffset() * TILE_SIZE;

				m_VActiv[currentVertex + 0].texCoords =
					Vector2f(0, 0);

				m_VActiv[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, 0);

				m_VActiv[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE);

				m_VActiv[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE);
				
			}
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
}

void Environment::setObjectVertexTexture(Vector2u position, IntRect f) {
	size_t currentVertex = position.x * m_LevelSize.y + position.y;
	currentVertex *= VERTS_IN_QUAD;
	std::cout << currentVertex << std::endl;
	m_VActiv[currentVertex + 0].texCoords =
		Vector2f(f.left, f.top - f.height);

	m_VActiv[currentVertex + 1].texCoords =
		Vector2f(f.left + f.width, f.top - f.height);

	m_VActiv[currentVertex + 2].texCoords =
		Vector2f(f.left + f.width, f.top);

	m_VActiv[currentVertex + 3].texCoords =
		Vector2f(f.left, f.top);
}

void Environment::loadLevel() {
	loadScaffold();
	loadOjects();
}