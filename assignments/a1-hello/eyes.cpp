#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }

    virtual void setup(){
      theta = 0.0;
      thetaRate = 1.0;
    }


    virtual void scene() {
      theta += thetaRate * dt();
      float px1 = 30.0f * sin(theta) + 0.5 * width() - 60;
      float py1= height() * 0.5 + 10;

      setColor(vec3(0,0,0));
      double x1 = width() * 0.5 - 60;
      double y1 = height() * 0.5 + 10;
      double radius1 = 20; 
      double radius2 = 100;
      drawSphere(vec3(px1,py1,0), radius1);
      setColor(vec3(1,1,1));
      drawSphere(vec3(x1, y1, -500), radius2);

      float px2 = 30.0f * sin(theta) + 0.5 * width() + 60;
      float py2= height() * 0.5 + 10;
      setColor(vec3(0,0,0));
      double x2 = width() * 0.5 + 60;
      double y2 = height() * 0.5 + 10;
      double radius3 = 20; 
      double radius4 = 100;
      drawSphere(vec3(px2,py2,0), radius3);
      setColor(vec3(1,1,1));
      drawSphere(vec3(x2, y2, -500), radius4);

    }
    float theta;
    float thetaRate;
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
