#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
class Weapon :
    public Item
{
private:
    void initVariables();

protected:
    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;

    unsigned damageMin;
    unsigned damageMax;
    unsigned range;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

public: 
    Weapon(unsigned level, unsigned value, std::string texture_file);
    Weapon(unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
        unsigned value,
        std::string texture_file);
    virtual ~Weapon();

    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const unsigned getDamage() const;
    const unsigned& getRanged() const;
    const bool getAttackTimer();

    unsigned getType() const { return this->type; }
    unsigned getLevel() const { return this->level; }
    unsigned getValue() const { return this->value; }

    virtual Item* clone() = 0;
    virtual void generate(const unsigned levelMax, const unsigned levelMin) = 0;

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif // !WEAPON_H

