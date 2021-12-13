#include "Engine.hpp"

Engine::Engine(){
   TCODConsole::initRoot(ANCHO_MAPA,ALTO_MAPA,"libtcod C++ tutorial",false);
  map = new Map(ANCHO_MAPA,ALTO_MAPA);
  bool first = true;
  createRoom(first,2,2,20,20);
  first = false;
  createRoom(first,25,25,50,50);

  map->dig((22/2),(22/2),(75/2),(22/2)+1);
  map->dig((75/2),(22/2),(75/2)+1,(75/2));

  enemy = new Actor(10,10,'&',TCODColor::yellow);

  actors.push(player);
  actors.push(enemy);

}

Engine::~Engine(){
  delete map;
  actors.clearAndDelete();
}

void Engine::createRoom(bool first, int x1, int y1, int x2, int y2){
  if (first)
  {
    player = new Actor((x1+x2)/2,(y1+y2)/2,'@',TCODColor::red);
  }
  map->dig(x1,y1,x2,y2);

}

void Engine::update(){
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
  switch(key.vk) {
    case TCODK_UP :
      if (!map->isWall(player->x,player->y-1)){
        player->y--;
      }
      break;
    case TCODK_DOWN :
      if (!map->isWall(player->x,player->y+1)){
        player->y++;
      }
      break;
    case TCODK_LEFT :
      if (!map->isWall(player->x-1,player->y)){
        player->x--;
      }
      break;
    case TCODK_RIGHT :
      if (!map->isWall(player->x+1,player->y)){
        player->x++;
      }
      break;

    default:break;
  }
}

void Engine::render(){
  TCODConsole::root->clear();
  map->render();
  for(Actor* actorAux: actors){
    actorAux -> render();
  }
  player->render();
  TCODConsole::flush();
}
