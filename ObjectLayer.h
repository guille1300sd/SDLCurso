#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include <vector>
#include "GameObject.h"
#include "Layer.h"

class ObjectLayer : public Layer{
private:
    std::vector<GameObject*> gameObjects;

public:
    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects() { return &gameObjects; }
};

#endif // OBJECTLAYER_H
