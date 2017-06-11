#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* state){
    gameStates.push_back(state);
    gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* state){
  if(!gameStates.empty()){

    if(gameStates.back()->getStateId() == state->getStateId()){
      return; //do nothing
    }

    if(gameStates.back()->onExit()){
      delete gameStates.back(); //no se por que con esto no funciona
      gameStates.pop_back();
    }

  }
    gameStates.push_back(state);
    gameStates.back()->onEnter();

}

void GameStateMachine::popState(){
  if(!gameStates.empty()){
    if(gameStates.back()->onExit()){
      delete gameStates.back();
      gameStates.pop_back();
    }
  }
}

void GameStateMachine::update(){
  if(!gameStates.empty()){
    gameStates.back()->update();
  }
}

void GameStateMachine::render(){
  if(!gameStates.empty()){
    gameStates.back()->render();
  }
}
