#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, 
    std::map<std::string, sf::Texture>& textures, Entity& player)
    : textures(textures), activeEnemies(activeEnemies), player(player)
{
    this->textures = textures;
    this->activeEnemies = activeEnemies;
}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile)
{
    switch (type)
    {
    case EnemyTypes::BUG1:
        this->activeEnemies.push_back(new Bug1(xPos, yPos, this->textures["BUG1_SHEET"], enemy_spawner_tile, this->player));
        enemy_spawner_tile.increaseEnemyCounter();
        break;
    case EnemyTypes::RAT1:
        this->activeEnemies.push_back(new Rat1(xPos, yPos, this->textures["RAT1_SHEET"], enemy_spawner_tile, this->player));
        enemy_spawner_tile.increaseEnemyCounter();
        break;
    default:
        std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY:: cant create enemy" << "\n";
        break;
    }
}

void EnemySystem::removeEnemy(const int index)
{
    this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
    delete this->activeEnemies[index];
    this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float& dtime)
{

}

void EnemySystem::render(sf::RenderTarget* target)
{

}
