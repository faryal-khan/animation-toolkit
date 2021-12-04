#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ADancer : public atkui::Framework
{
public:
   ADancer() : atkui::Framework(atkui::Perspective) {}
   virtual ~ADancer() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.color = vec3(1,0,0);
      thetaRate = 3.0;
      theta = 0.0;
   }

   void update()
   {
      _motion.update(_skeleton, elapsedTime());

      IKController ik;
      // TODO: Your code here
      
   }

   void scene()
   {  
      update();

      theta += thetaRate * dt();
      float py = 50.0f *sin(theta);
      float px1 = _skeleton.getByName("Beta:LeftHand")->getGlobalTranslation().x;
      float px2 = _skeleton.getByName("Beta:RightHand")->getGlobalTranslation().x;

      _lhandTarget = vec3(px1, py+(0.5*height() -140), 20);
      _rhandTarget = vec3(px2, -py+((0.5*height() -140)), 20);

      _drawer.draw(_skeleton, *this);
      setColor(vec3(0,0,1));
      drawSphere(_lhandTarget, 10);
      drawSphere(_rhandTarget, 10);
   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   // Hand target positions
   vec3 _lhandTarget;
   vec3 _rhandTarget;
   float thetaRate;
   float theta;

};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}

