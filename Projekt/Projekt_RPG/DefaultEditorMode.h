#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode :
    public EditorMode
{
private:
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    gui::TextureSelector* textureSelector;
    sf::IntRect textureRect;
    bool collision;
    short type;
    int layer;
    bool tileAddLock;

    void initVariables();
    void initGui();

public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~DefaultEditorMode();

    void updateKeybinds(const float& dtime);
    void updateGui(const float& dtime);
    void update(const float& dtime);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

#endif
