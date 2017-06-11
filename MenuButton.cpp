#include "MenuButton.h"

#include "InputHandler.h"

MenuButton::MenuButton(): SDLGameObject(), pcallback(){

}

void MenuButton::draw(){
  SDLGameObject::draw();
}

void MenuButton::update(){
  Vector2D* mousepos = TheInputHandler::Instance()->getMousePosition();

//------------------------------------------------------------------------------------------------------------------
  if(mousepos->getX() < (position.getX() + width) && mousepos->getX() > position.getX() &&
     mousepos->getY() < (position.getY() + height) && mousepos->getY() > position.getY()){

    if(TheInputHandler::Instance()->getMouseButtonState(LEFT) && released){
      currentFrame = CLICKED;

      pcallback(); //llamamos a la funcion si se hizo click

      released = false;
    }
    else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT)){
      released = true;
      currentFrame = MOUSE_OVER;
    }
  }
//---------------------------------------------------------------------------------------------------------------------------------
  else{
    currentFrame = MOUSE_OUT;
  }
}

void MenuButton::clean(){
  SDLGameObject::clean();
}

void MenuButton::load(const LoaderParams* params){
  SDLGameObject::load(params);
  callbackID = params->getCallBackID();
  currentFrame = MOUSE_OUT; //start at frame 0
}
