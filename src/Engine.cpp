#include "Engine.hpp"

Engine::Engine(): computeFov(true), fovRadius(FOVRADIOUS_INICIAL),gameStatus(STARTUP) {
  TCODConsole::initRoot(ANCHO_MAPA,ALTO_MAPA,"Mi primer Rouguelite",false);

  //Jugador
  player = new Actor(25, 25, '@', TCODColor::yellow, "Player");
  actors.push(player);



  map = new Map(ANCHO_MAPA, ALTO_MAPA);
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



  if (gameStatus==NEW_TURN){
    for (Actor* actorAux : engine.actors){
      actorAux->update();
    }
  }

  gameStatus=IDLE;

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
  TCODConsole::flush();
}

void Engine::sendToBack(Actor *actor) {
   actors.remove(actor);
   actors.insertBefore(actor,0);
}
