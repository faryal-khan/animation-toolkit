#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
    theta = 0.0;
    yPos = height() * 0.5 + 10;
    xPos1 = width() * 0.5 - 60;
    xPos2 = width() * 0.5 + 60;
    

  }

  virtual void scene() {
    mainAngle = atan2 (_mouseY, _mouseX);
    int dx = mousePosition().x - _mouseX;
    int dy = mousePosition().y - _mouseY;
    mouseMotion(mousePosition().x, mousePosition().y, dx, dy);
    vec3 target = vec3(_mouseX, _mouseY, 0);
    setColor(vec3(1,0,0));
    drawSphere(target, 5);
    

    double radius1 = 20; 
    double radius2 = 100;
    setColor(vec3(1,1,1));
    drawSphere(vec3(xPos1, yPos, -500), radius2);

    double radius3 = 20; 
    double radius4 = 100;
    setColor(vec3(1,1,1));
    drawSphere(vec3(xPos2, yPos, -500), radius4);

    int newPosY = radius3 * sin(mainAngle) + 0.5 * height();
    int newPosX = radius3 * cos(mainAngle) + 0.5 * width() - 60;
    setColor(vec3(0,0,0));
    drawSphere(vec3(newPosX, newPosY, 0), radius3);

    int newPosY2 = radius3* sin(mainAngle) + 0.5 * height();
    int newPosX2 = radius3 * cos(mainAngle) + 0.5 * width()+ 60;
    setColor(vec3(0,0,0));
    drawSphere(vec3(newPosX2, newPosY2, 0), radius3);

  }

  void mouseMotion(int x, int y, int dx, int dy) {
    _mouseX = x;
    _mouseY = height() - y;
  }

 private:
  int _mouseX;
  int _mouseY;
  int yPos;
  int xPos1;
  int xPos2;
  float theta;
  float mainAngle;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
