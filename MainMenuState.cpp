#include "MainMenuState.h"

const std::string MainMenuState::menuID = "MENU";

void MainMenuState::update(){

  for(int i = 0; i<gameObjects.size(); i++){
      gameObjects[i]->update();
  }

}

void MainMenuState::render(){

    for(int i = 0; i<gameObjects.size(); i++){
        gameObjects[i]->draw();
    }

}

bool MainMenuState::onExit(){
  for(int i=0; i<gameObjects.size(); i++){
    gameObjects[i]->clean();
  }

  gameObjects.clear();

  //clear the texture Manager
  for(int i=0; i < textureIDsList.size(); i++){
    TheTextureManager::Instance()->clearFromTextureMap(textureIDsList[i]);
  }
  std::cout<<"Exit MenuState\n";
  return true;
}

bool MainMenuState::onEnter(){
    //parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml",menuID,&gameObjects,&textureIDsList);

    mcallbacks.push_back(0);
    mcallbacks.push_back(menuToPlay);
    mcallbacks.push_back(exitFromMenu);

    //set the callbacks for menu items
    setCallbacks(mcallbacks);

    std::cout << "entering menu State" << endl;
    return true;
}

void MainMenuState::menuToPlay(){
  TheGame::Instance()->changeStatePlay();
  std::cout << "Play button clicked" << endl;
}

void MainMenuState::exitFromMenu(){
  std::cout << "Exit button clicked" << endl;
  TheGame::Instance()->quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks){
  //go through the game objects
  for(int i = 0; i < gameObjects.size(); i++){
    //if they are of type MenuButton then assign a callback based on the id passed in from file
    if(dynamic_cast<MenuButton*>(gameObjects[i])){
      MenuButton* pbutton = dynamic_cast<MenuButton*>(gameObjects[i]);
      pbutton->setCallback(callbacks[pbutton->getCallBackID()]);
    }
  }
}
