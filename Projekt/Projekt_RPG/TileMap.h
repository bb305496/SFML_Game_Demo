#ifndef TILEMAP_H
#define TILEMAP_H

#include "EnemySpawnerTile.h"
#include "RegularTile.h"
#include "DamagingTile.h"
#include "EnemySystem.h"
#include "Player.h"

class Tile;
class Entity;
class EnemySpawnerTile;

class TileMap
{
private:
    void clear();

    float gridSizeF;
	int gridSizeI;
	int layers;
	sf::Vector2i maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
    std::stack<Tile*> deferredRenderStack;
    std::string textureFile;
    sf::Texture tileSheet;
    sf::RectangleShape collisionBox;

    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;

    std::mutex mapMutex;

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
    TileMap(const std::string file_name);
	virtual ~TileMap();

    const bool tileEmpty(const int x, const int y, const int z) const;
    const sf::Texture* getTileSheet() const;
    const int getLayerSize(const int x, const int y, const int layer) const;
    const sf::Vector2i& getMaxSizeGrid() const;
    const sf::Vector2f& getMaxSizeF() const;

    void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
    void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect,
        const int enemy_type, const int enemy_amount, const int enemy_tts, const int enemy_md);
    void addDamagingTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, int damage);
    void removeTile(const int x, const int y, const int z, const int type = -1);
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
    const bool checkType(const int x, const int y, const int z, const int type) const;

    void updateWorldBoundsCollision(Entity* entity, const float& dtime);
    void updateTileColision(Entity* entity, const float& dtime);
    void updateTiles(Entity* entity, const float& dtime, EnemySystem& enemySystem);
    void updateTilesAsync(Entity* entity, const float& dtime);
    void update(Entity* entity, const float& dtime);

    void render(sf::RenderTarget& target, 
        const sf::Vector2i& gridPosition, 
        sf::Shader* shader = NULL,
        const sf::Vector2f playerPosition = sf::Vector2f(),
        const bool show_collision = false);
    void renderDeferred(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());
};

#endif

