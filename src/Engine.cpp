#include "Engine.hpp"

Engine::Engine(): computeFov(true), fovRadius(FOVRADIOUS_INICIAL) {
  TCODConsole::initRoot(ANCHO_MAPA,ALTO_MAPA,"Mi primer Rouguelite",false);

  //Jugador
  player = new Actor(25, 25, '@', TCODColor::yellow);
  actors.push(player);



  map = new Map(ANCHO_MAPA, ALTO_MAPA);
  map->computeFov();
}

Engine::~Engine( ){
  delete map;
  actors.clearAndDelete();
}


void Engine::update(){
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
  switch(key.vk) {
      case TCODK_UP :
        if(map->canWalk(player->x, player->y-1)){
            player->y--;
            computeFov = true;
        }
        break;
      case TCODK_DOWN :if(map->canWalk(player->x, player->y+1)){
            player->y++;
            computeFov = true;
        }; break;
      case TCODK_LEFT : if(map->canWalk(player->x-1, player->y)){
            player->x--;
            computeFov = true;
        }; break;
      case TCODK_RIGHT : if(map->canWalk(player->x+1, player->y)){
            player->x++;
            computeFov = true;
        }; break;
      default:break;
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
  TCODConsole::flush();
}
