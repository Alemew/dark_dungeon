#include "main.hpp"

static const int PANEL_HEIGHT=7;
static const int BAR_WIDTH=20;
static const int MSG_X=BAR_WIDTH+2;
static const int MSG_HEIGHT=PANEL_HEIGHT-1;

Gui::Gui() {
   con = new TCODConsole(engine.screenWidth,PANEL_HEIGHT);
}

Gui::~Gui() {
   delete con;
   clear();
}

void Gui::render(){
  con->setDefaultBackground(TCODColor::black);
  con->clear();

  renderBar(1,1,BAR_WIDTH,"HP",engine.player->destructible->hp,engine.player->destructible->maxHp,TCODColor::lightRed,TCODColor::darkerRed);

  int y=1;
  float colorCoef=0.4f;
  for (Message **it=log.begin(); it != log.end(); it++) {
    Message *message=*it;
    con->setDefaultForeground(message->col* colorCoef);
    con->print(MSG_X,y,message->text);
    y++;
    if ( colorCoef < 1.0f ) {
       colorCoef+=0.3f;
   }
  }

  TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT);
}

void Gui::renderBar(int x, int y, int width, const char *name,float value, float maxValue, const TCODColor &barColor,const TCODColor &backColor){
  con->setDefaultBackground(backColor);
  con->rect(x,y,width,1,false,TCOD_BKGND_SET);
  int barWidth = (int) (value/maxValue*width);
  if (barWidth > 0){
    con->setDefaultBackground(barColor);
    con->rect(x,y,barWidth,1,false,TCOD_BKGND_SET);
  }

   con->setDefaultForeground(TCODColor::white);
   con->printEx(x+width/2,y,TCOD_BKGND_NONE,TCOD_CENTER,
       "%s : %g/%g", name, value, maxValue);

}

Gui::Message::Message(const char *text, const TCODColor &col) :
   text(strdup(text)),col(col) {
}

Gui::Message::~Message() {
   free(text);
}

void Gui::clear(){
  log.clearAndDelete();
}

void Gui::message(const TCODColor &col, const char *text, ...) {

  va_list ap;
  char buf[128];
  va_start(ap,text);
  vsprintf(buf,text,ap);
  va_end(ap);
  char *lineBegin=buf;
  char *lineEnd;
  do {

    if ( log.size() == MSG_HEIGHT ) {
      Message *toRemove=log.get(0);
      log.remove(toRemove);
      delete toRemove;
    }

    lineEnd=strchr(lineBegin,'\n');

    if ( lineEnd ) {
      *lineEnd='\0';
    }

    Message *msg=new Message(lineBegin, col);
    log.push(msg);

    lineBegin=lineEnd+1;
   } while ( lineEnd );
}

Menu::~Menu() {
   clear();
}

void Menu::clear() {
   items.clearAndDelete();
}

void Menu::addItem(MenuItemCode code, const char *label) {
   MenuItem *item=new MenuItem();
   item->code=code;
   item->label=label;
   items.push(item);
}

Menu::MenuItemCode Menu::pick() {
   static TCODImage img("menu_background1.png");
   int selectedItem=0;
  while( !TCODConsole::isWindowClosed() ) {
    img.blit2x(TCODConsole::root,0,0);
    int currentItem=0;
    for (MenuItem **it=items.begin(); it!=items.end(); it++) {
      if ( currentItem == selectedItem ) {
        TCODConsole::root->setDefaultForeground(TCODColor::lighterOrange);
      } else {
        TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
      }
      TCODConsole::root->print(10,10+currentItem*3,(*it)->label);
      currentItem++;
    }
    TCODConsole::flush();
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);

    switch (key.vk) {
      case TCODK_UP :
        selectedItem--;
        if (selectedItem < 0) {
          selectedItem=items.size()-1;
        }
      break;
      case TCODK_DOWN :
        selectedItem = (selectedItem + 1) % items.size();
      break;
      case TCODK_ENTER : return items.get(selectedItem)->code;
      default : break;
    }
  }
  return NONE;
}

