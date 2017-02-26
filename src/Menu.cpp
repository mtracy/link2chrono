#include "Menu.h"
#include "TextureHolder.h"
#include <iostream>

using namespace sf;
Menu::Menu()
{
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	m_Width = resolution.x;
	m_Height = resolution.y;

	m_MenuView.setSize(resolution);
	m_MenuView.reset(FloatRect(0, 0, resolution.x, resolution.y));
	m_MenuTexture = TextureHolder::GetTexture(
		"graphics/background-grey.png");

	m_MenuSprite.setTexture(m_MenuTexture);
	m_MenuSprite.setScale(resolution.x / m_MenuTexture.getSize().x, 
							resolution.y / m_MenuTexture.getSize().y);

	// Load the font

	// Paused

	m_SelectedPanel = &m_EquippedPanel;
}

unsigned int Menu::getWidth() {
	return m_Width;
}

unsigned int Menu::getHeight() {
	return m_Height;
}

void Menu::update(PlayableCharacter& charac) {

	m_EquippedPanel.update(charac);

}


void Menu::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.setView(m_MenuView);
	window.draw(m_MenuSprite);
	for (auto t : m_Menu)
	{
		window.draw(t);
	}

	window.draw(m_EquippedPanel);
	

}




bool Menu::handleInput(sf::RenderWindow &window) {

	Event event;
	//std::cout << "handling menu input" << std::endl;

	while (window.pollEvent(event))
	{
		//panel will return false on exit
		if (!m_SelectedPanel->handleInput(event)) {
			return false;
		}
	}
	return true;
}


std::unique_ptr<ItemSlot> EquippedPanel::makeSlot(Vector2f pos) {
	auto rs = std::unique_ptr<RectangleShape>(new RectangleShape());
	rs->setFillColor(sf::Color::White);
	rs->setSize(m_SlotSize);
	rs->setOrigin(Vector2f(m_SlotSize.x / 2, m_SlotSize.y / 2));
	rs->setPosition(pos.x, pos.y);
	auto noitem = std::shared_ptr<Item>();
	return std::unique_ptr<ItemSlot>(new ItemSlot(noitem, std::move(rs)));
}

EquippedPanel::EquippedPanel() {

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	float x_size_frac = 1 / 3.0;
	float y_size_frac = 5 / 6.0;
	float x_off_frac = 1 / 12.0;
	float y_off_frac = 1 / 12.0;

	m_View.reset(FloatRect(0, 0, x_size_frac * resolution.x, y_size_frac * resolution.y));
	m_View.setViewport(sf::FloatRect(.05, .1, x_size_frac, y_size_frac));

	m_Size = m_View.getSize();
	m_SlotSize = Vector2f(m_Size.x / 5.0, m_Size.y / 5.0);

	m_Font.loadFromFile("fonts/Roboto-Light.ttf");
	m_PanelLabel.setFont(m_Font);
	m_PanelLabel.setCharacterSize(100);
	m_PanelLabel.setColor(Color::Black);
	m_PanelLabel.setPosition(0, 0);
	m_PanelLabel.setString("Equipped");

	m_PanelTexture = TextureHolder::GetTexture(
		"graphics/steel.png");
	
	m_PanelSprite.setTexture(m_PanelTexture);
	m_PanelSprite.setScale(m_Size.x / m_PanelTexture.getSize().x,
		m_Size.y / m_PanelTexture.getSize().y);
	m_PanelSprite.setPosition(0, 0);

	m_Equipped[Character::HEAD] = makeSlot(Vector2f(m_Size.x / 2, m_Size.y / 5));
	m_Equipped[Character::CHEST] = makeSlot(Vector2f(m_Size.x / 2, m_Size.y * 2.5 / 5));
	m_Equipped[Character::RHAND] = makeSlot(Vector2f(m_Size.x / 4, m_Size.y * 2.5 / 5));
	m_Equipped[Character::LHAND] = makeSlot(Vector2f(m_Size.x * 3 / 4, m_Size.y * 2.5 / 5));
	m_Equipped[Character::FEET] = makeSlot(Vector2f(m_Size.x / 2, m_Size.y * 4 / 5));
	m_Selected = Character::HEAD;
	select(m_Selected);

}

