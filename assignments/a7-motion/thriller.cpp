#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      xPos = 50;
      zPos = 0;
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);
      
      for(int i=0;i<3;i++){
         zPos += 100;
         xPos = 50;
         for(int j=0;j<4;j++){
            xPos +=100;
            Devil _devil;
            vec3 mainColor = vec3(0,0,1);
            vec3 color = mainColor + agl::randomUnitVector();
            vec3 position = vec3(xPos, 0, zPos) + agl::randomUnitVector();
            float size = 1.0f;
            _devil = Devil(position, color, size);
            chars.push_back(_devil);
         }
      }
   }

   virtual void scene() {
      

      if (!_paused) _motion.update(_skeleton, elapsedTime());

      for(int i=0;i<chars.size();i++){
         chars.at(i).draw(_skeleton, *this);
      }
      
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   std::vector<Devil> chars;
   int xPos;
   int zPos;
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

