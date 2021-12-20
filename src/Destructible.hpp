#include "main.hpp"

#pragma once

class Destructible {
public :
   float maxHp;
   float hp;
   float defense;
   std::string corpseName; // the actor's name once dead/destroyed

  Destructible(float maxHp, float defense, const std::string corpseName);
  inline bool isDead() { return hp <= 0; }
  float takeDamage(Actor *owner, float damage);
  virtual void die(Actor *owner);
};

  class MonsterDestructible : public Destructible {
public :
   MonsterDestructible(float maxHp, float defense, const char *corpseName);
   void die(Actor *owner);
};

class PlayerDestructible : public Destructible {
public :
   PlayerDestructible(float maxHp, float defense, const char *corpseName);
   void die(Actor *owner);
};

