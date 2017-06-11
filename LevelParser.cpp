#include "LevelParser.h"

Level* LevelParser::parseLevel(const char* levelFile){

  //create a TinyXML document and load the map XML
  TiXmlDocument levelDocument;
  levelDocument.LoadFile(levelFile);

  //create the Level Object
  Level* level = new Level();

  //get The root node
  TiXmlElement* root = levelDocument.RootElement();

  root->Attribute("tilewidth", &tileSize);
  root->Attribute("width",&width);
  root->Attribute("height",&height);


  //we must parse the textures needed for this level, which have been added to properties
  for(TiXmlElement* e = root->FirstChildElement(); e!=NULL; e = e->NextSiblingElement()){
    if( e->Value() == std::string("properties")){
        for(TiXmlElement* ee = e->FirstChildElement(); ee != NULL; ee = ee->NextSiblingElement()){
            if(ee->Value() == std::string("property"))  parseTextures(ee);
        }
    }
  }


  //parse the tileSets
  for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
    if(e->Value() == std::string("tileset")){
      parseTileSets(e, level->getTilesets());
    }
  }

  //parse any object Layer
  for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
    if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")){

        if(e->FirstChildElement()->Value() == std::string("object")){
            parseObjectLayer(e,level->getLayers());
        }
        else if(e->FirstChildElement()->Value() == std::string("data")){
            parseTileLayer(e,level->getLayers(),level->getTilesets());
        }

    }
  }

  return level;
}

void LevelParser::parseTileSets(TiXmlElement* tileSetRoot, std::vector<Tileset>* tilesets){


  //first add the tileset to the texture manager
  TheTextureManager::Instance()->load(tileSetRoot->FirstChildElement()->Attribute("source"),
  tileSetRoot->Attribute("name"),TheGame::Instance()->getRenderer());

  //create a tileset object
  Tileset tileset;
  tileSetRoot->FirstChildElement()->Attribute("width",&tileset.width);
  tileSetRoot->FirstChildElement()->Attribute("height",&tileset.height);
  tileSetRoot->Attribute("firstgid",&tileset.firstGridID);
  tileSetRoot->Attribute("tilewidth",&tileset.tileWidth);
  tileSetRoot->Attribute("tileheight",&tileset.tileHeight);
  tileSetRoot->Attribute("spacing",&tileset.spacing);
  tileSetRoot->Attribute("margin",&tileset.margin);
  tileset.name = tileSetRoot->Attribute("name");

  tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

  tilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* tileElement, std::vector<Layer*>* layers, const std::vector<Tileset>* tilesets){
  TileLayer* tileLayer = new TileLayer(tileSize,*tilesets);
  //tile data
  std::vector<std::vector<int> > data;

  std::string decodedIDs;
  TiXmlElement* dataNode;

  for(TiXmlElement* e = tileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
    if(e->Value() == std::string("data")){
      dataNode = e;
    }
  }


  for(TiXmlNode* e = dataNode->FirstChild(); e != NULL; e = e->NextSibling()){
    TiXmlText* text  = e->ToText();
    std::string t = text->Value();
    decodedIDs = base64_decode(t);
  }

  //uncompress zlib compression
  uLongf numGids = width * height * sizeof(int);
  std::vector<unsigned> gids(numGids);
  uncompress((Bytef*)&gids[0],&numGids,(const Bytef*) decodedIDs.c_str(),decodedIDs.size());

  std::vector<int> layerRow(width);

  for(int j=0; j<height; j++){
    data.push_back(layerRow);
  }

  for(int rows = 0; rows < height; rows++){
    for(int cols = 0; cols < width; cols++){
      data[rows][cols] = gids[rows * width + cols];
    }
  }

  tileLayer->setTileIDs(data);

  layers->push_back(tileLayer);
}

void LevelParser::parseTextures(TiXmlElement* textureRoot){

    std::cout << textureRoot->Attribute("value") << endl;

    TheTextureManager::Instance()->load(textureRoot->Attribute("value"),textureRoot->Attribute("name"),
    TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* objectElement, std::vector<Layer*>* layers){
    //Create an Object Layer
    ObjectLayer* objectLayer = new ObjectLayer();

    std::cout << objectElement->FirstChildElement()->Value() << endl;

    for(TiXmlElement* e = objectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        std::cout << e->Value();

        if(e->Value() == std::string("object")){
            int x,y, width, height, numFrames, callbackID, animSpeed;
            std::string textureID;

            //get the initial node values type, x and y
            e->Attribute("x",&x);
            e->Attribute("y",&y);

            GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));

            //get the property values
            for(TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement()){

                if(properties->Value() == std::string("properties")){
                    for(TiXmlElement* property = properties->FirstChildElement(); property != NULL;
                    property = property->NextSiblingElement()){

                        if(property->Value() == std::string("property")){
                            if(property->Attribute("name") == std::string("numFrames")){
                                property->Attribute("value",&numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight")){
                                property->Attribute("value",&height);
                            }
                            else if(property->Attribute("name") == std::string("textureID")){
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth")){
                                property->Attribute("value",&width);
                            }
                             else if(property->Attribute("name") == std::string("callbackID")){
                                property->Attribute("value",&callbackID);
                            }
                             else if(property->Attribute("name") == std::string("animSpeed")){
                                property->Attribute("value",&animSpeed);
                            }
                        }//FIN DE LAS PROPERTY

                    }//FOR DE LAS PROPERTY
                }//IF de las properties

            }
            pGameObject->load(new LoaderParams(x,y,width,height,textureID,numFrames,callbackID,animSpeed));
            objectLayer->getGameObjects()->push_back(pGameObject);
        }
    }

    layers->push_back(objectLayer);
}
