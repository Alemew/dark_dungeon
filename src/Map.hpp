#include "libtcod.hpp"

#ifndef DARK_DUNGEON_MAP
#define DARK_DUNGEON_MAP

struct Tile {
   bool canWalk; // can we walk through this tile?
   Tile() : canWalk(true) {}
};

class Map {
public :
   int width,height;

   Map(int width, int height);
   ~Map();
   bool isWall(int x, int y) const;
   void render() const;
protected :
   Tile *tiles;

   void setWall(int x, int y);
};

#endif DARK_DUNGEON_MAP
