#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
    this->renderTexture.create(
        this->StataData->gfxSettings->resolution.width,
        this->StataData->gfxSettings->resolution.height);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(
        0, 
        0, 
        this->StataData->gfxSettings->resolution.width,
        this->StataData->gfxSettings->resolution.height));
}

void GameState::initView()
{
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->StataData->gfxSettings->resolution.width / 1.3),
        static_cast<float>(this->StataData->gfxSettings->resolution.height / 1.3)
        ));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->StataData->gfxSettings->resolution.width) / 2.f,
        static_cast<float>(this->StataData->gfxSettings->resolution.height) / 2.f
    ));
}

void GameState::initKeybinds()
{

	std::ifstream ifs("Config/game_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/alagard.ttf"))
	{
		throw("could not load font");
	}
}

void GameState::initTextures()
{
    auto loadPlayerSheet = []() {
        sf::Texture texture;
        texture.loadFromFile("Resources/Images/Sprites/Player/Final_man.png");
        return texture;
        };

    auto loadBug1Sheet = []() {
        sf::Texture texture;
        texture.loadFromFile("Resources/Images/Sprites/Enemy/BugAnim.png");
        return texture;
        };

    auto loadRat1Sheet = []() {
        sf::Texture texture;
        texture.loadFromFile("Resources/Images/Sprites/Enemy/RatAnim.png");
        return texture;
        };

    std::future<sf::Texture> playerSheetFuture = std::async(std::launch::async, loadPlayerSheet);
    std::future<sf::Texture> bug1SheetFuture = std::async(std::launch::async, loadBug1Sheet);
    std::future<sf::Texture> rat1SheetFuture = std::async(std::launch::async, loadRat1Sheet);

    this->texture["PLAYER_SHEET"] = playerSheetFuture.get();
    this->texture["BUG1_SHEET"] = bug1SheetFuture.get();
    this->texture["RAT1_SHEET"] = rat1SheetFuture.get();
}

void GameState::initPauseMenu()
{
    const sf::VideoMode& vm = this->StataData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->StataData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("EXIT", gui::p2pY(78.7037f, vm), gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm), gui::calcCharSize(vm), "Exit to main menu");
}

void GameState::initShaders()
{
    if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
    {
        std::cout << "ERROR::GAMESTATE:: could not load shaders" << "\n";
    }
}

void GameState::initKeyTime()
{
    this->keyTimeMax = 0.3f;
    this->keyTimer.restart();
}

void GameState::initPlayers()
{
	this->player = new Player(320, 300, this->texture["PLAYER_SHEET"]);
}

void GameState::initPlayerGUI()
{
    this->playerGUI = new PlayerGUI(this->player, this->StataData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
    this->enemySystem = new EnemySystem(this->activeEnemies, this->texture, *this->player);
}

void GameState::initTileMap()
{
    //this->tileMap = new TileMap(this->StataData->gridSize, 100, 100, "Resources/Images/Tiles/Tile1ch.png");
    this->tileMap = new TileMap("test.slmp");
}

void GameState::initSystems()
{
    this->tts = new TextTagSystem("Fonts/alagard.ttf");
}

void GameState::initMusic()
{
    this->music.openFromFile("Resources/Music/Game/Game.wav");
    music.play();
    music.setLoop(true);
}

GameState::GameState(StateData* state_data)
	: State(state_data)
{
    this->initDeferredRender();
    this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
    this->initShaders();
    this->initKeyTime();

	this->initPlayers();
    this->initPlayerGUI();
    this->initEnemySystem();
    this->initTileMap();
    this->initSystems();
    this->initMusic();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
    delete this->playerGUI;
    delete this->tileMap;
    delete this->enemySystem;
    delete this->tts;

    for (size_t i = 0; i < activeEnemies.size(); i++)
    {
        delete this->activeEnemies[i];
    }  
}

const bool GameState::getKeyTime()
{
    if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
    {
        this->keyTimer.restart();
        return true;
    }

    return false;
}

void GameState::resetPlayerPositionAndHealth()
{
    this->player->setPosition(320, 300);

    this->player->resetHealth();
}

void GameState::updateView(const float& dtime)
{
    //if (!this->playerGUI->getTabsOpen())
    //{
        this->view.setCenter(
            std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePositionWindow.x) - static_cast<float>(this->StataData->gfxSettings->resolution.width / 2)) / 8.f),
            std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePositionWindow.y - static_cast<float>(this->StataData->gfxSettings->resolution.height / 2)) / 8.f))
        );
    //}

    if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
    {
        if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
        {
            this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
        else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
        {
            this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
    }

    if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
    {
        if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
        {
            this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
        }
        else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
        {
            this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
        }
    }

    this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->StataData->gridSize);
    this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->StataData->gridSize);
}

