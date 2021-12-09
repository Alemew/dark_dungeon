#include "Map.hpp"
#include "libtcod.hpp"


Map::Map(int width, int height): width(width), height(height){

  tiles = new Tile[width*height];

  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++)
    {
      if (i==width-1 || i== 0 || j== height-1 || j==0){
      setWall(i,j);
    }
  }
}


};
Map::~Map(){
  delete[] tiles;
};
bool Map::isWall(int x, int y) const{

  if (!tiles[x+y*width].canWalk)
  {
    return true;
  }else{
    return false;
  }

};
void Map::render() const{
static const TCODColor darkGround(50,50,150);
static const TCODColor darkWall(0,0,100);
for (int i = 0; i < width; i++)
{
  for (int j = 0; j < height; j++)
  {
    if (isWall(i,j))
    {
      TCODConsole::root->setCharBackground(i,j,darkWall);
    }else{
      TCODConsole::root->setCharBackground(i,j,darkGround);
    }
  }
}

};
void Map::setWall(int x, int y){

  tiles[x+y*width].canWalk = false;

};