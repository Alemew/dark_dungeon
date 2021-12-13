#include "libtcod.hpp"

#pragma once

#define ANCHO_MAPA 80
#define ALTO_MAPA 50

struct Tile {
   bool canWalk; // can we walk through this tile?
   Tile() : canWalk(false) {}
};

class Map {
public :
   int width,height;

   Map(int width, int height);
   ~Map();
   bool isWall(int x, int y) const;
   void render() const;
   void dig(int x_inicial,int y_inicial, int x_final, int y_final);

protected :
   Tile *tiles;

   void setGround(int x, int y);
};

