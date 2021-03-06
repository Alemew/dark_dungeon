#include "main.hpp"

#pragma once

static const int TRACKING_TURNS=3;

class Ai {
public :
   virtual void update(Actor *owner)=0;
};

class PlayerAi : public Ai {
public :
  void update(Actor *owner);

protected :
  bool moveOrAttack(Actor *owner, int targetx, int targety);
};

class MonsterAi : public Ai {
public :
  void update(Actor *owner);

protected :
  int moveCount;
  void moveOrAttack(Actor *owner, int targetx, int targety);
};
