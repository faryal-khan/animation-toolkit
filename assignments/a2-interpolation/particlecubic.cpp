#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    t = 0.0;
    pos = vec3(0, 1, -4);
  }

  void scene() {

    vec3 pos1;
      for(float t=0.0;t<=1.0;t+=0.001){
          float current = 1-t;
          float first = std::pow(current,3);
          float second = 3*t* std::pow(current,2) ;
          float third = 3* std::pow(t, 2) * current;
          float fourth = std::pow(t, 3);
          pos1 = (first * B0) + (second *B1) + (third *B2) + (fourth *B3) ;
          setColor(vec3(0, 1, 1));
          drawSphere(pos1, 2);
       }


    if(t<=1){
      t += 0.005;
    }
    else{
      t = 0.0;
      pos = vec3(0, 1, -4);
    }

    float current = 1-t;
    float first = std::pow(current,3);
    float second = 3*t* std::pow(current,2);
    float third = 3* std::pow(t, 2) * current;
    float fourth = std::pow(t, 3);
    pos = (first * B0) + (second *B1) + (third *B2) + (fourth *B3);
    setColor(vec3(0, 0, 1));
    drawSphere(pos, 15);
       
  }

  private:
    vec3 pos;
    float t;
    vec3 B0 = vec3(100,  50, 0);
    vec3 B1 = vec3(150, 200, 0);
    vec3 B2 = vec3(250, 100, 0);
    vec3 B3 = vec3(300, 300, 0);
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}