void EquippedPanel::updateSlot(PlayableCharacter& charac, Character::Piece piece) {
	
	std::shared_ptr<Item> i;
	switch (piece)
	{
	case Character::HEAD:
		i = charac.getHeadItem();
		break;
	case Character::CHEST:
		i = charac.getChestItem();
		break;
	case Character::LHAND:
		i = charac.getLHItem();
		break;
	case Character::RHAND:
		i = charac.getRHItem();
		break;
	case Character::FEET:
		i = charac.getFeetItem();
		break;
	default:
		i = nullptr;
		break;
	}

	m_Equipped[piece]->m_Item = i;
	if (m_Equipped[piece]->m_Item) {
		auto position = m_Equipped[piece]->m_Box->getPosition();
		auto origin = m_Equipped[piece]->m_Box->getOrigin();
		auto texture_size = m_Equipped[piece]->m_Item->m_Sprite.getTexture()->getSize();
		
		// TODO: remove this once images are the correct size naturally
		m_Equipped[piece]->m_Item->m_Sprite.setScale(m_SlotSize.x / texture_size.x, m_SlotSize.y / texture_size.y);
		m_Equipped[piece]->m_Item->m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
		m_Equipped[piece]->m_Item->m_Sprite.setPosition(position);		
	}
}

void EquippedPanel::update(PlayableCharacter& charac) {

	updateSlot(charac, Character::HEAD);
	updateSlot(charac, Character::CHEST);
	updateSlot(charac, Character::LHAND);
	updateSlot(charac, Character::RHAND);
	updateSlot(charac, Character::FEET);
}

void EquippedPanel::draw(sf::RenderTarget &window, sf::RenderStates states) const {
	window.setView(m_View);	
	window.draw(m_PanelSprite);	
	window.draw(m_PanelLabel);

	for (auto i = m_Equipped.begin(); i != m_Equipped.end(); i++) {
		window.draw(*(i->second));
	}
}



void EquippedPanel::select(Character::Piece sel) {
	m_Equipped.at(sel)->m_Box->setFillColor(sf::Color::Red);
}

void EquippedPanel::deselect(Character::Piece sel) {
	m_Equipped.at(sel)->m_Box->setFillColor(sf::Color::White);
}



Character::Piece EquippedPanel::getSelectedItem() {
	return m_Selected;
}


bool EquippedPanel::handleInput(Event &event) {
	switch (event.type)
	{
	case Event::KeyReleased:
		switch (event.key.code)
		{
		case Keyboard::W:
			moveUp();
			break;
		case Keyboard::S:
			moveDown();
			break;
		case Keyboard::D:
			moveRight();
			break;
		case Keyboard::A:
			moveLeft();
			break;

		case Keyboard::Space:
			
			break;
		case Keyboard::Q:
			return false;
			break;
		default:
			//std::cout << "hit " << event.key.code << std::endl;
			break;
		}		
		break;
	}
	return true;
}

void EquippedPanel::moveUp() {
	switch (m_Selected)
	{
	case Character::HEAD:
		break;
	case Character::CHEST:
	case Character::LHAND:
	case Character::RHAND:
		deselect(m_Selected);
		m_Selected = Character::HEAD;
		select(m_Selected);
		break;
	case Character::FEET:
		deselect(m_Selected);
		m_Selected = Character::CHEST;
		select(m_Selected);
		break;
	default:
		break;
	}
}

void EquippedPanel::moveDown() {
	switch (m_Selected)
	{
	case Character::HEAD:
		deselect(m_Selected);
		m_Selected = Character::CHEST;
		select(m_Selected);
		break;
	case Character::CHEST:
	case Character::LHAND:
	case Character::RHAND:
		deselect(m_Selected);
		m_Selected = Character::FEET;
		select(m_Selected);
		break;
	case Character::FEET:
		break;
	default:
		break;
	}
}

void EquippedPanel::moveLeft() {
	switch (m_Selected)
	{
	case Character::HEAD:
	case Character::CHEST:
	case Character::FEET:
		deselect(m_Selected);
		m_Selected = Character::RHAND;
		select(m_Selected);
		break;	
	case Character::LHAND:	
		deselect(m_Selected);
		m_Selected = Character::CHEST;
		select(m_Selected);
		break;
	case Character::RHAND:
		break;
	default:
		break;
	}
}

void EquippedPanel::moveRight() {
	switch (m_Selected)
	{
	case Character::HEAD:
	case Character::CHEST:
	case Character::FEET:
		deselect(m_Selected);
		m_Selected = Character::LHAND;
		select(m_Selected);
		break;
	case Character::RHAND:
		deselect(m_Selected);
		m_Selected = Character::CHEST;
		select(m_Selected);
		break;
	case Character::LHAND:
		break;
	default:
		break;
	}
}