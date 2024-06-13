#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "PlayerGUITabs.h"

class PlayerGUI
{
private:
    Player* player;

    sf::VideoMode& vm;
    sf::Font font;

    //Bar
    sf::Texture textureBar;
    sf::RectangleShape Bar;

    //Level Bar
    std::string levelBarString;
    sf::Text levelBarText;
    sf::RectangleShape levelBarBack;


    //EXP Bar
    std::string expBarString;
    sf::Text expBarText;
    float expBarMaxWidth;
    sf::RectangleShape expBarBack;
    sf::RectangleShape expBarInner;

    //HP Bar
    //gui::ProgressBar* hpBar;
    std::string hpBarString;
    sf::Text hpBarText;
    float hpBarMaxWidth;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;

    PlayerGUITabs* playerTabs;

    void initTextureBar();
    void initFont();
    void initLevelBar();
    void initExpBar();
    void initHpBar();
    void initPlayerTabs(sf::VideoMode vm, sf::Font& font, Player& player);

public:
    PlayerGUI(Player* player, sf::VideoMode& vm);
    virtual ~PlayerGUI();

    const bool getTabsOpen() const;
    void toggleCharacterTab();

    void updateLevelBar();
    void updateExpBar();
    void updateHpBar();
    void updatePlayerTabs();

    void update(const float& dtime);

    void renderTexureBar(sf::RenderTarget& target);
    void renderLevelBar(sf::RenderTarget& target);
    void renderExpBar(sf::RenderTarget& target);
    void renderHpBar(sf::RenderTarget& target);
    void renderPlayerTabs(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

#endif
