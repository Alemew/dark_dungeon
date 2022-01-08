#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP),fovRadius(10),
   screenWidth(screenWidth),screenHeight(screenHeight) {
   TCODConsole::initRoot(screenWidth,screenHeight,"Dark Dungeon",false);
   gui = new Gui();
}

void Engine::init(){
  player = new Actor(25,25,'@',TCODColor::white,"player",2);
   player->destructible=new PlayerDestructible(30,2,"your cadaver");
   player->attacker=new Attacker(5);
   player->ai = new PlayerAi();
   actors.push(player);

  map = new Map(ANCHO_MAPA, ALTO_MAPA);
  gui->message(TCODColor::red,
 "Welcome warrior!\nPrepare to enter the dungeon of despair.");
 gameStatus=STARTUP;
  map->computeFov();
}


Engine::~Engine( ){
  term();
  delete gui;
}

void Engine::term(){
  actors.clearAndDelete();
   if ( map ) delete map;
   gui->clear();
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

void Engine::load(){
  engine.gui->menu.clear();
  engine.gui->menu.addItem(Menu::NEW_GAME,"New game");
  engine.gui->menu.addItem(Menu::EXIT,"Exit");

  Menu::MenuItemCode menuItem=engine.gui->menu.pick();

  if ( menuItem == Menu::EXIT || menuItem == Menu::NONE ) {
    engine.term();
    engine.init();
  } else if ( menuItem == Menu::NEW_GAME ) {
    engine.term();
    engine.init();
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
