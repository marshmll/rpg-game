/*
 * The player entity class.
 *
 *  Created on: 19 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "../PCH/stdafx.h"
#include "Player.h"

#define PRIORITARY true

/* INITIALIZERS */
void Player::initVariables()
{
	/**
	 * @return void
	 *
	 * Initializes player variables.
	 */

	this->isJumping = false;
	this->currentJumpAnimationName = "NONE";
}

void Player::initAnimations()
{
	/**
	 * @return void
	 *
	 * Initializes player animations.
	 */

	this->animationComponent->addAnimation("IDLE_DOWN", 100.f, 0, 0, 0, 0, 64.f, 64.f);
	this->animationComponent->addAnimation("IDLE_UP", 100.f, 0, 1, 0, 1, 64.f, 64.f);
	this->animationComponent->addAnimation("IDLE_RIGHT", 100.f, 0, 2, 0, 2, 64.f, 64.f);
	this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 3, 0, 3, 64.f, 64.f);

	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 4, 5, 4, 64.f, 64.f);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 5, 5, 5, 64.f, 64.f);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 6, 5, 6, 64.f, 64.f);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 7, 5, 7, 64.f, 64.f);

	this->animationComponent->addAnimation("SPRINT_DOWN", 10.f, 6, 4, 9, 4, 64.f, 64.f);
	this->animationComponent->addAnimation("SPRINT_UP", 10.f, 6, 5, 9, 5, 64.f, 64.f);
	this->animationComponent->addAnimation("SPRINT_RIGHT", 10.f, 6, 6, 9, 6, 64.f, 64.f);
	this->animationComponent->addAnimation("SPRINT_LEFT", 10.f, 6, 7, 9, 7, 64.f, 64.f);

	this->animationComponent->addAnimation("JUMP_DOWN", 13.f, 5, 0, 8, 0, 64.f, 64.f);
	this->animationComponent->addAnimation("JUMP_UP", 13.f, 5, 1, 8, 1, 64.f, 64.f);
	this->animationComponent->addAnimation("JUMP_RIGHT", 13.f, 5, 2, 8, 2, 64.f, 64.f);
	this->animationComponent->addAnimation("JUMP_LEFT", 13.f, 5, 3, 8, 3, 64.f, 64.f);
}

/* CONSTRUCTOR AND DESTRUCTOR */
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
	/**
	 * @constructor
	 *
	 * Player entity class constructor.
	 * -> Initializes variables
	 * -> Sets the player position with x and y arguments.
	 * -> Initializes components
	 * -> Initializes animations
	 */

	this->initVariables();
	this->setPosition(sf::Vector2f(x, y));

	this->createHitboxComponent(70.f, 45.f, 50.f, 85.f);
	this->createMovementComponent(200.f, 12.f, 8.f);
	this->createAnimationComponent(texture_sheet);

	this->initAnimations();
}

Player::~Player()
{
	/**
	 * @destructor
	 */
}

/* FUNCTIONS */
void Player::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the player entity.
	 * -> Updates the movement component.
	 * -> Plays the respective animation.
	 */

	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	this->updateJump(dt);
	this->updateAnimation(dt);
}

void Player::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the player into a target.
	 */

	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}

void Player::updateAnimation(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the player animations.
	 */

	switch (this->movementComponent->getCurrentState())
	{
	case IDLE:
		this->animationComponent->play("IDLE_" + this->movementComponent->getDirection(), dt);
		break;
	case MOVING:
		this->animationComponent->play("WALK_" + this->movementComponent->getDirection(), dt,
				std::abs(this->movementComponent->getVelocity().x + this->movementComponent->getVelocity().y),
				this->movementComponent->getMaxVelocity());
		break;
	}
}

void Player::updateJump(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the jump states and animations.
	 */

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
	{
		this->isJumping = true;
		this->animationComponent->play("JUMP_" + this->movementComponent->getDirection(), dt, PRIORITARY);
		this->currentJumpAnimationName = "JUMP_" + this->movementComponent->getDirection();
	}

	if (this->currentJumpAnimationName != "NONE")
	{
		if (this->animationComponent->isAnimationDone(this->currentJumpAnimationName))
			this->isJumping = false;
	}

}

