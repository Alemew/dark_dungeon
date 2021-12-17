#include "main.hpp"

void PlayerAi::update(Actor *owner) {
   if ( owner->destructible && owner->destructible->isDead() ) {
       return;
   }
int dx = 0;
int dy = 0;

  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
  switch(key.vk) {
      case TCODK_UP :
        dy = -1;
        break;
      case TCODK_DOWN :
        dy = +1;
        break;
      case TCODK_LEFT :
        dx = -1;
        break;
      case TCODK_RIGHT :
        dx = +1;
        break;
      default:break;
  }

  if (dy != 0 || dx !=0){
    gameStatus = NEW_TURN;
    if(this->player->moveOrAttack(this->player->x+dx,this->player->y+dy)){
      map->computeFov();
    }
  }
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx,int targety) {
   if ( engine.map->isWall(targetx,targety) ){
     return false;
   }
   // look for living actors to attack
   for (Actor* actorAux : engine.actors) {
       if ( actorAux->destructible && !actorAux->destructible->isDead() && actorAux->x == targetx && actorAux->y == targety ) {
           owner->attacker->attack(owner, actorAux);
           return false;
       }
   }
   // look for corpses
  for (Actor* actorAux : engine.actors) {
   if ( actorAux->destructible && actorAux->destructible->isDead()
        && actorAux->x == targetx && actorAux->y == targety ) {
          std::cout<< "There's a "<<actorAux->name<< " here"<<std::endl;
   }
  }
  owner->x=targetx;
  owner->y=targety;
  return true;
}
