#include "main.hpp"


static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;


class BspListener : public ITCODBspCallback {
private :
    Map &map; // a map to dig //No puede ser un puntero a null
    int roomNum; // room number
    int lastx,lasty; // center of the last room
public :
    BspListener(Map &map) : map(map), roomNum(0) {}
    bool visitNode(TCODBsp *node, void *userData) {
    	if ( node->isLeaf() ) {
    		int x,y,w,h;
        TCODRandom *rng=TCODRandom::getInstance();
        w=rng->getInt(ROOM_MIN_SIZE, node->w-2);
        h=rng->getInt(ROOM_MIN_SIZE, node->h-2);
        x=rng->getInt(node->x+1, node->x+node->w-w-1);
        y=rng->getInt(node->y+1, node->y+node->h-h-1);
        map.createRoom(roomNum == 0, x, y, x+w-1, y+h-1);
        if ( roomNum != 0 ) {
          // dig a corridor from last room
          map.dig(lastx,lasty,x+w/2,lasty);
          map.dig(x+w/2,lasty,x+w/2,y+h/2);
        }
        lastx=x+w/2;
        lasty=y+h/2;
        roomNum++;
      }
      return true;
    }
};


Map::Map(int width, int height): width(width), height(height){
  seed=TCODRandom::getInstance()->getInt(0,0x7FFFFFFF);
};

void Map::init(bool withActors) {

  rng = new TCODRandom(seed, TCOD_RNG_CMWC);
  tiles = new Tile[width*height];
  map = new TCODMap(width,height);

  TCODBsp bsp(0,0,width,height);
  bsp.splitRecursive(NULL,8,ROOM_MAX_SIZE,ROOM_MAX_SIZE,1.5f,1.5f);
  BspListener listener(*this);
  bsp.traverseInvertedLevelOrder(&listener,NULL);
}

Map::~Map(){
  delete map;
  delete[] tiles;
};
bool Map::isWall(int x, int y) const{
  return !map->isWalkable(x,y);
};

void Map::render() const{
  static const TCODColor darkGround(50,50,150);
  static const TCODColor darkWall(0,0,100);
  static const TCODColor lightWall(130,110,50);
  static const TCODColor lightGround(200,180,50);


  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++)
    {
      if ( isInFov(x,y) ) {
           TCODConsole::root->setCharBackground(x,y, isWall(x,y) ? lightWall :lightGround );
       } else if ( isExplored(x,y) ) {
           TCODConsole::root->setCharBackground(x,y, isWall(x,y) ? darkWall : darkGround );
       }
    }
  }
};


void Map::dig(int x_inicial, int y_inicial, int x_final, int y_final){
    //Swapear si inicial > final
    if(x_inicial > x_final){
      int aux = x_inicial;
      x_inicial = x_final;
      x_final = aux;
    }

    if(y_inicial > y_final){
      int aux = y_inicial;
      y_inicial = y_final;
      y_final = aux;
    }

    //Por ??ltimo, marcamos el agujero:
    for(int x = x_inicial; x <= x_final; x++){
      for(int y = y_inicial; y <= y_final; y++){
        setWalkable(x,y);
      }
    }
};

void Map::createRoom(bool first, int x1, int y1, int x2, int y2){
  dig(x1,y1,x2,y2);
  if(first){
    //Movemos el actor principal
    engine.player->x = (x1+x2)/2;
    engine.player->y = (y1+y2)/2;
  }else{
    //A??adir un NPC:
    TCODRandom *rng=TCODRandom::getInstance();
    if(rng->getInt(0,2) == 0){
      int numberMonsters=rng->getInt(1,3);
      while (numberMonsters>0)
      {
        int npcx = rng->getInt(0,x2-x1)+x1;
        int npcy = rng->getInt(0,y2-y1)+y1;
        if (canWalk(npcx,npcy)){
          addMonster(npcx,npcy);
          numberMonsters--;
        }
      }
    }
  }
  engine.stairs->x=(x1+x2)/2;
  engine.stairs->y=(y1+y2)/2;
};


bool Map::isInFov(int x, int y) const{
  if(map->isInFov(x,y)){
    tiles[x+y*width].explored = true;
    return true;
  }
  return false;
};

bool Map::isExplored(int x, int y) const{
  return tiles[x+y*width].explored;
};

void Map::computeFov(){
  map->computeFov(engine.player->x, engine.player->y, engine.fovRadius);
};



void Map::setWall(int x, int y){
  map->setProperties(x, y, false, false );
};


void Map::setWalkable(int x, int y){
  map->setProperties(x, y, true, true ); // Para hacer modificaciones!
};

bool Map::canWalk(int x,int y)const{
  if (isWall(x,y)){
    return false;
  }
  for (Actor* actorAux : engine.actors){
    if (actorAux->blocks && actorAux->x==x && actorAux->y==y){
      return false;
    }
  }
  return true;
};

void Map::addMonster(int x, int y) {
  // Sacar un aleatorio:
  TCODRandom* rng = TCODRandom::getInstance();
  if (rng->getInt(1,5)!=5)
  {
    // 4 de cada 5 veces es un orco con color desaturatedGreen y caracter 'o'
    Actor* orc = new Actor(x, y, 'O', TCODColor::desaturatedGreen,"Ogro");
    orc->evasion = 3;
    orc->fovOnly=false;
    orc->destructible = new MonsterDestructible(10,0,"dead orc");
    orc->attacker = new Attacker(3);
    orc->ai = new MonsterAi();
    engine.actors.push(orc);
  }else {
    // 1 de cada 5 veces es un troll con color darkerGreen y caracter 'T'
    Actor* troll = new Actor(x, y, 'T', TCODColor::darkerGreen, "Troll");
    troll->evasion = 2;
    troll->fovOnly=false;
    troll->destructible = new MonsterDestructible(16,1,"troll carcass");
    troll->attacker = new Attacker(4);
    troll->ai = new MonsterAi();
    engine.actors.push(troll);
  }

}

