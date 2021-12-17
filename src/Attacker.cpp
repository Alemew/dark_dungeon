#include "main.hpp"

Attacker::Attacker(float power) : power(power) {
}

void Attacker::attack(Actor *owner, Actor *target) {
   if ( target->destructible && ! target->destructible->isDead() ) {
       if ( power - target->destructible->defense > 0 ) {
           std::cout<<owner->name<<" attacks "<<target->name<<" for "<<power - target->destructible->defense<<" hit points"<<std::endl;
       } else {
           printf("%s attacks %s but it has no effect!\n", owner->name, target->name);
           std::cout<< owner->name << " attacks " << target->name << " but it has no effect!" << std::endl;
       }
       target->destructible->takeDamage(target,power);
   } else {
     std::cout << owner->name << " attacks " << target->name << " in vain" << std::endl;
   }
}
