#include "atkui/framework.h"
using namespace glm;

class Screensaver : public atkui::Framework {

struct Curve {
  vec3 color;
  vec3 B0, B1, B2, B3;
};

 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    t = 0.0;

    before.B0 = vec3(randomNum(400), randomNum(400), 0);
    before.B1  = vec3(randomNum(400), randomNum(400), 0);
    before.B2  = vec3(randomNum(400), randomNum(400), 0);
    before.B3  = vec3(randomNum(400), randomNum(400), 0);
    before.color = agl::randomUnitVector()*3.0f;

    after.B0 = vec3(randomNum(400), randomNum(400), 0);
    after.B1  = vec3(randomNum(400), randomNum(400), 0);
    after.B2  = vec3(randomNum(400), randomNum(400), 0);
    after.B3  = vec3(randomNum(400), randomNum(400), 0);
    after.color = agl::randomUnitVector()*3.0f;

  }

  void scene() {
    
    Curve curr;
    curr.B0 = before.B0*(1-(t)) + after.B0 *t;
    curr.B1 = before.B1 *(1-(t)) + after.B1 *t;
    curr.B2 = before.B2 *(1-(t)) + after.B2 *t;
    curr.B3 = before.B3 *(1-(t)) + after.B3 *t;

    curr.color = before.color *(1-(t)) + after.color *t;

    if(t>1){
      t = 0.0;
      before = after;
      after.B0 = vec3(randomNum(400), randomNum(400), 0);
      after.B1  = vec3(randomNum(400), randomNum(400), 0);
      after.B2  = vec3(randomNum(400), randomNum(400), 0);
      after.B3 = vec3(randomNum(400), randomNum(400), 0);
      after.color = agl::randomUnitVector()*3.0f;

    }
    else{
      index++;
      t += 0.01;
      if(index ==10){
      curves.push_back(curr);
      
      if (curves.size() >= 50){
        curves.pop_front();
      }
      index = 0;
      }
    }

    
    for(Curve& pres : curves){
      for(float i=0.0;i<1.0;i+=0.01){
          drawCurves(i, pres.B0, pres.B1, pres.B2, pres.B3, pres.color);
      }
    }
    

}

void drawCurves(float t, vec3 b0, vec3 b1, vec3 b2, vec3 b3, vec3 color){
  float current = 1-t;
    float first = std::pow(current,3);
    float second = 3*t* std::pow(current,2);
    float third = 3* std::pow(t, 2) * current;
    float fourth = std::pow(t, 3);
    vec3 pos = (first * b0) + (second *b1) + (third *b2) + (fourth *b3) ;
    setColor(color);
    drawSphere(pos, 2);
}

  float randomNum(int limit){
    return (float)(rand()%limit);
  }

  private:
  float t;

  std::list<Curve> curves;
  Curve before;
  Curve after;
  int index = 0;

};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

