#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <iostream>
#include "LoaderParams.h"

using namespace std;

class GameObject{
protected:
  GameObject(){}
  virtual ~GameObject() {}

public:
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

  //new load function
  virtual void load(const LoaderParams* params) = 0;
};


#endif //GAMEOBJECT
