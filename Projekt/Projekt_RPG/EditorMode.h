#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class TileMap;
class Tile;

class EditorStateData
{
public:
    EditorStateData() {};

    sf::View* view;

    sf::Font* font;

    float* keytime;
    float* keytimeMax;

    std::map<std::string, int>* keybinds;

    sf::Vector2i* mousePositionScreen;
    sf::Vector2i* mousePositionWindow;
    sf::Vector2f* mousePositionView;
    sf::Vector2i* mousePositionGrid;
};

class EditorMode
{
private:


protected:
    StateData* stateData;
    EditorStateData* editorStateData;
    TileMap* tileMap;


public:
    EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EditorMode();

    const bool getKeytime();

    virtual void updateKeybinds(const float& dtime) = 0;
    virtual void updateGui(const float& dtime) = 0;
    virtual void update(const float& dtime) = 0;

    virtual void renderGui(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

#endif

