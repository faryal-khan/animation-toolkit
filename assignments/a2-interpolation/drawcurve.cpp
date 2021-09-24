#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);

    if(onepr){
      vec3 pos;
      for(float t=0.0;t<=1.0;t+=0.001){
          float current = 1-t;
          float first = std::pow(current,3);
          float second = 3*t* std::pow(current,2) ;
          float third = 3* std::pow(t, 2) * current;
          float fourth = std::pow(t, 3);
          pos = (first * B0) + (second *B1) + (third *B2) + (fourth *B3) ;
          setColor(vec3(0, 0, 1));
          drawSphere(pos, 2);
       }
    }

    if(twopr){
      vec3 pos;
      for(float t=0.0;t<=1.0;t+=0.001){
          float current = 1.0-t;

          //Level 1

          vec3 b10 = (B0*current) + (B1*t);
          vec3 b11 = (B1*current) + (B2*t);
          vec3 b12 = (B2*current) + (B3*t);

          //Level 2

          vec3 b20 = (b10*current) + (b11*t);
          vec3 b21 = (b11*current) + (b12*t);

          //Level 3

          vec3 b30 = (b20 *current) + (b21 *t);
          setColor(vec3(0, 0, 1));
          drawSphere(b30, 2);
       }

    }

  }
  
  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      onepr= true;
      twopr= false;
    }
    else if (key == GLFW_KEY_2) {
      onepr = false;
      twopr = true;
    }
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
  bool onepr;
  bool twopr;

};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}

