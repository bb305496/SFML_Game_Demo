#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState :
    public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape backgroud;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropdownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    void updateKeybinds(const float& dtime);
    void upadteGui(const float& dtime);
    void renderGui(sf::RenderTarget& target);
    void update(const float& dtime);
    void render(sf::RenderTarget* target = nullptr);
};

#endif

