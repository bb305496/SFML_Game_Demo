#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

class Entity;

class Player :  public Entity
{
private:

    Inventory* inventory;

    bool initAttack;
    bool attacking;
    Weapon* weapon;
    float keyTime;
    float keyTimeMax;

    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;

    void initVariables();
    void initComponents();
    void initAnimations();
    void initInventory();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    AttributeComponent* getAttributeComponent();
    Weapon* getWeapon() const;

    const bool canTakeDamage();
    void updateKeyTime(const float& dtime);

    const std::string toStringCharacterTab() const;
    const bool& getInitAttack() const;

    const bool getDamageTimer();

    const unsigned getDamage() const;
    bool isDead() const;
    void resetHealth();

    void setInitAttack(const bool initAttack);

    void loseHP(const int hp);
    void gainHP(const int hp);
    void loseEXP(const int exp);
    void gainEXP(const int exp);
    void updateAnimation(const float& dtime);

    //Virtula from entity
    void setPosition(const float x, const float y);
    void move(const float dir_x, const float dir_y, const float& dtime);
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();

    void update(const float& dtime, sf::Vector2f& mouse_pos_view, const sf::View& view);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);


};

#endif 

