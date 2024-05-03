#ifndef TILEMAP_TILEMAP_H_
#define TILEMAP_TILEMAP_H_

#include "../Tile/Tile.h"

class TileMap
{
private:
	/* VARIABLES */
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u tileMapDimensions;
	std::vector<std::vector<std::vector<Tile*> > > tileMap;

	sf::Texture tileTextureSheet;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	TileMap(float gridSize, unsigned width, unsigned );
	virtual ~TileMap();

	/* FUNCTIONS */
	void update();
	void render(sf::RenderTarget &target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &textureRect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	/* ACCESSORS */
	const sf::Texture* getTileTextureSheet() const;
};

#endif /* TILEMAP_TILEMAP_H_ */
