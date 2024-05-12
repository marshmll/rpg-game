/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "Tile.h"

/* CONSTRUCTOR AND DESTRUCTOR */

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF,
					 const sf::Texture &texture, const sf::IntRect textureRect,
					 bool collision,
					 short type)
{
	this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));

	this->tile.setFillColor(sf::Color::White);

	this->tile.setTexture(&texture);

	this->tile.setPosition(grid_x * gridSizeF, grid_y * gridSizeF);

	this->tile.setTextureRect(textureRect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{
}

/* FUNCTIONS */

void Tile::update()
{
}

void Tile::render(sf::RenderTarget &target)
{
	target.draw(this->tile);
}

const bool Tile::intersects(const sf::FloatRect &bounds) const
{
	return this->tile.getGlobalBounds().intersects(bounds);
}

/* ACCESSORS */

const sf::Vector2f &Tile::getPosition() const
{
	return this->tile.getPosition();
}

const bool &Tile::isCollideable()
{
	return this->collision;
}

const std::string Tile::getPropertiesAsString() const
{
	std::stringstream ss;

	ss << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " "
		 << this->collision << " " << this->type;

	return ss.str();
}
