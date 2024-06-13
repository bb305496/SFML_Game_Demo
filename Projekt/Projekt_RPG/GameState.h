#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Bow.h"
#include "Enemy.h"
#include "TextTagSystem.h"

class GameState :  public State
{
private:
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    sf::Music music;

    std::map<std::string, sf::Texture> texture;

    sf::Font font;
    PauseMenu* pmenu;

    sf::Shader core_shader;

    sf::Clock keyTimer;
    float keyTimeMax;

    Player* player;
    PlayerGUI* playerGUI;

    std::vector<Enemy*> activeEnemies;
    EnemySystem* enemySystem;

    TileMap* tileMap;

    TextTagSystem* tts;

    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initShaders();
    void initKeyTime();
    void initPlayers();
    void initPlayerGUI();
    void initEnemySystem();
    void initTileMap();
    void initSystems();
    void initMusic();


public:
    GameState(StateData* state_data);
    virtual ~GameState();

    const bool getKeyTime();

    void resetPlayerPositionAndHealth();

    //Functions
    void updateView(const float& dtime);
    void updateKeybinds(const float& dtime);
    void updatePlayerKeybinds(const float& dtime);
    void updatePlayerGUI(const float& dtime);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dtime);
    void updatePlayer(const float& dtime);
    void updateCombatAndEnemies(const float& dtime);
    template<typename U>
    requires std::integral<U>
    void updateCombat(Enemy* enemy, U index, const float& dtime);
    void update(const float& dtime);
    void render(sf::RenderTarget* target = nullptr);

};
#endif
