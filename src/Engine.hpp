#include "libtcod.hpp"
#include "Map.hpp"
#include "Actor.hpp"


#pragma once
#define FOVRADIOUS_INICIAL 10

class Engine{
public:
  Map* map;
  TCODList<Actor*> actors;
  Actor* player;
  int fovRadius;
  bool computeFov;

  Engine();
  ~Engine();
  void update();
  void render() ;
};

extern Engine engine;
