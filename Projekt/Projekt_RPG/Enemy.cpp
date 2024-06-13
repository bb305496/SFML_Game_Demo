#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
    this->gainExp = 10;
    this->damageTimerMax = 500;
    this->despawnTimerMax = 1000;
}


void Enemy::initAnimations()
{

}


Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile)
    : enemySpawnerTile(enemy_spawner_tile)
{
    this->initVariables();
    this->initAnimations();
}

Enemy::~Enemy()
{

}

const unsigned& Enemy::getGainExp() const
{
    return this->gainExp;
}

EnemySpawnerTile& Enemy::getEnemySpawnerTile()
{
    return this->enemySpawnerTile;
}

const bool Enemy::getDamageTimerDone() const
{
    return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Enemy::getDespawnTimerDone() const
{
    return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

void Enemy::resetDamageTimer()
{
    this->damageTimer.restart();
}

void Enemy::generateAttributes(const unsigned& level)
{
    this->gainExp = level * (rand() % 5 + 1);
}

void Enemy::loseHp(const int hp)
{
    if (this->attributeComponent)
    {
        this->attributeComponent->loseHP(hp);
    }
}

const bool Enemy::isDead() const
{
    if (this->attributeComponent)
    {
        return this->attributeComponent->isDead();
    }
    return false;
}

const AttributeComponent* Enemy::getAtributeComp() const
{
    if (this->attributeComponent)
        return this->attributeComponent;
    else
    {
        std::cout << "ERROR::ENEMY::GETATRIBUTECOMP atrib comp is not initialize" << "\n";
        return nullptr;
    }
}

void Enemy::update(const float& dtime, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
    if(vectorDistance(this->getPosition(), view.getCenter()) < 1500.f)
    {
        this->despawnTimer.restart();
    }
}