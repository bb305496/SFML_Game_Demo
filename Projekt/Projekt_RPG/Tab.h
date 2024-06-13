#ifndef TAB_H
#define TAB_H

#include "Gui.h";
#include "Player.h"

class Tab
{
protected:
    sf::VideoMode& vm;
    sf::Font& font;
    Player& player;
    bool hidden;

public:
    Tab(sf::VideoMode& vm, sf::Font& font, Player& player, bool hidden);
    virtual ~Tab();

    const bool& getHiddem() const;
    const bool& getOpen() const;
    void toogle();

    void hide();
    void show();
    
    virtual void update() = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

#endif