void GameState::updateKeybinds(const float& dtime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerKeybinds(const float& dtime)
{
    //if (!this->playerGUI->getTabsOpen())
    //{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        {
            this->player->move(-1.f, 0.f, dtime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        {
            this->player->move(1.f, 0.f, dtime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        {
            this->player->move(0.f, -1.f, dtime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        {
            this->player->move(0.f, 1.f, dtime);
        }
    //}
}

void GameState::updatePlayerGUI(const float& dtime)
{
    this->playerGUI->update(dtime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_TAB_CHARACTER"))) && this->getKeyTime())
    {
        this->playerGUI->toggleCharacterTab();
    }
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("EXIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dtime)
{
    this->tileMap->updateWorldBoundsCollision(this->player, dtime);
    this->tileMap->updateTileColision(this->player, dtime);
    this->tileMap->updateTiles(this->player, dtime, *this->enemySystem);
}

void GameState::updatePlayer(const float& dtime)
{
    this->player->update(dtime, this->mousePositionView, this->view);
}

void GameState::updateCombatAndEnemies(const float& dtime)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getWeapon()->getAttackTimer())
        this->player->setInitAttack(true);

    int index = 0;
    for (auto* enemy : this->activeEnemies)
    {
        enemy->update(dtime, this->mousePositionView, this->view);

        this->tileMap->updateWorldBoundsCollision(enemy, dtime);
        this->tileMap->updateTileColision(enemy, dtime);

        this->updateCombat(enemy, index, dtime);

        //Dangerous
        if (enemy->isDead())
        {
            this->player->gainEXP(enemy->getGainExp());
            this->tts->addTextTag(TagTypes::EXPERIENCE_TAG, this->player->getCenter().x - 50.f, this->player->getCenter().y, 
                static_cast<int>(enemy->getGainExp()), "+" , "Exp");

            this->enemySystem->removeEnemy(index);
            continue;
        }
        else if (enemy->getDespawnTimerDone())
        {
            this->enemySystem->removeEnemy(index);
            continue;
        }
        ++index;
    }

    this->player->setInitAttack(false);

    if (this->player->isDead())
    {
        this->resetPlayerPositionAndHealth();
    }
}

template <typename U>
requires std::integral<U>
void GameState::updateCombat(Enemy* enemy, U index, const float& dtime)
{
        if (this->player->getInitAttack()
            && enemy->getGlobalBounds().contains(this->mousePositionView)
            && enemy->getDistance(*this->player) < this->player->getWeapon()->getRanged()
            && enemy->getDamageTimerDone())
        {
            //Get to this!!!
            int dmg = static_cast<int>(this->player->getDamage());
            enemy->loseHp(dmg);
            enemy->resetDamageTimer();
            this->tts->addTextTag(TagTypes::DEFAULT_TAG, enemy->getPosition().x + 20.f, enemy->getPosition().y, dmg, "-", "Hp");
        }

        //Check for enemy damage
        if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && player->getDamageTimer())
        {
            int dmg = enemy->getAtributeComp()->damageMax;
            this->player->loseHP(dmg);
            this->tts->addTextTag(TagTypes::NEGATIVE_TAG, player->getPosition().x, player->getPosition().y, dmg, "-", "Hp");
        }
}

void GameState::update(const float& dtime)
{
	this->updateMousePosition(&this->view);
	this->updateKeybinds(dtime);
	this->updateKeytime(dtime);

	if (!this->paused) //Unpaused update
	{
        this->updateView(dtime);

		this->updatePlayerKeybinds(dtime);

        this->updateTileMap(dtime);

        this->updatePlayer(dtime);

        this->updatePlayerGUI(dtime);

        this->updateCombatAndEnemies(dtime);

        this->tts->update(dtime);
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePositionWindow);
		this->updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
    this->renderTexture.clear();

    this->renderTexture.setView(this->view);

    this->tileMap->render(this->renderTexture, 
        this->viewGridPosition,
        &this->core_shader, 
        this->player->getCenter(),
        false);

    for (auto* enemy : this->activeEnemies)
    {
        enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), true);
    }

	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), true);

    this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());

    this->tts->render(this->renderTexture);

    this->renderTexture.setView(this->renderTexture.getDefaultView());
    this->playerGUI->render(this->renderTexture);

	if (this->paused) //Pause menu render
	{
        //this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

    //Final render
    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}
