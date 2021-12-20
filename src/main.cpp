#include "main.hpp"

Engine engine;

int main() {

  while ( !TCODConsole::isWindowClosed() ) {
    Engine engine(80,50);
    engine.update();
    engine.render();
  }
  return  0;
}
