#ifndef GAMEOBJECTFACTORY
#define GAMEOBJECTFACTORY

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator{

public:
  virtual GameObject* createGameObject() const = 0;
  virtual ~BaseCreator() {}
};

class GameObjectFactory{

private:
  std::map<std::string,BaseCreator*> m_creators;
  static GameObjectFactory* s_pInstance;
  GameObjectFactory() {}
public:
//----------------------------------------------------------------------------------------------------------------------
  bool registerType(std::string typeID, BaseCreator* pCreator){
      std::map<std::string,BaseCreator*>::iterator it = m_creators.find(typeID);

      //IF the type is ready register, do nothing
      if(it != m_creators.end()){
        delete pCreator;
        return false;
      }

      m_creators[typeID] = pCreator;

      return true;
  }
//------------------------------------------------------------------------------------------------------------
  GameObject* create(std::string typeID){
    std::map<std::string,BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end()){
      std::cout << "could not find type: " << typeID << endl;
      return NULL;
    }

    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
  }
//------------------------------------------------------------------------------------------------------------------

static GameObjectFactory* Instance(){
    if(s_pInstance == 0){
      s_pInstance  = new GameObjectFactory();
      return s_pInstance;
    }
    return s_pInstance;
}

};

typedef GameObjectFactory TheGameObjectFactory;

#endif //GAMEOBJECTFACTORY
