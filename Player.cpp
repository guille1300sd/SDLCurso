#include "Player.h"
#include "InputHandler.h"

Player::Player(): SDLGameObject(){

}

void Player::draw(){
  SDLGameObject::draw();
}

void Player::update(){

  velocity.setX(0);
  velocity.setY(0);

  handleInput();

  currentFrame = int (((SDL_GetTicks()/100)%6));

  SDLGameObject::update();
}

void Player::clean(){

}

void Player::load(const LoaderParams* params){
  SDLGameObject::load(params);
}

void Player::handleInput(){
/*
  if(TheInputHandler::Instance()->joysticksInitialised()){

    if(TheInputHandler::Instance()->xvalue(0,1)>0 || TheInputHandler::Instance()->xvalue(0,1)<0){
        velocity.setX(1* TheInputHandler::Instance()->xvalue(0,1));
    }

    if(TheInputHandler::Instance()->yvalue(0,1)>0 || TheInputHandler::Instance()->yvalue(0,1)<0){
        velocity.setY(1* TheInputHandler::Instance()->yvalue(0,1));
    }

    if(TheInputHandler::Instance()->xvalue(0,2)>0 || TheInputHandler::Instance()->xvalue(0,2)<0){
        velocity.setX(1* TheInputHandler::Instance()->xvalue(0,2));
    }

    if(TheInputHandler::Instance()->yvalue(0,2)>0 || TheInputHandler::Instance()->yvalue(0,2)<0){
        velocity.setY(1* TheInputHandler::Instance()->yvalue(0,2));
    }

  }
*/

  //if(TheInputHandler::Instance()->getMouseButtonState(LEFT)){
  //  velocity.setX(1);
  //}

//---------------------Para que siga al mouse---------------------------------------------------------------------------
  Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
  velocity = (*vec - position) / 50;
//-------------------------------------------------------------------------------------------------------------------

/*  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)){
    velocity.setX(-2);
  }
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
    velocity.setX(2);
  }
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
    velocity.setY(-2);
  }
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)){
    velocity.setY(2);
  }

  if(position.getX()>640) position.setX(-width);
*/
}
