#ifndef GAMESTATEH
#define GAMESTATEH

#include <iostream>
#include <string.h>
#include <vector>

class GameState{
public:
  virtual void update() = 0;
  virtual void render() = 0;

  virtual bool onEnter() = 0;
  virtual bool onExit() = 0;

  virtual std::string getStateId() const = 0;

protected:
  std::vector<std::string> textureIDsList;
};

#endif //GAMESTATEH
