#include "main.hpp"
#pragma once

class Actor {
public :

   int x,y; // position on map
   int ch; // ascii code
   std::string name;
   int evasion;
   TCODColor col; // color
   bool blocks; // can we walk on this actor?
   bool fovOnly; // only display when in fov
   Attacker *attacker; // something that deals damage
   Destructible *destructible; // something that can be damaged
   Ai *ai; // something self-updating

   Actor(int x, int y, int ch, const TCODColor &col, std::string name);
   void render( ) const;
   void update();
   //bool moveOrAttack(int x, int y);
};


