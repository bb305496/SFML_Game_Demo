#include "stdafx.h"
#include "DamagingTile.h"

DamagingTile::DamagingTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture_sheet, const sf::IntRect& texture_rect, int damage)
    : Tile(TileTypes::DAMAGING, grid_x, grid_y, gridSizeF, texture_sheet, texture_rect, false)
{
    this->damage = damage;
}

DamagingTile::~DamagingTile()
{

}

const int DamagingTile::getDamage() const
{
    return this->damage;
}

const std::string DamagingTile::getAsString() const
{
    std::stringstream ss;

    ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->damage;

    return ss.str();
}

void DamagingTile::update()
{

}

void DamagingTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", player_position);

        target.draw(this->shape, shader);
    }
    else
        target.draw(this->shape);
}
