#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
    this->range = 155;
    this->damageMin = 1;
    this->damageMax = 3;

    this->attackTimer.restart();
    this->attackTimerMax = 300;
}

Weapon::Weapon(unsigned level, unsigned value, std::string texture_file)
    : Item(level, value)
{
    this->initVariables();

    if (!this->weapon_texture.loadFromFile(texture_file))
    {
        std::cout << "ERROR::PLYAER:: cold not load weapon" << "\n";
    }
    this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::Weapon(unsigned level, unsigned damage_min, unsigned damage_max, unsigned range, unsigned value, std::string texture_file)
    : Item(level, value)
{
    this->initVariables();

    this->damageMin = damage_min;
    this->damageMax = damage_max;
    this->range = range;

    if (!this->weapon_texture.loadFromFile(texture_file))
    {
        std::cout << "ERROR::PLYAER:: cold not load weapon" << "\n";
    }
    this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::~Weapon()
{

}

const unsigned& Weapon::getDamageMin() const
{
    return this->damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
    return this->damageMax;
}

const unsigned Weapon::getDamage() const
{
    return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

const unsigned& Weapon::getRanged() const
{
    return this->range;
}

const bool Weapon::getAttackTimer()
{
    if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
    {
        this->attackTimer.restart();
        return true;
    }

    return false;
}
