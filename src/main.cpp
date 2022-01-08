#include "main.hpp"

Engine engine(80,50);

int main() {
  engine.load();
  while ( !TCODConsole::isWindowClosed() ) {

    engine.update();
    engine.render();
  }
  return  0;
}
