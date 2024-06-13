#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Gui.h"
#include "SettingsState.h"
#include "EditorState.h"
#include "Game.h"

class MainMenuState :
    public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape backgroud;
    sf::Font font;
    sf::Music music;

    sf::RectangleShape btnBackground;
    std::map<std::string, gui::Button*> buttons;

    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initMusic();
    void resetGui();

public:

    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions
    void updateKeybinds(const float& dtime);
    void upadteButtons();
    void playMusic();
    void stopMusic();
    void renderButtons(sf::RenderTarget& target);
    void update(const float& dtime);
    void render(sf::RenderTarget* target = nullptr);
};

#endif