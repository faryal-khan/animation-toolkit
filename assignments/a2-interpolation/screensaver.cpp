#include "atkui/framework.h"
using namespace glm;

class Screensaver : public atkui::Framework {
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    t = 0.0;

   color1 = agl::randomUnitVector()/2.0f * vec3(1, 3, 5);
   color2 = agl::randomUnitVector()/2.0f;
   color3 = agl::randomUnitVector()/2.0f;

  }

  void scene() {
  for(float i=0.0;i<=1.0;i+=0.001){
      drawCurves(i, before[0], before[1], before[2], before[3],color1);
  }

  for(float i=0.0;i<=1.0;i+=0.001){
      drawCurves(i, after[0], after[1], after[2], after[3], color2);
  }

  vec3 new0;
  vec3 new1;
  vec3 new2;
  vec3 new3;

  if(t<=1){
    t += 0.005;
  }
  else{
    t = 0.0;
    before[0] = after[0];
    before[1] = after[1];
    before[2] = after[2];
    before[3] = after[3];
    after[0] = vec3(randomNum(400), randomNum(400), 0);
    after[1] = vec3(randomNum(400), randomNum(400), 0);
    after[2] = vec3(randomNum(400), randomNum(400), 0);
    after[3] = vec3(randomNum(400), randomNum(400), 0);
    color1= agl::randomUnitVector()/3.0f;
    color2 = agl::randomUnitVector()/3.0f;
    color3 = agl::randomUnitVector()/3.0f;
  }

  new0 = before[0] *(1-(t)) + after[0] *t;
  new1 = before[1] *(1-(t)) + after[1] *t;
  new2 = before[2] *(1-(t)) + after[2] *t;
  new3 = before[3] *(1-(t)) + after[3] *t;


  for(float j=0.0;j<=1.0;j+=0.001){
    drawCurves(j, new0, new1, new2, new3, color3);
  }
  

    
  
  }

void drawCurves(float t, vec3 b0, vec3 b1, vec3 b2, vec3 b3, vec3 color){
  float current = 1-t;
    float first = std::pow(current,3);
    float second = 3*t* std::pow(current,2) ;
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

  vec3 before [4]=
    {
    vec3(randomNum(400), randomNum(400), 0),
    vec3(randomNum(400), randomNum(400), 0),
    vec3(randomNum(400), randomNum(400), 0),
    vec3(randomNum(400), randomNum(400), 0)
    };
  vec3 after [4]=
    {
    vec3(randomNum(400), randomNum(400), 0),
    vec3(randomNum(400), randomNum(400), 0),
    vec3(randomNum(400), randomNum(400), 0),
    vec3(randomNum(400), randomNum(400), 0)
    };

  vec3 color1;
  vec3 color2;
  vec3 color3;

};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

