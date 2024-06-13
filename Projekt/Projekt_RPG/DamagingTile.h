#ifndef DAMAGINGTILE_H
#define DAMAGINGTILE_H

#include "Tile.h"

class DamagingTile :
    public Tile
{
private:
    int damage;

public:
    DamagingTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture_sheet, const sf::IntRect& texture_rect, int damage);
    virtual ~DamagingTile();

    const int getDamage() const;

    virtual const std::string getAsString() const;

    virtual void update();
    virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position);
};

#endif

