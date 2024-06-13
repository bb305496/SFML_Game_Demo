#include "stdafx.h"
#include "EnemyEditorMode.h"

void EnemyEditorMode::initVariables()
{
    this->type = 0;
    this->amount = 1;
    this->timeToSpawn = 60;
    this->maxDistance = 1000.f;
}

void EnemyEditorMode::initGui()
{
    //Text
    this->cursorText.setFont(*this->editorStateData->font);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setCharacterSize(15);
    this->cursorText.setPosition(this->editorStateData->mousePositionView->x, this->editorStateData->mousePositionView->y - 30.f);


    //General Gui
    this->sidebar.setSize(sf::Vector2f(100.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
}

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
    : EditorMode(state_data, tile_map, editor_state_data)
{
    this->initVariables();
    this->initGui();
}

EnemyEditorMode::~EnemyEditorMode()
{

}

void EnemyEditorMode::updateKeybinds(const float& dtime)
{
    //Add tile
    if (sf::Mouse::isButtonPressed(::sf::Mouse::Left) && this->getKeytime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePositionWindow)))
        {
            this->tileMap->addTile(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, 0, this->textureRect,
            this->type, this->amount, this->timeToSpawn, this->maxDistance);
        }
    }
    //Remove tile
    else if (sf::Mouse::isButtonPressed(::sf::Mouse::Right) && this->getKeytime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePositionWindow)))
        {
            this->tileMap->removeTile(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, 0, TileTypes::ENEMYSPAWNER);
        }
    }

    //Toggle collision
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_UP"))) && this->getKeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) or sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->type > 0)
                this->type--;
        }
        else if (this->type < 10)
            this->type++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("AMOUNT_UP"))) && this->getKeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) or sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->amount > 0)
                this->amount--;
        }
        else if (this->amount < 1000)
            this->amount++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TTS_UP"))) && this->getKeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) or sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->timeToSpawn > 0)
                this->timeToSpawn--;
        }
        else if (this->timeToSpawn < 1000)
            this->timeToSpawn++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("MD_UP"))) && this->getKeytime())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) or sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->maxDistance > 0)
                this->maxDistance--;
        }
        else if (this->maxDistance < 1000)
            this->maxDistance++;
    }
}

void EnemyEditorMode::updateGui(const float& dtime)
{
    this->selectorRect.setPosition(this->editorStateData->mousePositionGrid->x * this->stateData->gridSize, this->editorStateData->mousePositionGrid->y * this->stateData->gridSize);
    this->cursorText.setPosition(this->editorStateData->mousePositionView->x + 100.f, this->editorStateData->mousePositionView->y - 50.f);

    std::stringstream ss;
    ss <<
        "\n" << "Enemy Type: " << this->type <<
        "\n" << "Enemy amount: " << this->amount <<
        "\n" << "Time to spawn: " << this->timeToSpawn <<
        "\n" << "Max distance: " << this->maxDistance;


    this->cursorText.setString(ss.str());
}

void EnemyEditorMode::update(const float& dtime)
{
    this->updateKeybinds(dtime);
    this->updateGui(dtime);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target)
{
    target.setView(*this->editorStateData->view);
    target.draw(this->selectorRect);
    target.draw(this->cursorText);

    target.setView(target.getDefaultView());
    target.draw(this->sidebar);
}

void EnemyEditorMode::render(sf::RenderTarget& target)
{
    this->renderGui(target);
}
