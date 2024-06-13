#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "EnemySpawnerTile.h"
#include "Bug1.h"
#include "Rat1.h"

enum EnemyTypes {BUG1 = 0, RAT1};

class EnemySystem
{
private:
    std::map<std::string, sf::Texture>& textures;
    std::vector<Enemy*>& activeEnemies;
    Entity& player;

public:
    EnemySystem(std::vector<Enemy*>& activeEnemies, 
        std::map<std::string, sf::Texture>& textures, Entity& player);
    virtual ~EnemySystem();

    void createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile);
    void removeEnemy(const int index);

    void update(const float& dtime);
    void render(sf::RenderTarget* target);
};

#endif

