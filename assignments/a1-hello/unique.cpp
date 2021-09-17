#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
     theta = 0.0;
     thetaRate = 1.0;
     r = 50.0;
  }

  virtual void scene() {
    theta += thetaRate * dt();
      float px = r * cos(theta) + 0.5 * width();
      float py = r * sin(theta) + 0.5 * height();
      // setColor(vec3(0,1,0));
      // drawSphere(vec3(px, py, 0), 10);

      float newAngle = 0.0;
      float newRad = r;
      for(int i=0;i<36;i++){
         newRad += 10; 
         for(int j=0;j<36;j++){
            newAngle= ((3.142*10)/180) * 10 * j + theta;
            px = newRad * cos(newAngle) + 0.5 * width() + 10;
            py = newRad * sin(newAngle) + 0.5 * height() + 10;
            setColor(pallet[i]);
            drawSphere(vec3(px, py, 0), 10);
         } 
         newAngle = 0.0;
      }
  }
   private:
    float theta;
    float thetaRate;
    float r;
    vec3 pallet [40]=
    {
       vec3(0,165,227)/255.0f,
       vec3(141,215,191)/255.0f,
       vec3(255,150,197)/255.0f,
       vec3(255,87,104)/255.0f,
       vec3(255,162,58)/255.0f,
       vec3(0,165,227)/255.0f,
       vec3(141,215,191)/255.0f,
       vec3(255,150,197)/255.0f,
       vec3(255,87,104)/255.0f,
       vec3(255,162,58)/255.0f,
       vec3(0,165,227)/255.0f,
       vec3(141,215,191)/255.0f,
       vec3(255,150,197)/255.0f,
       vec3(255,87,104)/255.0f,
       vec3(255,162,58)/255.0f,
       vec3(0,165,227)/255.0f,
       vec3(141,215,191)/255.0f,
       vec3(255,150,197)/255.0f,
       vec3(255,87,104)/255.0f,
       vec3(255,162,58)/255.0f,
       vec3(0,165,227)/255.0f,
       vec3(141,215,191)/255.0f,
       vec3(255,150,197)/255.0f,
       vec3(255,87,104)/255.0f,
       vec3(255,162,58)/255.0f,
       vec3(0,165,227)/255.0f,
       vec3(141,215,191)/255.0f,
       vec3(255,150,197)/255.0f,
       vec3(255,87,104)/255.0f,
       vec3(255,162,58)/255.0f

   };
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}
