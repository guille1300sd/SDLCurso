#ifndef GAMEH
#define GAMEH

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameObject.h"
#include "GameStateMachine.h"

#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Enemy.h"
#include "Player.h"
#include "AnimatedGraphic.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"

class Game{
private:
  bool running;

  SDL_Window* window;
  SDL_Renderer* renderer;

  int gameheight, gamewidth;
//-------------------------------------------------------------
  vector<GameObject*> gameObjects;
  GameStateMachine* pGameStateMachine;
//----------------------------------------------------------------
  Game(){}
  static Game* s_pInstance;
public:

  ~Game();

  bool init(char const * title, int posx, int posy, int height, int width, bool fullscreen);

  void render();
  void update();
  void handleEvents();
  void clean();

  void quit(){ running = false; SDL_Quit();}

  bool isRunning(){ return running;}
  SDL_Renderer* getRenderer(){ return renderer; }

  GameStateMachine* getStateMachine() { return pGameStateMachine; }

//Metodos para cambiar el GAMESTATE------------------------------------------------------------------------------------------------
  void changeStateMenu();
  void changeStatePlay();
  void changeStatePause();
  void changeStateGameOver();
//----------------------------------------------------------------------------------------------------------------------------
  static Game* Instance(){
    if(s_pInstance == 0){
      s_pInstance = new Game();
      return s_pInstance;
    }
    else{
      return s_pInstance;
    }
  }

  int getGameWidth() { return gamewidth; }
  int getGameHeight() { return gameheight; }
};

typedef Game TheGame;

#endif //GAMEH
