#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP),fovRadius(10),
   screenWidth(screenWidth),screenHeight(screenHeight) {
   TCODConsole::initRoot(screenWidth,screenHeight,"libtcod C++ tutorial",false);

   player = new Actor(40,25,'@',"player",TCODColor::white);
   player->destructible=new PlayerDestructible(30,2,"your cadaver");
   player->attacker=new Attacker(5);
   player->ai = new PlayerAi();
   actors.push(player);

  map = new Map(screenWidth, screenHeight);
  map->computeFov();
}

Engine::~Engine( ){
  delete map;
  actors.clearAndDelete();
}


void Engine::update(){

  if (gameStatus == STARTUP)
  {
    map->computeFov();
    gameStatus=IDLE;
  }
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
  player->update();
  if (gameStatus==NEW_TURN){
    for (Actor* actorAux : engine.actors){
      actorAux->update();
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
  TCODConsole::root->print(1,screenHeight-2, "HP : %d/%d",(int)player->destructible->hp,(int)player->destructible->maxHp);
  TCODConsole::flush();
}

void Engine::sendToBack(Actor *actor) {
   actors.remove(actor);
   actors.insertBefore(actor,0);
}
