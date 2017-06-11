#include "Game.h"

#include "InputHandler.h"

using namespace std;

Game* Game::s_pInstance = 0;

Game::~Game(){
}

/*
Inicia los componentes SDL para para la aplicacion
*/
bool Game::init(char const * title, int posx, int posy, int height, int width, bool fullscreen){

  int flags = 0;
  if(fullscreen) flags = SDL_WINDOW_FULLSCREEN;

   if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

     cout << "SDL Init success" << endl;
     window = SDL_CreateWindow(title,posx,posy,height,width,flags);

     gamewidth = width;
     gameheight = height;

     if(window != 0){
       cout << "Window creation success" << endl;
       renderer = SDL_CreateRenderer(window,-1,0);
//-----------------------------------------------------------------------------------
SDL_SetRenderDrawColor(renderer,0,0,0,255);
       if(renderer != 0){
         cout << "Renderer creation success" << endl;

         //-------------------------------Dibujando la imagen------------------------------------
/*         if(!TheTextureManager::Instance()->load("assets/spriteSheet.png","animate",renderer)){
           return false;
         }
*/
         //----------------------------Register the object in GAME OBJECT FACTORY---------------------------------------------
          TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
          TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
          TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
          TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
         //------------------------------Inicializando el Input Handler--------------------------------------------------------
         TheInputHandler::Instance()->initialisedJoysticks();
         //------------------------------------------GAME STATE MACHINE----------------------------------------------------------
         pGameStateMachine = new GameStateMachine();
         pGameStateMachine->changeState(new MainMenuState());

         //------------------------------------------------------------------------------------------------------------------
       }else{
         cout << "Renderer init fail" << endl;
         return false;
       }
//-------------------------------------------------------------------------------
     }
     else{
       cout << "Window init fail" << endl;
       return false;
     }
   }
   else{
     cout << "SDL Init Fail" << endl;
     return false;
   }

   cout << "Init success" << endl;
   running = true;

   return true;
}

//Limpia el render y lo actualiza
void Game::render(){
  SDL_RenderClear(renderer);

  pGameStateMachine->render();

  SDL_RenderPresent(renderer);
}

void Game::update(){
  pGameStateMachine->update();
}

//
void Game::handleEvents(){
  TheInputHandler::Instance()->update();

}

//Cierra todos los componentes y cierra SDL
void Game::clean(){
  cout << "Cleaning Game" << endl;
  TheInputHandler::Instance()->clean();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::changeStateMenu(){
  pGameStateMachine->changeState(new MainMenuState());
}

void Game::changeStatePause(){
  pGameStateMachine->pushState(new PauseState());
}

void Game::changeStatePlay(){
  pGameStateMachine->changeState(new PlayState());
}

void Game::changeStateGameOver(){
  pGameStateMachine->pushState(new GameOverState());
}
