#ifndef RAT1_H
#define RAT1_H


#include "Enemy.h"
#include "AIFollow.h"

class Rat1 :
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
    Rat1(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
    virtual ~Rat1();

    void updateAnimation(const float& dtime);

    void update(const float& dtime, sf::Vector2f& mouse_pos_view, const sf::View& view);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);

};

#endif // !RAT1_H
