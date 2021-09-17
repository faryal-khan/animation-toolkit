#include "atkui/framework.h"

using namespace glm;

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }
  struct Particle{
    vec3 currentPos;
    vec3 vel;
    vec3 color;
    float posX;
    float posY;
  };

  virtual void setup() {
    radius = 15.0; 
    direction = vec3(1, 3, 4);
    mainColor = vec3(0,0,1);

    for(int i = 0;i<200;i++){
      parts[i].vel = (float)(rand()%150) * direction;
      parts[i].color = mainColor + agl::randomUnitVector()/2.0f;
      parts[i].posX = randomNum(width());
      parts[i].posY = randomNum(height());
    
      parts[i].currentPos = vec3(parts[i].posX, parts[i].posY, i);
    }
  }

  float randomNum(int limit){
    return (float)(rand()%limit);
  }
  virtual void scene() {
    // currentPos = currentPos + vel * elapsedTime();
    // // colors are RGB triplets in range [0,1]
    // setColor(vec3(0,1,0));

    // // draw a sphere at center of screen
    // double radius = 20; 
    // drawSphere(currentPos, radius);
    
    for(int i=0;i<200;i++){

      parts[i].currentPos = parts[i].currentPos + parts[i].vel * dt();
      parts[i].vel += 0.3f;
      setColor(parts[i].color);

      if(parts[i].currentPos[0] >= width()){
        parts[i].currentPos = vec3(0.0, parts[i].posY, i);
      }
      if(parts[i].currentPos[1] >= height()){
        parts[i].currentPos = vec3(parts[i].posX, 0.0, i);
      }
      else{
      drawSphere(parts[i].currentPos, radius);
      }
    }
  }

  Particle parts[200];
  float radius;
  vec3 direction;
  vec3 mainColor;
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
