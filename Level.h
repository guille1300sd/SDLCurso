#ifndef LEVELH
#define LEVELH

#include <vector>
#include <iostream>
#include "Layer.h"

struct Tileset{
  int firstGridID;
  int tileWidth;
  int tileHeight;
  int spacing;
  int margin;
  int width;
  int height;
  int numColumns;
  std::string name;
};

class Level{
private:
  std::vector<Tileset> tilesets;
  std::vector<Layer*> layers;

  friend class LevelParser;
  Level() {}
public:

  ~Level(){}

  void update();
  void render();

  std::vector<Tileset>* getTilesets() { return &tilesets; }
  std::vector<Layer*>* getLayers() { return &layers; }
};

#endif //LEVELH
