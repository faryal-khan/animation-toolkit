#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }

  virtual void setup(){
    currentPos = vec3(0, 1, -4);
    vel = agl::randomUnitVector() * 50.0f; 
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(currentPos, radius);

    if(spacePressed){
      currentPos = currentPos + vel * dt();
    }

    if(rPressed){
      currentPos = vec3(0, 1, -4);
      vel = agl::randomUnitVector() * 100.0f; 
    }
    
  }

  void keyUp(int key, int mods){
    if(key == GLFW_KEY_SPACE){
      spacePressed = true;
      rPressed = false;
    }

    if(key == GLFW_KEY_R){
      rPressed = true;
      spacePressed = false;
    }
  }

 vec3 currentPos;
 vec3 vel;
 bool spacePressed = false;
 bool rPressed = false;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
