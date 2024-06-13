#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
    unsigned value, std::string texture_file)
    :MeleeWeapon(level, damage_min, damage_max, range, value, texture_file)
{
    //Visual Weapon
    this->weapon_sprite.setOrigin(
        this->weapon_sprite.getGlobalBounds().width / 2.f,
        this->weapon_sprite.getGlobalBounds().height
    );
}

Sword::~Sword()
{

}

Sword* Sword::clone()
{
    return new Sword(*this);
}

void Sword::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)
{
    //Update visual weapon
    this->weapon_sprite.setPosition(center);

    float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
    float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

    const float pi = 3.14159265f;
    float deg = atan2(dY, dX) * 180.f / pi;

    if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax / 2)
    {
        //this->weapon_sprite.rotate(10.f);
        float lenght = std::sqrt(pow(dX, 2) + pow(dY, 2));
        sf::Vector2f normVec(dX / lenght, dY / lenght);

        this->weapon_sprite.setPosition(center.x + normVec.x * 20.f, center.y + normVec.y * 20.f);
    }
    else
    {
        this->weapon_sprite.setRotation(deg + 90.f);
    }
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
    if (shader)
        target.draw(this->weapon_sprite, shader);
    else
        target.draw(this->weapon_sprite);
}