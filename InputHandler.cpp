#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler(){
   for(int i=0; i<3; i++){
     mouseButtonStates.push_back(false);
   }

   mousePosition = new Vector2D(0,0);
}

void InputHandler::initialisedJoysticks(){

  if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  }

  if(SDL_NumJoysticks() > 0){

    for(int i=0; i< SDL_NumJoysticks(); i++){
        SDL_Joystick* joy = SDL_JoystickOpen(i);

        if(SDL_JoystickGetAttached(joy)){
          joysticks.push_back(joy);
          joysticksValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));

          std::vector<bool> tempButtons;
          for(int j=0; j<SDL_JoystickNumButtons(joy); j++){
              tempButtons.push_back(false);
          }
          buttonStates.push_back(tempButtons);

        }
        else{
          std::cout << SDL_GetError();
        }
    }

    SDL_JoystickEventState(SDL_ENABLE);
    bJoysticksInitialised = true;
    std::cout << "Initialised " << joysticks.size() << " joystick(s)";
  }
  else{
    bJoysticksInitialised = false;
  }

}

void InputHandler::clean(){
    if(bJoysticksInitialised){
      for(int i=0; i<SDL_NumJoysticks(); i++){
        SDL_JoystickClose(joysticks[i]);
      }
    }
}

void InputHandler::update(){
  SDL_Event event;

  keystate = SDL_GetKeyboardState(0);

  while(SDL_PollEvent(&event)){

    if(event.type == SDL_QUIT){
        TheGame::Instance()->quit();
    }

//-----------------Mouse event-------------------------------------------------------------------------
    if(event.type == SDL_MOUSEBUTTONDOWN){

      if(event.button.button == SDL_BUTTON_LEFT){
          mouseButtonStates[LEFT] = true;
      }

      if(event.button.button == SDL_BUTTON_MIDDLE){
          mouseButtonStates[MIDDLE] = true;
      }

      if(event.button.button == SDL_BUTTON_RIGHT){
          mouseButtonStates[RIGHT] = true;
      }

    }

    if(event.type == SDL_MOUSEBUTTONUP){

      if(event.button.button == SDL_BUTTON_LEFT){
          mouseButtonStates[LEFT] = false;
      }

      if(event.button.button == SDL_BUTTON_MIDDLE){
          mouseButtonStates[MIDDLE] = false;
      }

      if(event.button.button == SDL_BUTTON_RIGHT){
          mouseButtonStates[RIGHT] = false;
      }

    }

    if(event.type == SDL_MOUSEMOTION){
      mousePosition->setX(event.motion.x);
      mousePosition->setY(event.motion.y);
    }
//---------------------------------------------------------------------------------------------------

    if(event.type == SDL_JOYAXISMOTION){
      int whichOne = event.jaxis.which;

      //Left stick move left or right
      if(event.jaxis.axis == 0){
        if(event.jaxis.value > joystickDeadZone) joysticksValues[whichOne].first->setX(1);
        else if(event.jaxis.value < -joystickDeadZone) joysticksValues[whichOne].first->setX(-1);
        else joysticksValues[whichOne].first->setX(0);
      }

      //left stick move up or down
      if(event.jaxis.axis == 1){
        if(event.jaxis.value > joystickDeadZone) joysticksValues[whichOne].first->setY(1);
        else if(event.jaxis.value < -joystickDeadZone) joysticksValues[whichOne].first->setY(-1);
        else joysticksValues[whichOne].first->setY(0);
      }

      //Rigth stick move left or right
      if(event.jaxis.axis == 3){
        if(event.jaxis.value > joystickDeadZone) joysticksValues[whichOne].second->setX(1);
        else if(event.jaxis.value < -joystickDeadZone) joysticksValues[whichOne].second->setX(-1);
        else joysticksValues[whichOne].second->setX(0);
      }

      //Right stick move up or down
      if(event.jaxis.axis == 4){
        if(event.jaxis.value > joystickDeadZone) joysticksValues[whichOne].second->setY(1);
        else if(event.jaxis.value < -joystickDeadZone) joysticksValues[whichOne].second->setY(-1);
        else joysticksValues[whichOne].second->setY(0);
      }
    }

  }
}

int InputHandler::xvalue(int joy, int stick){

  if(joysticksValues.size() > 0){
      if(stick == 1){
        return joysticksValues[joy].first->getX();
      }
      else if(stick == 2){
        return joysticksValues[joy].second->getX();
      }
  }

  return 0;
}

int InputHandler::yvalue(int joy, int stick){

  if(joysticksValues.size() > 0){
      if(stick == 1){
        return joysticksValues[joy].first->getY();
      }
      else if(stick == 2){
        return joysticksValues[joy].second->getY();
      }
  }

  return 0;
}

bool InputHandler::isKeyDown(SDL_Scancode key){
  if(keystate != 0){
    if(keystate[key] == 1){
      return true;
    }
    else{
      return false;
    }
  }

  return false;
}
