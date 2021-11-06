#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "person.h"

using namespace atk;
using namespace glm;

class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      vec3 position = vec3(0);
      vec3 color = vec3(0.4,0,0.2);
      float size = 1.0f;
      _person = Person(position, color, size);
   }

   virtual void scene() {
      _motion.update(_skeleton, elapsedTime());
      _person.draw(_skeleton, *this);
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   Person _person;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
}