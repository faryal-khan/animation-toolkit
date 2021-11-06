#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class MotionViewer : public atkui::Framework
{

public:
   MotionViewer() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
   }

   void setupFileName(char* filename) {
      BVHReader reader;
      if(filename == NULL){
         reader.load("../motions/Beta/jump.bvh", skeleton, motion);
      }
      else{
         std::string name;
         name += filename;
         reader.load(name, skeleton, motion);
      }
      motion.update(skeleton, 0);
   }

   void scene() {
      if(!paused){
         time += dt() *timeScale;
         motion.update(skeleton, time);

      }
      else{
         if(period == true){
            if(time>motion.getNumKeys()-1){
               time = 0;
            }
            time+=dt();
            motion.update(skeleton, time);
            period = false;
         }

         if(comma == true){
            if(time<0){
               time = motion.getNumKeys()-1;
            }
            time-=dt();
            motion.update(skeleton, time);
            comma = false;
         
         }
      }
      if(r_brack == true){
         timeScale += 0.4;
         r_brack = false;
      }

      if(l_brack == true){
         
         timeScale = timeScale/2;
         l_brack = false;
      }

      if(z_pressed){
         motion.update(skeleton, 0);
         z_pressed = false;
      }

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

      drawText(paused? "Paused" : "Playing", 10, 15);
      drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
      drawText("Time scale: "+std::to_string(timeScale), 10, 55);


   }

   virtual void keyUp(int key, int mods) {
      if(key == GLFW_KEY_P){
         paused = !paused;
      }

      if(key == GLFW_KEY_0){
         z_pressed = true;
      }

      if(key == GLFW_KEY_PERIOD){
         period = true;
      }

       if(key == GLFW_KEY_COMMA){
         comma = true;
      }

      if(key == GLFW_KEY_RIGHT_BRACKET){
         r_brack = true;
      }

      if(key == GLFW_KEY_LEFT_BRACKET){
         l_brack = true;
      }

   }

private:
   Skeleton skeleton;
   Motion motion;

   float timeScale = 1.0f;
   int currentFrame = 0; 
   bool paused = false;
   float time = 0;
   bool z_pressed;
   bool period;
   bool comma; 
   bool r_brack;
   bool l_brack;
};


int main(int argc, char** argv) {
   char* file = argv[1];
   MotionViewer viewer;

   viewer.setupFileName(file);

   viewer.run();
}