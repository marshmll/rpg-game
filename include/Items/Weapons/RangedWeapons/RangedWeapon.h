#ifndef RANGEDWEAPON_H_
#define RANGEDWEAPON_H_

#include "Weapon.h"

class RangedWeapon : public Weapon
{
private:
protected:
public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

    RangedWeapon(const std::string texture_path, const short unsigned value,
                 const short unsigned range, const short unsigned damage_min, const short unsigned damage_max);

    virtual ~RangedWeapon();

    /* FUNCTIONS ============================================================================================== */

    virtual void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                        const sf::Vector2f entity_center, std::string entity_direction) = 0;

    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    virtual RangedWeapon *clone() = 0;
};

#endif