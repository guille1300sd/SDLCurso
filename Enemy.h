#ifndef ENEMYH
#define ENEMYH

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject{
public:

  Enemy();

  virtual void draw();
  virtual void update();
  virtual void clean();

  virtual void load(const LoaderParams* params);
};


class EnemyCreator : public BaseCreator{
public:
  GameObject* createGameObject() const{
    return new Enemy();
  }

};

#endif //ENEMYH
