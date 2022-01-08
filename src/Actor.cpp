#include "main.hpp"

Actor::Actor(int x, int y, int ch, const TCODColor &col, std::string name, int evasion): x(x), y(y), ch(ch), col(col),name(name),evasion(evasion),blocks(true),attacker(NULL),destructible(NULL),ai(NULL){};

void Actor::render( ) const{
  TCODConsole::root->putChar(x,y,ch);
  TCODConsole::root->setCharForeground(x,y,col);
};

void Actor::update() {
  if(ai){
    ai->update(this);
  }
};




