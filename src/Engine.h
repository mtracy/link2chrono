#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "SoundManager.h"
#include "HUD.h"
#include "Menu.h"
#include "ParticleSystem.h"
#include "Projectile.h"
#include <memory>
#include "Baddie.h"
#include "Environment.h"


using namespace sf;

class Engine
{
private:
	
	
	// The texture holder
	TextureHolder th;

	// create a particle system
	ParticleSystem m_PS;

	// Where is the mouse in relation to world coordinates
	

	// Thomas and his friend, Bob
	Thomas m_Thomas;

	// Create a SoundManager
	SoundManager m_SM;

	// The Hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	// The Hud
	Menu m_Menu;

	static const int TILE_SIZE = 50;
	static const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 300;

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main View
	View m_MainView;

	// The view for the background
	View m_BGMainView;

	View m_HudView;



	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	// Declare a shader for the background
	Shader m_RippleShader;

	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	bool m_InMenu = false;


	// How much time is left in the current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	

	// The 2d array with the map for the level
	// A pointer to a pointer

	//Scaffold** m_ArrayLevel = NULL;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;
	Texture m_ObjectTiles;
	
	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();	

	// Load a new level
	void loadLevel();

	// Run will call all the private functions
	bool detectCollisions(Character& character, float dtAsSeconds);
	
	// Make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters,
		int** arrayLevel);

public:
	Environment m_Env;
	// A vector of Vector2f for the fire emiiter locations
	vector <Vector2f> m_FireEmitters;
	vector <unique_ptr<Projectile>> m_Projectiles;

	vector<unique_ptr<Baddie>> m_Chars;
	

	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;
	Character *getPlayer() {
		return &m_Thomas;
	}

	Activatable *getActive(int x, int y) {
		return m_Env.m_Activatables[y][x];
	}

	static const int getTileSize() {
		return TILE_SIZE;
	}

	void setObjectVertexTexture(Vector2u v, IntRect r) {
		m_Env.setObjectVertexTexture(v, r);
	}





};
