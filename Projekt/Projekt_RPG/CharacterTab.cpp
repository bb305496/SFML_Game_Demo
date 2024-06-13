#include "stdafx.h"
#include "CharacterTab.h"

void CharacterTab::initText()
{
    this->infoText.setFont(this->font);
    this->infoText.setCharacterSize(gui::calcCharSize(this->vm, 70));
    this->infoText.setFillColor(sf::Color::White);
    this->infoText.setPosition(this->back.getPosition().x + gui::p2pX(4.f, this->vm), this->back.getPosition().y + gui::p2pY(6.f, this->vm));

    this->infoText.setString(this->player.toStringCharacterTab());
}

void CharacterTab::initCharacterTabTexture()
{
    this->tab.setSize(sf::Vector2f(gui::p2pX(22.f, this->vm), gui::p2pY(98.f, this->vm)));
    this->tab.setPosition(sf::Vector2f(gui::p2pX(77.f, this->vm), gui::p2pY(0.f, this->vm)));
    //this->statsTab.loadFromFile("Resources/Images/Tab/StatsTab.png");
    std::string textureFilePath = "Resources/Images/Tab/StatsTab1.png";
    if (std::filesystem::exists(textureFilePath)) {
        if (!this->statsTab.loadFromFile(textureFilePath)) {
            std::cout << "ERROR::CHARACTERTAB::COUDL NOT LOAD TEXTURE " << textureFilePath << "\n";
        }
    }
    else {
        std::cout << "ERROR::CHARACTERTAB " << textureFilePath << " does not exist." << "\n";
    }
    this->tab.setTexture(&this->statsTab);
}

void CharacterTab::initBack()
{
    this->back.setFillColor(sf::Color(191, 64, 191, 70));
    this->back.setSize(sf::Vector2f(gui::p2pX(18.f, this->vm), gui::p2pY(88.f, this->vm)));
    this->back.setPosition(sf::Vector2f(gui::p2pX(79.f, this->vm), gui::p2pY(4.f, this->vm)));
}

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player)
    : Tab(vm, font, player, true)
{
    this->initCharacterTabTexture();

    this->initBack();

    this->initText();
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{
    if (!this->hidden)
    {
        this->infoText.setString(this->player.toStringCharacterTab());
    }
}

void CharacterTab::render(sf::RenderTarget& target)
{
    if (!this->hidden)
    {
        target.draw(back);
        target.draw(infoText);
        target.draw(this->tab);
    }
}
