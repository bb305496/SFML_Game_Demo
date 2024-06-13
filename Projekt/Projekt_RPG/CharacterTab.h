#ifndef CHARACTERTAB_H
#define CHARACTERTAB_H

#include "Tab.h"

class CharacterTab
    : public Tab
{
private:
    sf::Texture statsTab;
    sf::RectangleShape tab;
    sf::RectangleShape back;
    sf::Text infoText;

    void initCharacterTabTexture();
    void initBack();
    void initText();


public:
    CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player);
    virtual ~CharacterTab();

    void update();
    void render(sf::RenderTarget& target);
};

#endif

