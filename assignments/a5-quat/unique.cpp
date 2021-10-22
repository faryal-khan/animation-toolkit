#include "atkui/framework.h"
using namespace glm;

#include "atkui/framework.h"
#include "atkmath/matrix3.h"
using namespace glm;
using atkmath::Deg2Rad;
using atkmath::Matrix3;
using atkmath::Vector3;

class Cubes : public atkui::Framework
{
public:
   Cubes() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
      mainAngle = 1.0;
  
   }

  virtual void scene() {
    
    for(float i=0.5;i<40;i++){
        for(float j=0.5;j<40;j++){
            
            int dx = mousePosition().x - _mouseX;
            int dy = mousePosition().y - _mouseY;
            mouseMotion(mousePosition().x, mousePosition().y, dx, dy);
            vec3 target = vec3(_mouseX, _mouseY, 0);
            setColor(vec3(1,0,0));
            drawSphere(target, 15);

            float newPosY = i*height()/40 ;
            float newPosX = j*width()/40 ;

            setColor(vec3(1,0,0));
            push();
               translate(vec3(newPosX, newPosY, 0));
               mainAngle = atan2(target[1]-newPosY, target[0]-newPosX);
               rotate(mainAngle, vec3(1, 0, 0));
               drawCube(vec3(0, 0, 0), vec3(30, 3, 0));
            pop();
        }
    }
}

void mouseMotion(int x, int y, int dx, int dy) {
    _mouseX = x;
    _mouseY = height() - y;
}


private:
  int _mouseX;
  int _mouseY;
  float mainAngle;

};


int main(int argc, char** argv) {
   Cubes viewer;
   viewer.run();
   return 0;
}

