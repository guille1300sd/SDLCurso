#include "Enemy.h"

Enemy::Enemy():SDLGameObject(){
}

void Enemy::draw(){
  SDLGameObject::draw();
}

void Enemy::update(){
  currentFrame = int (((SDL_GetTicks()/100) % numFrames));

  if(position.getY() < 0){
    velocity.setY(2);
  }
  else if(position.getY() > 400){
    velocity.setY(-2);
  }

  SDLGameObject::update();
}

void Enemy::clean(){
SDLGameObject::clean();
}

void Enemy::load(const LoaderParams* params){
  SDLGameObject::load(params);
  velocity.setY(2);
}
