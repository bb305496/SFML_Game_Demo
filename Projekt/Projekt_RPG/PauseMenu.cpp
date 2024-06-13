#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	: font(font)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(vm.width), 
		static_cast<float>(vm.height)));

	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(
		static_cast<float>(vm.width) / 4.f,
		static_cast<float>(vm.height)));

	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		0.f);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(gui::calcCharSize(vm));
	this->menuText.setString("PAUSED");
    this->menuText.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + gui::p2pY(1.851f, vm));
}

PauseMenu::~PauseMenu()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(
    const std::string key,
    const float y,
    const float width,
    const float height,
    const unsigned char_size, 
    const std::string text)
{

	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, char_size,
		sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void PauseMenu::update(const sf::Vector2i& mousePositionWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePositionWindow);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}