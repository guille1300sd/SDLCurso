#include "PauseState.h"
#include "InputHandler.h"

const std::string PauseState::pauseID = "PAUSE";

void PauseState::pauseToMain(){
  TheGame::Instance()->changeStateMenu();
}

void PauseState::resumePlay(){
  TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update(){
  for(int i=0; i<gameObjects.size(); i++){
    gameObjects[i]->update();
  }
}

void PauseState::render(){
  for(int i=0; i<gameObjects.size(); i++){
    gameObjects[i]->draw();
  }
}

bool PauseState::onEnter(){

    StateParser stateParser;
    stateParser.parseState("test.xml",pauseID,&gameObjects,&textureIDsList);

    mcallbacks.push_back(0);
    mcallbacks.push_back(pauseToMain);
    mcallbacks.push_back(resumePlay);

    setCallbacks(mcallbacks);

    std::cout << "entering PauseState" << endl;
    return true;
}

bool PauseState::onExit(){
  for(int i=0; i<gameObjects.size(); i++){
    gameObjects[i]->clean();
  }
  gameObjects.clear();

  //clear the texture Manager
  for(int i=0; i < textureIDsList.size(); i++){
    TheTextureManager::Instance()->clearFromTextureMap(textureIDsList[i]);
  }

  //reset the mouse button states to false
  TheInputHandler::Instance()->reset();

  std::cout << "exiting PauseState" << endl;
  return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks){
  //go through the game objects
  for(int i = 0; i < gameObjects.size(); i++){
    //if they are of type MenuButton then assign a callback based on the id passed in from file
    if(dynamic_cast<MenuButton*>(gameObjects[i])){
      MenuButton* pbutton = dynamic_cast<MenuButton*>(gameObjects[i]);
      pbutton->setCallback(callbacks[pbutton->getCallBackID()]);
    }
  }
}
