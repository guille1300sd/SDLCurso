#ifndef MAINMENUSTATEH
#define MAINMENUSTATEH

#include <vector>

#include "MenuState.h"
#include "GameObject.h"
#include "Game.h"

class MainMenuState : public MenuState{
private:
  static const std::string menuID;
  std::vector<GameObject*> gameObjects;

  //call back function for menu items
  static void  menuToPlay();
  static void exitFromMenu();

  virtual void setCallbacks(const std::vector<Callback>& callbacks);
public:
  virtual void update();
  virtual void render();

  virtual bool onExit();
  virtual bool onEnter();

  virtual std::string getStateId() const { return menuID; }
};

#endif //MENUSTATEH
