#include "atkui/framework.h"
#include "atkmath/matrix3.h"
using namespace glm;
using atkmath::Deg2Rad;
using atkmath::Matrix3;
using atkmath::Vector3;

class Smiley : public atkui::Framework
{
public:
   Smiley() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
      theta = 0.0;
      thetaRate = 1.0;
   }

   virtual void scene() {
      theta += thetaRate * dt();

      float px = 10.0;
      float py = 10.0;
      
      float newAngle = 0.0;
      float newRad = 100;
      for(int i=0;i<10;i++){
         for(int j=0;j<36;j++){
            newAngle= ((3.142*10)/180)* j;
            px = newRad * cos(newAngle) + 0.5 * width() + 10;
            py = newRad * sin(newAngle) + 0.5 * height() + 10;

            Matrix3 rot;
            Vector3 euler(35, 45, 60);
            Vector3 anglesRad = euler * Deg2Rad;

            setColor(vec3(1, 0.5, 1)+agl::randomUnitVector()/2.0f);
            push();
            translate(vec3(px, py, 0));
            rotate(anglesRad[0]+theta, vec3(1, 0, 0));
            rotate(anglesRad[1]+theta, vec3(0, 1, 0));
            rotate(anglesRad[2]+theta, vec3(0, 0, 1));
            drawCone(vec3(0.5, 0.5, 0), 25);
            pop();
         } 
         newRad += 20; 
         newAngle = 0.0;
      }

   }
   private:
   float theta;
   float thetaRate;

};


int main(int argc, char** argv) {
   Smiley viewer;
   viewer.run();
   return 0;
}

