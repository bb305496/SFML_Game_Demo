#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
    this->level = level;
    this->exp = 0;
    this->expNext = static_cast<int>((50/3) * (pow(this->level + 1, 3) - 6* pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
    this->attributePoints = 4;

    this->vitality = 1;
    this->strength = 1;
    this->dexterity = 1;
    this->agility = 1;
    this->intelligence = 1;

    this->updateLevel();
    this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}

std::string AttributeComponent::debugPrint() const
{
    std::stringstream ss;

    ss << " Level: " << this->level << "\n"
        << "Exp: " << this->exp << "\n"
        << "Exp Next: " << this->expNext << "\n"
        << "Attpoints: " << this->attributePoints << "\n";

    return ss.str();
}

void AttributeComponent::loseHP(const int hp)
{
    this->hp -= hp;

    if (this->hp < 0)
        this->hp = 0;
}

void AttributeComponent::gainHP(const int hp)
{
    this->hp += hp;

    if (this->hp > this->hpMax)
        this->hp = this->hpMax;
}

void AttributeComponent::loseEXP(const int exp)
{
    this->exp -= exp;

    if (this->exp < 0)
        this->exp = 0;
}
void AttributeComponent::gainExp(const int exp)
{
    this->exp += exp;

    this->updateLevel();
}

const bool AttributeComponent::isDead() const
{
    return this->hp <= 0;
}

void AttributeComponent::updateStats(const bool reset)
{

    //Balance this later!!! 
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    this->hpMax = (this->vitality * 9 + 5 * (this->vitality / 3)) + this->intelligence;
    this->damageMin = (this->strength + 2 * (this->strength / 6)) + this->intelligence;
    this->damageMax = (this->strength + 2 * (this->strength / 3)) + this->intelligence;
    this->accuracy  = this->dexterity * 4 + this->dexterity / 3 + this->intelligence;
    this->defence   = this->agility * 2 + this->agility / 3 + this->intelligence;
    this->luck      = this->intelligence + 2 * (this->intelligence / 3);


    if (reset)
    {
        this->hp = this->hpMax;
    }
}

void AttributeComponent::updateLevel()
{
    while (this->exp >= this->expNext)
    {
        ++this->level;
        this->exp -= this->expNext;
        this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
        ++this->attributePoints;
    }

    //this->vitality += 1;
    //this->strength += 1;
    //this->dexterity += 1;
    //this->agility += 1;
    //this->intelligence += 1;

    //this->hp = this->hpMax;

    //this->updateStats(true);
}

void AttributeComponent::update()
{
    this->updateLevel();
}
