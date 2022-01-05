#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP),fovRadius(10),
   screenWidth(screenWidth),screenHeight(screenHeight) {
   TCODConsole::initRoot(screenWidth,screenHeight,"Dark Dungeon",false);

   player = new Actor(25,25,'@',TCODColor::white,"player");
   player->destructible=new PlayerDestructible(30,2,"your cadaver");
   player->attacker=new Attacker(5);
   player->ai = new PlayerAi();
   actors.push(player);

  map = new Map(ANCHO_MAPA, ALTO_MAPA);
  gui = new Gui();
  gui->message(TCODColor::red,
 "Welcome warrior!\nPrepare to enter the dungeon of despair.");
  map->computeFov();
}


Engine::~Engine( ){
  delete map;
  delete gui;
  actors.clearAndDelete();
}


void Engine::update(){

  if (gameStatus == STARTUP)
  {
    map->computeFov();
  }
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
  gameStatus=IDLE;
  player->update();
  if (gameStatus==NEW_TURN){
    for (Actor* actorAux : engine.actors){
      if (actorAux!=player)
      {
        actorAux->update();
      }
    }
  }
}


void Engine::render(){
  TCODConsole::root->clear();
  //Mapa
  if(computeFov){
    computeFov = false;
    map->computeFov();
  }
  map->render();
  //Actores
  for(Actor* actorAux : actors){
    if(map->isInFov(actorAux->x,actorAux->y)){
      actorAux ->render();
    }

  }
  //re-renderizo el jugador:
  player->render();
  gui->render();
  TCODConsole::flush();
}

void Engine::sendToBack(Actor *actor) {
   actors.remove(actor);
   actors.insertBefore(actor,0);
}
