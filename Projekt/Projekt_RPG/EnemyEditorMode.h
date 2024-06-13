#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class EnemySpawnerTile;

class EnemyEditorMode :
    public EditorMode
{
private:
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    sf::IntRect textureRect;

    int type;
    int amount;
    int timeToSpawn;
    float maxDistance;

    void initVariables();
    void initGui();

public:
    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();


    void updateKeybinds(const float& dtime);
    void updateGui(const float& dtime);
    void update(const float& dtime);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

#endif

