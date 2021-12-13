#include "libtcod.hpp"
#include "Map.hpp"
#include "Actor.hpp"

#pragma once

class Engine{
  Map* map;
  TCODList<Actor*> actors;
  Actor* player;
  Actor* enemy;

public:
  Engine();
  ~Engine();
  void update();
  void render();
  void createRoom(bool first, int x1, int y1, int x2, int y2);
};

extern Engine engine;

