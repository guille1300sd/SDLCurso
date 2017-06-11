#ifndef LOADERPARAMSH
#define LOADERPARAMSH

#include <iostream>

using namespace std;

class LoaderParams{
private:
  int x;
  int y;

  int width;
  int height;

  string textureID;

  int numFrames;

  int callbackID;
  int animSpeed;
public:
  //Constructor
  LoaderParams(int x, int y, int width, int height, string textureID, int numFrames, int callbackID = 0, int animSpeed= 0)
  :x(x),y(y),width(width),height(height), textureID(textureID), numFrames(numFrames), callbackID(callbackID), animSpeed(animSpeed){}

  int getX() const { return x; }
  int getY() const { return y; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  string getTextureId() const { return textureID; }
  int getNumFrames() const { return numFrames; }
  int getCallBackID() const { return callbackID; }
  int getAnimSpeed() const { return animSpeed; }
};

#endif //LOADERPARAMSH
