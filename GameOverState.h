#ifndef GAMEOVERSTATEH
#define GAMEOVERSTATEH

#include <vector>
#include "MenuState.h"
#include "GameObject.h"
#include "Game.h"
#include "StateParser.h"

class GameOverState : public MenuState{
private:
  static void gameOverToMain();
  static void restartPlay();

  static const std::string gameOverID;

  std::vector<GameObject*> gameObjects;

  virtual void setCallbacks(const std::vector<Callback>& callbacks);

public:
  virtual void render();
  virtual void update();

  virtual bool onExit();
  virtual bool onEnter();

  virtual std::string getStateId() const { return gameOverID; }
};

#endif //GAME
