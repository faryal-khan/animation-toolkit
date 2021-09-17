#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
      theta = 0.0;
      thetaRate = 0.5;
      r = 0.0;
   }

   virtual void scene() {
      theta += thetaRate * dt();
      float px = 0.0;
      float py = 0.0;
      
      float newAngle = 0.0;
      float newRad = r;
      for(int i=0;i<20;i++){
         for(int j=0;j<36;j++){
            vec3 color= pallet[i];
            if(i%2 == 0){
               newAngle= ((3.142*10)/180)* j + theta;
            }
            else{
               newAngle= ((3.142*10)/180) * j + (theta*-1);
            } 
           
            px = newRad * cos(newAngle) + 0.5 * width() + 10;
            py = newRad * sin(newAngle) + 0.5 * height() + 10;
            
            setColor(color);
            drawSphere(vec3(px, py, 0), 10);
         } 
         newRad += 20; 
         newAngle = 0.0;
      }
   
      
   }

private:
float theta;
float thetaRate;
float r;


vec3 pallet [20]=
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
       vec3(255,162,58)/255.0f

   };

};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
