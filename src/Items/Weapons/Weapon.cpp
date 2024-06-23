#include "stdafx.h"
#include "Weapon.h"

/* INITIALIZERS =============================================================================================== */

void Weapon::initVariables()
{
    cooldownTimer.restart();
    cooldownTimerMax = sf::Int32(500);
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

Weapon::Weapon(const ItemType type, const std::string texture_path, const short unsigned value,
               const short unsigned range, const short unsigned damage_min, const short unsigned damage_max)

    : Item(value, type)
{
    this->range = range;
    damageMin = damage_min;
    damageMax = damage_max;

    initVariables();

    if (!weaponHorizontalTexture.loadFromFile(texture_path, sf::IntRect(0, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path);

    if (!weaponUpTexture.loadFromFile(texture_path, sf::IntRect(64, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path);

    if (!weaponDownTexture.loadFromFile(texture_path, sf::IntRect(128, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path);

    weaponSprite.setTexture(weaponDownTexture);
}

Weapon::~Weapon()
{
}

/* ACCESSORS ================================================================================================ */

const short unsigned &Weapon::getRange() const
{
    return range;
}

const short unsigned &Weapon::getDamageMin() const
{
    return damageMin;
}

const short unsigned &Weapon::getDamageMax() const
{
    return damageMax;
}

const bool Weapon::didCooldown()
{
    if (cooldownTimer.getElapsedTime().asMilliseconds() >= cooldownTimerMax)
    {
        cooldownTimer.restart();
        return true;
    }

    return false;
}

/* MODIFIERS ===================================================================================================== */

void Weapon::setCooldownTimerMax(const sf::Int32 new_timer_max)
{
    cooldownTimerMax = new_timer_max;
}