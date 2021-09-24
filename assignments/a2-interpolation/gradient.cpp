#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }
  virtual void setup() {
    yellow = vec3(1, 1, 0);
    red = vec3(1, 0, 0);
    cyan = vec3(0, 1, 1);
    fuschia = vec3(1, 0, 1);
    
  }

  virtual void scene() {
    vec3 xColor1;
    vec3 xColor2;
    vec3 xColor;
    
    for(float i=0.5;i<10;i++){
      xColor2 = yellow *(1-(i*0.10f)) + cyan * i*0.10f;
      xColor1 = red *(1-(i*0.10f)) + fuschia * i*0.10f;

      for(float j=0.5;j<10;j++){
        xColor = xColor1 *(1-(j*0.10f)) + xColor2 *j*0.10f ;
        setColor(xColor);
        drawCube(vec3(width()*i*0.10, height()*j*0.10, 0), vec3(50, 50, 0));
      }
    }
    
  }

  private:
    vec3 yellow;
    vec3 red;
    vec3 cyan;
    vec3 fuschia;
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
