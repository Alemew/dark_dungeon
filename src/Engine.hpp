#include "main.hpp"

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
  Gui* gui;
  TCODList<Actor*> actors;
  Actor* player;
  Actor* stairs;
  int fovRadius;
  bool computeFov;
  int screenWidth;
  int screenHeight;
  TCOD_key_t lastKey;
  int level;


  Engine();
  ~Engine();
  void update();
  void render() ;
  void sendToBack(Actor *actor);
  Engine(int screenWidth, int screenHeight);
  void init();
  void term();
  void load();
  void nextLevel();
};

extern Engine engine;
