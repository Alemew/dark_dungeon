#include "libtcod.hpp"
#include "Map.hpp"
#include "Actor.hpp"


#pragma once
#define FOVRADIOUS_INICIAL 10

class Engine{
public:

  enum GameStatus {
    STARTUP,  // Estado inicial, preparar el juego.
    IDLE,  // Estás parado, no hay nada que procesar
    NEW_TURN,  // Te movistes, hay que procesar.
    VICTORY,  // Has ganado
    DEFEAT  // Has perdido
  } gameStatus;  // Declaramos una variable de este enumerado

  Map* map;
  TCODList<Actor*> actors;
  Actor* player;
  int fovRadius;
  bool computeFov;

  Engine();
  ~Engine();
  void update();
  void render() ;
  void sendToBack(Actor *actor);
};

extern Engine engine;
