#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "Game.h"

using namespace std;

#include "tinyxml/tinyxmlerror.cpp"
#include "tinyxml/tinyxmlparser.cpp"
#include "tinyxml/tinystr.cpp"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.cpp"

#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"


const int FPS = 60;
const int DELAY_TIME = 1000.0f /  FPS;

#undef main

int main(int argc, char const *argv[]) {

  Uint32 frameStart, frameTime;

  //Para poder imprimir por consola----------------------------------------
      AllocConsole();
      freopen( "CON", "w", stdout );
//----------------------------------------------------------------------------

  if(TheGame::Instance()->init("Chapter 1: Seccion 7",100,100,640,480,false)){

    while(TheGame::Instance()->isRunning()){
      frameStart = SDL_GetTicks();

      TheGame::Instance()->update();
      TheGame::Instance()->handleEvents();
      TheGame::Instance()->render();

      frameTime = SDL_GetTicks() - frameStart;

      if(frameTime < DELAY_TIME){
        SDL_Delay((int) (DELAY_TIME - frameTime));
      }
    }
  }
  else{
    return -1;
  }

  TheGame::Instance()->clean();

  return 0;
}
