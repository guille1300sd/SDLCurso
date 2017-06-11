#ifndef MENUBUTTONH
#define MENUBUTTONH

#include "SDLGameObject.h"
#include "GameObjectFactory.h"


class MenuButton : public SDLGameObject{

private:

//Variable para manejar los CLICKED
bool released;

//Estados que puede tener el boton--------------------------------------------------------
  enum button_state{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
  };
//---------------------------------------------------------------------------------------------
//Puntero a funcion---------------------------------------------------------------------------------
void (*pcallback) ();

public:
  MenuButton();

  virtual void draw();
  virtual void update();
  virtual void clean();

  virtual void load(const LoaderParams* params);

  void setCallback(void (*callback)()) { pcallback = callback; }
  int getCallBackID() { return callbackID; }
};

class MenuButtonCreator : public BaseCreator{
public:
  GameObject* createGameObject() const{
    return new MenuButton();
  }
};

#endif //MENUBUTTONH
