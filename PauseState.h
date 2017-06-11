#ifndef PAUSESTATEH
#define PAUSESTATEH

#include <vector>
#include "MenuState.h"
#include "GameObject.h"
#include "Game.h"

class PauseState : public MenuState{

private:
  static void pauseToMain();
  static void resumePlay();

  static const std::string pauseID;

  std::vector<GameObject*> gameObjects;

  virtual void setCallbacks(const std::vector<Callback>& callbacks);
public:
  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateId() const { return pauseID; }

};

#endif //PAUSESTATEH
