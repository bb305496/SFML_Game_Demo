#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"


class Enemy :
    public Entity
{
protected:
    EnemySpawnerTile& enemySpawnerTile;
    unsigned gainExp;
    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;
    sf::Clock despawnTimer;
    sf::Int32 despawnTimerMax;

    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:
    Enemy(EnemySpawnerTile& enemy_spawner_tile);
    virtual ~Enemy();

    const unsigned& getGainExp() const;
    EnemySpawnerTile& getEnemySpawnerTile();

    const bool getDamageTimerDone() const;
    const bool getDespawnTimerDone() const;

    void resetDamageTimer();

    virtual void generateAttributes(const unsigned& level);

    virtual void loseHp(const int hp);
    virtual const bool isDead() const;

    virtual const AttributeComponent* getAtributeComp() const;

    virtual void updateAnimation(const float& dtime) = 0;

    virtual void update(const float& dtime, sf::Vector2f& mouse_pos_view, const sf::View& view) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

#endif

