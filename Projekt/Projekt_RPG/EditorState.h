#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorModes.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EnemyEditorMode;
class EditorStateData;

enum EditorModes { DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE };

class EditorState :
    public State
{
private:
    EditorStateData editorStateData;

    sf::View view;
    float cameraSpeed;

    sf::Font font;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;
    
    std::vector<EditorMode*> modes;
    unsigned activeMode;

    void initVariables();
    void initEditorStateData();
    void initView();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();
    void initModes();

public:

    EditorState(StateData* state_data);
    virtual ~EditorState();


    //Functions
    void updateKeybinds(const float& dtime);
    void updateEditorInput(const float& dtime);
    void upadteButtons();
    void updateGui(const float& dtime);
    void updatePauseMenuButtons();
    void updateModes(const float& dtime);
    void update(const float& dtime);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void renderModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
