#pragma once
#include <SFML/Graphics.hpp>
#include "PlayableCharacter.h"
#include "Item.h"

using namespace sf;
#define MAX_NUMBER_OF_ITEMS 3

struct Vector2uComp {
	bool operator()(const Vector2u& lhs, const Vector2u& rhs) const{ return (lhs.x == rhs.x) ? lhs.y < rhs.y : lhs.x < rhs.x; };
};

class ItemSlot : public Drawable {
public:
	ItemSlot(std::shared_ptr<Item> item, std::unique_ptr<RectangleShape> box) : m_Item(item), m_Box(std::move(box)) {};
	std::shared_ptr<Item> m_Item;
	std::unique_ptr<RectangleShape> m_Box;
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const { 
		window.draw(*m_Box);
		if (m_Item != nullptr) {
			window.draw(*m_Item);
		}
	};
};

class Panel : public Drawable
{
public: 
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const = 0;
	virtual void update(PlayableCharacter&) = 0;
	virtual bool handleInput(Event& e) = 0;
	//std::unique_ptr<RectangleShape> m_PanelBox;
	Texture m_PanelTexture;
	Sprite m_PanelSprite;

};



class EquippedPanel : public Panel {
public:	
	EquippedPanel();
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;
	virtual void update(PlayableCharacter&);
	virtual bool handleInput(Event& e);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void select(Character::Piece);
	void deselect(Character::Piece);
	Character::Piece getSelectedItem();
	void EquippedPanel::updateSlot(PlayableCharacter&, Character::Piece);

	

private:
	std::unique_ptr<ItemSlot> makeSlot(Vector2f pos);
	View m_View;
	Text m_PanelLabel;
	Font m_Font;
	Vector2f m_Size;
	Vector2f m_SlotSize;
	std::map<const Character::Piece, std::unique_ptr<ItemSlot>> m_Equipped;
	Character::Piece m_Selected;
	//std::map<const Character::Piece, Vector2f> m_PositionMap;
	//Vector2f m_RHandPos;

};



class Menu : public Drawable
{

private:
	
	std::vector<sf::Text> m_Menu;

	EquippedPanel m_EquippedPanel;
	unsigned int m_Width;
	unsigned int m_Height;
	sf::View m_MenuView;
	Sprite m_MenuSprite;
	Texture m_MenuTexture;
	Panel *m_SelectedPanel;

public:
	Menu();
	unsigned int getWidth();
	unsigned int getHeight();
	void update(PlayableCharacter&);
	
	static const int MAX_Y = 5;
	static const int MAX_X = 5;

	

	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;
	bool handleInput(sf::RenderWindow &window);
};