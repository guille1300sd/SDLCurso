#include "GameOverState.h"

const std::string GameOverState::gameOverID = "GAMEOVER";

void GameOverState::gameOverToMain(){
  TheGame::Instance()->changeStateMenu();
}

void GameOverState::restartPlay(){
  TheGame::Instance()->changeStatePlay();
}

void GameOverState::render(){
  for(int i=0; i<gameObjects.size(); i++){
    gameObjects[i]->draw();
  }
}

void GameOverState::update(){
  for(int i=0; i<gameObjects.size(); i++){
    gameObjects[i]->update();
  }
}

bool GameOverState::onEnter(){

  //parse the state
  StateParser stateParser;
  stateParser.parseState("test.xml",gameOverID,&gameObjects,&textureIDsList);

  mcallbacks.push_back(0);
  mcallbacks.push_back(gameOverToMain);
  mcallbacks.push_back(restartPlay);

  setCallbacks(mcallbacks);

  std::cout << "entering PauseState" << endl;
  return true;
}

bool GameOverState::onExit(){
  for(int i=0; i<gameObjects.size(); i++){
    gameObjects[i]->clean();
  }
  gameObjects.clear();

    //clear the texture Manager
    for(int i=0; i < textureIDsList.size(); i++){
      TheTextureManager::Instance()->clearFromTextureMap(textureIDsList[i]);
    }

  std::cout << "Exiting GameOverState" << endl;
  return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks){
  //go through the game objects
  for(int i = 0; i < gameObjects.size(); i++){
    //if they are of type MenuButton then assign a callback based on the id passed in from file
    if(dynamic_cast<MenuButton*>(gameObjects[i])){
      MenuButton* pbutton = dynamic_cast<MenuButton*>(gameObjects[i]);
      pbutton->setCallback(callbacks[pbutton->getCallBackID()]);
    }
  }
}
