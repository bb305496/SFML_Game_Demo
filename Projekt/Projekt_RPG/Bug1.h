#ifndef BUG1_H
#define BUG1_H

#include "Enemy.h"
#include "AIFollow.h"

class Bug1 :
    public Enemy
{
private:

    void initVariables();
    void initAnimations();
    void initAI();
    void initGUI();

    sf::RectangleShape hpBar;

    AIFollow* follow;

public:
    Bug1(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
    virtual ~Bug1();

    void updateAnimation(const float& dtime);

    void update(const float& dtime, sf::Vector2f& mouse_pos_view, const sf::View& view);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);

};

#endif

