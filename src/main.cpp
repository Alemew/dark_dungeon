#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"

int main() {

  Actor player(5,5,'@',TCODColor::red);
  Map mapa(80,50);

   TCODConsole::initRoot(mapa.width,mapa.height,"libtcod C++ tutorial",false);
   while ( !TCODConsole::isWindowClosed() ) {
       TCOD_key_t key;
       TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
       switch(key.vk) {
           case TCODK_UP :
           if (!mapa.isWall(player.x,player.y-1))
           {
                player.y--; break;
           }
           case TCODK_DOWN :
           if (!mapa.isWall(player.x,player.y+1))
           {
                player.y++; break;
           }
           case TCODK_LEFT :
           if (!mapa.isWall(player.x-1,player.y))
           {
                player.x--; break;
           }
           case TCODK_RIGHT :
           if (!mapa.isWall(player.x+1,player.y))
           {
                player.x++; break;
           }

           default:break;
       }
       TCODConsole::root->clear();
       mapa.render();
       player.render();


       TCODConsole::flush();
   }

   return 0;
}
