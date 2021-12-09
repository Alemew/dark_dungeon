#include "libtcod.hpp"

#ifndef DARK_DUNGEON_ACTOR
#define DARK_DUNGEON_ACTOR

class Actor {
public :
   int x,y; // position on map
   int ch; // ascii code
   TCODColor col; // color

   Actor(int x, int y, int ch, const TCODColor &col);
   void render() const;
};

#endif DARK_DUNGEON_ACTOR
