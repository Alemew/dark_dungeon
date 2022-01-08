#include "main.hpp"

Attacker::Attacker(float power) : power(power) {
}

void Attacker::attack(Actor *owner, Actor *target) {
  TCODRandom* rng = TCODRandom::getInstance();
  if ( target->destructible && ! target->destructible->isDead() ) {
    if (target->evasion<=rng->getInt(1,7))
    {
      if ( power - target->destructible->defense > 0 ) {
        engine.gui->message(owner==engine.player ? TCODColor::red : TCODColor::lightGrey,"%s attacks %s for %g hit points.", owner->name.c_str(), target->name.c_str(),power - target->destructible->defense);
      } else {
       // engine.gui->message(TCODColor::white,"%s attacks %s for %g hit points.", owner->name.c_str(), target->name.c_str(), power);
      }
      target->destructible->takeDamage(target,power);
    }else{
      engine.gui->message(owner==engine.player ? TCODColor::red : TCODColor::lightGrey,"%s attacks but %s dodged the attack", owner->name.c_str(), target->name.c_str());
    }
  } else {
    engine.gui->message(TCODColor::lightGrey,"%s attacks %s in vain.",owner->name.c_str(),target->name.c_str());
  }
}
