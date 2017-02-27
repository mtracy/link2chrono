#include "Thomas.h"
#include "TextureHolder.h"
#include "Armor.h"

Thomas::Thomas(Engine *eng)
{
	// Associate a texture with the sprite
	m_Speed = 400;
	m_Health = 100;
	m_IsAlive = true;
	m_Eng = eng;

	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/characters/mychar.png"));

	m_UpPosition = IntRect(0, 4 * 64, 64, 64);
	m_DownPosition = IntRect(0, 6 * 64, 64, 64);
	m_LeftPosition = IntRect(0, 5 * 64, 64, 64);
	m_RightPosition = IntRect(0, 7 * 64, 64, 64);

	m_Sprite.setTextureRect(m_DownPosition);
	m_Origin = Vector2f(32, 32);
	m_Inventory.addWeapon(std::shared_ptr<Weapon>(new Melee()));
	m_Inventory.addArmor(std::shared_ptr<Armor>(new HeadArmor()));
	m_Inventory.addArmor(std::shared_ptr<Armor>(new ChestArmor()));
	m_Inventory.addArmor(std::shared_ptr<Armor>(new FeetArmor()));
	m_Inventory.addArmor(std::shared_ptr<Armor>(new Shield()));
	setRHItem(m_Inventory.getWeapon(0));
	setHeadItem(m_Inventory.getArmor(0));
	setChestItem(m_Inventory.getArmor(1));
	setFeetItem(m_Inventory.getArmor(2));
	setLHItem(m_Inventory.getArmor(3));
	setName("Phillip");
}

// A virtual function
bool Thomas::handleInput()
{

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_UpPressed = true;
	}
	else
	{
		m_UpPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_DownPressed = true;
	}
	else
	{
		m_DownPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		m_EPressed = true;
	}
	else
	{
		m_EPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) )
	{		
		m_SpacePressed = true;
	}
	else
	{
		m_SpacePressed = false;
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		m_Num1Pressed = true;
	}
	else
	{
		m_Num1Pressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		m_Num2Pressed = true;
	}
	else
	{
		m_Num2Pressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		m_Num3Pressed = true;
	}
	else
	{
		m_Num3Pressed = false;
	}

	return false;
}