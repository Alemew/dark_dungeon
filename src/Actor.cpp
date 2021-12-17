#include "main.hpp"

Actor::Actor(int x, int y, int ch, const TCODColor &col, std::string name): x(x), y(y), ch(ch), col(col),name(name),blocks(true),attacker(NULL),destructible(NULL),ai(NULL){};

void Actor::render( ) const{
  TCODConsole::root->putChar(x,y,ch);
  TCODConsole::root->setCharForeground(x,y,col);
};

void Actor::update() {
  if(ai){
    ai->update(this);
  }
};

/**
 * Devuelve falso si no se puede mover (pared u enemigo).
 * Si vas contra un enemigo, entonces haces un mensaje de ataque.
 * Si no hay pared ni enemigo, entonces actualizamos la posición de este actor (this) a x e y que pasamos.
 */
/*bool Actor::moveOrAttack(int x, int y) {
  if (engine.map->isWall(x,y)){
    return false;
  }
  for (Actor* actorAux : engine.actors){
    if (actorAux->x==x && actorAux->y==y){
      std::cout<<"El "<<actorAux->name<<" ni se inmuta"<<std::endl;
      return false;
    }
  }
  this->x =x;
  this->y=y;

}*/


