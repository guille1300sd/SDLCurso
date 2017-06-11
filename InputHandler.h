#ifndef INPUTHANLDER
#define INPUTHANDLER

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "Vector2D.h"
#include "Game.h"

enum mouse_buttons{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};


class InputHandler{
private:
  const int joystickDeadZone = 10000;

  std::vector<SDL_Joystick*> joysticks;
  std::vector<std::pair<Vector2D*,Vector2D*> > joysticksValues;
  std::vector<std::vector<bool> > buttonStates;
  bool bJoysticksInitialised;

  std::vector<bool> mouseButtonStates;
  Vector2D* mousePosition;

  const Uint8* keystate;

  static InputHandler* s_pInstance;

  InputHandler();
  ~InputHandler(){}

  //private functions to handle different evet types


public:
  static InputHandler* Instance(){
    if(s_pInstance == 0){
      s_pInstance = new InputHandler();
    }
    return s_pInstance;
  }

  void update();
  void clean();

  void initialisedJoysticks();
  bool joysticksInitialised() { return bJoysticksInitialised;}

  int xvalue(int joy, int stick);
  int yvalue(int joy, int stick);

  bool getButtonState(int joy, int buttonNumber){
    return buttonStates[joy][buttonNumber];
  }

  bool getMouseButtonState(int buttonNumber){
    return mouseButtonStates[buttonNumber];
  }

  Vector2D* getMousePosition(){
    return mousePosition;
  }

  bool isKeyDown(SDL_Scancode key);

  void reset(){

    for(int i=0; i<mouseButtonStates.size(); i++){
      mouseButtonStates[i] = false;
    }

  }

};

typedef InputHandler TheInputHandler;

#endif //INPUTHANDLER
