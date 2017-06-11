#ifndef LEVELPARSERH
#define LEVELPARSERH


#include <vector>
#include "tinyxml/tinyxml.h"
#include "base64/base64.h"
#include "TileLayer.h"
#include "zlib/zlib.h"
#include "Game.h"
#include "ObjectLayer.h"

class LevelParser{
private:
  void parseTileSets(TiXmlElement* tileSetRoot, std::vector<Tileset>* tilesets);
  void parseTileLayer(TiXmlElement* tileElement, std::vector<Layer*>* layers, const std::vector<Tileset>* tilesets);

  void parseTextures(TiXmlElement* textureRoot);
  void parseObjectLayer(TiXmlElement* objectElement, std::vector<Layer*>* layers);

  int tileSize;
  int width;
  int height;

public:
  Level* parseLevel(const char* levelFile);
};

#endif // LEVELPARSERH
